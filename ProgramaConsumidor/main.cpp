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

static int produz;
static int consome;

int main()
{
   void *memoria_compartilhada = (void *)0;
   struct memoria *aux;
   int id_memoria;

   produz = semget((key_t)6667, 1, 0666 | IPC_CREAT);
   consome = semget((key_t)6668, 1, 0666 | IPC_CREAT);

   cria_segmento_de_memoria(&id_memoria);
   anexa_segmento_de_memoria(&id_memoria, &memoria_compartilhada);


    aux = (struct memoria*)memoria_compartilhada;
    inicializador(aux);

   for(;;)
   {
       if(aux->tamanho!=0)
       {
           aux->conteudo[aux->c]=' ';
           aux->tamanho--;
           aux->c++;
           if(aux->c==aux->max)aux->c=0;
           printf("%s\n",aux->conteudo);
       }
       sleep(1);

   }

   desanexa_segmento_de_memoria(&memoria_compartilhada);
   deleta_segmento_de_memoria(&id_memoria);
   return 0;
}
