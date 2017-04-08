#include "stdio.h"
#include <mpi.h>
#include <time.h>

#define maxtime 80000
/* A simulação é executada com pelo menos MINPROC 
* processos, podendo ser igual a 1 para testes
* Para uma matriz maior é interessante ajustar MINPROC
* para o número real de processadores */
#define MINPROC 4
#define cols 200
#define totrows 200
#define rows totrows/MINPROC + 2

double black[rows+2][cols+2];

void storeconst(int s, int e, int row, int col, double val)
{ if (row >= s && row <= e)
      black[row-s][col] = val;   }

int main(int argc, char **argv)
{double red[rows+2][cols+2];
 int s, e, mylen, r, c, tick;
 int inum, nproc, dims, coords[2], ndim = 1;
 int periods[1], reorder;// usadas como booleanas
 int upproc, downproc; 
 MPI_Comm comm1d;//struct ompi_communicator_t *comm1d;
 MPI_Status status;

// Chamando MPI_INIT
   MPI_Init (&argc, &argv);
// Recebendo o número de processos em paralelo
   MPI_Comm_size (MPI_COMM_WORLD, &nproc);

   dims = nproc;      
   periods[0] = 0; // significa um valor falso
   reorder = 1; // significa um valor verdade

// cria grupo cartesiano unidimensional de processos
   MPI_Cart_create (MPI_COMM_WORLD, ndim, &dims, periods, reorder, &comm1d); 
// Pega valor de rank dentro do grupo de comunicadores
   MPI_Comm_rank (comm1d, &inum);
// Pega a topologia do grupo COMM1D e o lugar desse processo dentro dessa topologia
   MPI_Cart_get (comm1d, ndim, &dims, periods, coords);
/* Retorna os vizinhos de distância 1 acima e abaixo,   *
 * sendo que os das extremidades terão apenas um desses *
 * vizinhos.                                            *
 * MPI_CART_SHIFT cuida disso para nós                  */
   MPI_Cart_shift (comm1d, 0, 1, &upproc, &downproc);
   s = totrows/nproc*inum;
   e = totrows/nproc*(inum+1);
   mylen = (e - s) + 1;
   if (mylen > rows) 
     { printf ("No space, need %d, have %d (split among %d processors)\n", mylen, rows, nproc); 
       printf ("%d %d %d %d %d\n",totrows, nproc, inum, s, e);
     }
// Começa frio (todos os pontos em 0◦C)
   for (r=0; r <= mylen+1; r++)
     for (c=0; c <= cols+1; c++)
            black[r][c] = 0.0;
// Inicia a execução das iterações
   for (tick = 1; tick <= maxtime; tick++)  {
// Inicia valores das fontes constantes de calor
      storeconst(s, e, totrows/3, cols/3, 10.0);
      storeconst(s, e, 2*totrows/3, cols/3, 20.0);
      storeconst(s, e, totrows/3, 2*cols/3, -20.0);
      storeconst(s, e, 2*totrows/3, 2*cols/3, 20.0);
      
// Envia para vizinho de cima e recebe do vizinho abaixo
      MPI_Send(&black[1][0], cols, MPI_DOUBLE, upproc, 1, comm1d);
      MPI_Recv(&black[mylen+1][0], cols, MPI_DOUBLE, downproc, 1, comm1d, &status); 
// Envia para baixo e recebe de cima num único comando
      MPI_Sendrecv (&black[mylen][0], cols, MPI_DOUBLE, downproc, 2, &black[0][0], cols, MPI_DOUBLE, upproc, 2, MPI_COMM_WORLD, &status);
/* Calcula-se as temperaturas nessa iteração */
     for (r=1; r <= mylen; r++)
       for (c=1; c <= cols; c++)
          red[r][c] = ( black[r][c] + black[r][c-1] + black[r-1][c] + black[r+1][c] + black[r][c+1] ) / 5.0;
/* Copia a matriz – Normalmente faríamos a fase vermelha do laço, mas assim diminuímos  o tamanho do exemplo */
     for (r=1; r <= mylen; r++)
       for (c=1; c <= cols; c++)
          black[r][c] = red[r][c];
  }  /* Final do laço principal “for (tick = 1; tick <= maxtime; tick++)” */
  if (inum==1) 
    { for (r=12; r <= 22; r++) {
        for (c=62; c <= 70; c++)
          printf("%lf ",black[r][c]);
      puts("  "); }
    }
  MPI_Finalize();
}


