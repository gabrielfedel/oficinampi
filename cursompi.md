No programa o trecho mpi deve ser cercado por
MPI_Init (&argc,&argv) e MPI_Finalize


MPI_Comm_size(MPI_COMM_WORLD, &size)
/*número de processos disparados*/

MPI_Comm_rank
/*identidade (rank) do processo*/

MPI_Cart_create(COMM, dims, dsize, wrap, reorder, cart)
/*cria uma topologia cartesiana, a partir dos comunicadores em COMM, com dimensões dim, wrap diz se é fechada, e reorder se pode reordeenar os comunicadores. coloca os comunicadores em cart*/

MPI_Cart_coords(cart, myrank, dims, coords)
/*retorna as coordenadas numa topologia de dims dimensões - coords é um vetor*/

MPI_Cart_shif(cart, dim, displ, &src, &dst))
/*retorna ranks dos vizinhos a uma distância displ na topologia*/

#Funções de comunicação simples

MPI_Send(msg, length, type, id, tag, comm)
/*envia msg para o processo id
tem que ser do mesmo tipo
o tipo pode ser packed (como um struct em c)
tag : indica qual finalidade da mensagem
não bloqueante
*/

MPI_Recv(msg length type, id, tag, comm, status)
/*
bloqueante
status: para testar os dados recebidos (se o recebido eh igual o esperado)
*/

MPI_Sendrecv(smsg, slength, stype, dest, stag, rmsg, relength, rtype, source, rtag, comm, status)
/*
faz leitura e recebimento (considerando que o mesmo código está rodando em diversas máquinas simultaneamente)
*/

MPI_Barrier(group)
/* fazer processos em grupo esperarem pelos demais */

MPI_Bcast(msg count, type, root, comm)
/*
disparar broadcast (o prcesso que tem rank root

*/

MPI_Scatter(msg, count, type, rmsg, rcount, rtype, root, comm)
/*
o processo root envia um conjunto de dados (por exemplo matriz 400x400), que será recebido parcialmente por cada outro processo (por exemplo 1 recebe 0..100 linhas, o 2 recebe 101..linhas..
*/

MPI_Gather....
/*
recebe o pedaço enviado por Scatter
*/

MPI_Reduce
/*
similar ao Scatter, porém o root também aplicaca operação nos operandos recebidos
*/
MPI_Allreduce
/*
todo mundo manda , não só o root
*/

open-mpi.org

mcs.anl.gov/mpi

ufsca.edu/~peter/ppmpi


# Problema:
chapa temperatura uniforme, alguns pontos com temperatura especifico
como calcular a temperatura em um ponto

para achar a temperatura, média da temperatura dos vizinhos (horizontal e vertical) e dele próprio na interação interior

fazendo calculo na matriz red e na matriz na black

a programação é feito dividindo a matriz em grupo de linhas ou colunas (para escolher como dividir, depende da linguagem, cada uma armazena a matriz de um jeito)

-----
Solução em SPMD pela criação de barreiras de sincronismo entre cada iteração

--

compilação usando openmpi

mpicc -o arqexec arqfonte.c

execução

mpirun -np numproc arqexec
(-numpro: numero de processos disparados)

# Versão 1
MPI_Send, MPI_Recv e MPI_Sendrecv


