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
#define CONSUMIDOR 5678

int produtor;
int consumidor;

int main()
{
   void *memoria_compartilhada = (void *)0;
   struct memoria *aux;
   int id_memoria;

   produtor = semget((key_t)PRODUTOR, 1, IPC_CREAT | 0666);
   constroi(PROD, produtor);

   if(produtor < 0){
       fprintf(stderr, "ERRO: Falha ao obter o identificador de memória do semaforo!");
       printf("Entrou aqui: %d\n", __LINE__);
   }
   consumidor = semget((key_t)CONSUMIDOR, 1, IPC_CREAT | 0666);
   constroi(CONS, consumidor);
   printf("Entrou aqui: %d", __LINE__);
   if(consumidor == -1){
       fprintf(stderr, "ERRO: Falha ao obter o identificador de memória do semaforo!");
       printf("Entrou aqui: %d", __LINE__);
   }

   printf("Entrou aqui: %d", __LINE__);
   cria_segmento_de_memoria(&id_memoria);
   anexa_segmento_de_memoria(&id_memoria, &memoria_compartilhada);
   aux = (struct memoria*)memoria_compartilhada;

   printf("Entrou aqui: %d", __LINE__);
   for(;;){
       bloqueia(produtor);
       while(aux->tamanho != 50){
               if(aux->tamanho!=aux->max){
                   aux->conteudo[aux->p]='J';
                   aux->tamanho++;
                   aux->p++;
                   if(aux->p==aux->max)aux->p=0;
                   printf("%s",aux->conteudo);
               }
               sleep(1);
       }
       libera(consumidor);
   }

   desanexa_segmento_de_memoria(&memoria_compartilhada);
   destroi(PROD, produtor);
   destroi(CONS, consumidor);
   return 0;
}
