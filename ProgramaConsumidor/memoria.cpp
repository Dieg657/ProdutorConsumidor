#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void inicializador(struct memoria * A) // Inicializador de Estrutura da Memória Compartilhada
{
   A->c=0;
   A->p=0;
   A->tamanho=0;
   A->max=50;
   for(int i=0; i<A->max; i++)
   {
       A->conteudo[i]=' ';
   }
}

void cria_segmento_de_memoria(int *id_memoria)
{
   *id_memoria=shmget((key_t)5555, sizeof(struct memoria), 0666 | IPC_CREAT);
   if (*id_memoria == -1) {
       fprintf(stderr, "ERRO: Falha ao criar segmento de memoria compartilhada\n");
       exit(EXIT_FAILURE);
   }
}
void deleta_segmento_de_memoria(int * id_memoria)
{
   if (shmctl((*id_memoria), IPC_RMID, 0) == -1) {
      fprintf(stderr, "ERRO: Falha ao apagar memoria compartilhada\n");
   }
}

void desanexa_segmento_de_memoria(void **memoria_compartilhada)
{
   if (shmdt(*memoria_compartilhada) == -1) {
       fprintf(stderr, "ERRO: Problema ao remover referencia da memoria compartilhada\n");
   }
}

void anexa_segmento_de_memoria(int * id_memoria, void **memoria_compartilhada)
{
   *memoria_compartilhada = shmat(*id_memoria, (void *)0, 0);
   if (*memoria_compartilhada == (void *)-1) {
       fprintf(stderr, "ERRO: Falha ao acoplar segmento de memoria!\n");
       exit(EXIT_FAILURE);
   }
}
