#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "memoria.h"
#include "memoria.cpp"
#include "sinaleiro.h"
#include "sinaleiro.cpp"

#define PROD 1
#define CONS 2

#define PRODUTOR 1234
#define CONSUMIDOR 1234

int produtor;
int consumidor;

int main()
{
   void *memoria_compartilhada = (void *)0;
   struct memoria *aux;
   int id_memoria;

   constroi(PROD, produtor);
   produtor = semget((key_t)PRODUTOR, 1, IPC_CREAT | 0666);

   if(produtor < 0){
       fprintf(stderr, "ERRO: Falha ao obter o identificador de memória do semaforo!");
       //printf("Entrou aqui: %d\n", __LINE__);
   }
   constroi(CONS, consumidor);
   consumidor = semget((key_t)CONSUMIDOR, 1, IPC_CREAT | 0666);
   if(consumidor == -1){
       fprintf(stderr, "ERRO: Falha ao obter o identificador de memória do semaforo!"); return -1;
   }

   cria_segmento_de_memoria(&id_memoria);
   anexa_segmento_de_memoria(&id_memoria, &memoria_compartilhada);


    aux = (struct memoria*)memoria_compartilhada;
    inicializador(aux);

   for(;;)
   {
       bloqueia(consumidor);
       if(aux->tamanho!=0)
       {
           aux->conteudo[aux->c]=' ';
           aux->tamanho--;
           aux->c++;
           if(aux->c==aux->max)aux->c=0;
              printf("%s\n",aux->conteudo);
       }
       sleep(1);
       libera(produtor);
   }

   desanexa_segmento_de_memoria(&memoria_compartilhada);
   deleta_segmento_de_memoria(&id_memoria);
   destroi(PROD, produtor);
   destroi(CONS, consumidor);

   return 0;
}
