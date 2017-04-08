#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	int rc;
	int processId;
	int noProcesses;
	int nameSize;
	char computerName[MPI_MAX_PROCESSOR_NAME];

	/*
	 * MPI_Init(&argc, &argv)
	 * Inicializa uma sessão MPI. 
	 * DEVE SER CHAMADA ANTES DE QUALQUER OUTRA FUNÇÃO MPI.
	 */	
	rc = MPI_Init(&argc, &argv);
	if (rc == MPI_SUCCESS)
	{			
		/*
		 * MPI_Comm_size(MPI_COMM_WORLD, &noProcesses)
		 * Obtem o nº de processos que "rodam" em um comunicador.
		 *
		 * Parâmetros:
		 * MPI_COMM_WORLD (in): comunicador dos processos
		 * &noProcesses (out): recebe o nº de processos que o comunicador MPI_COMM_WORLD vai utilizar
		 *
		 * Observação: 
		 * MPI_COMM_WORLD é o comunicador padrão criado automaticamente na inicialização da sessão MPI 
		 * e contém todos processados usados no programa.
		 */
		 
		MPI_Comm_size(MPI_COMM_WORLD, &noProcesses);

		/*
		 * MPI_Comm_rank(MPI_COMM_WORLD, &processId)
		 * Determina a posição de um processo em execução em um comunicador.
		 *
		 * Parâmetros:
		 * MPI_COMM_WORLD (in): comunicador dos processos
		 * &processId (out): recebe o valor da posiçao do processo que está em execução.
		 *
		 * Observação:
		 * A posição retornada por esta função é a (qtd. de processos - 1).
		 */

		MPI_Comm_rank(MPI_COMM_WORLD, &processId);

		/*
		 * MPI_Get_processor_name(computerName, &nameSize);
		 * Obtem o nome do host no qual o processo está em execução
		 * 
		 * Parâmetros:
		 * computerName (out): array de caracter que armazena o nome do host
		 * &nameSize (out): retorna o tamanho do nome do host
		 */
		MPI_Get_processor_name(computerName, &nameSize);


		fprintf(stderr, "%s - Processo %d de %d \n", computerName, processId, noProcesses);
	}
	
	/*
	 * MPI_Finalize()
	 * Libera a memória utilizada na sessão MPI criada.
	 */

	MPI_Finalize();
	return 0;
}

