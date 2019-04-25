#include "sinaleiro.h"
#include <sys/sem.h>
#include <stdio.h>

int constroi(int sem_num, int sem_id)
{
   union semun sem_union;
   sem_union.val = 1;
   printf("Num linha: %d, Sem: %d\n", __LINE__, sem_num);
   if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
       fprintf(stderr, "ERRO: Falha ao criar semaforo!\n");
   return 0;
}

static void destroi(int sem_num, int sem_id)
{
   union semun sem_union;
   if (semctl(sem_id, sem_num, IPC_RMID, sem_union) == -1)
       fprintf(stderr, "ERRO: Falha ao deletar o semaforo\n");
}

int libera(int sem_id){
   struct sembuf sem_b;
   sem_b.sem_num = 0;
   sem_b.sem_op = 1; /* P() */
   sem_b.sem_flg = SEM_UNDO;
   if(semop(sem_id, &sem_b, 1) == -1){
       fprintf(stderr, "ERRO: Falha ao liberar semaforo!");
       return -1;
   }
   return 0;
}

int bloqueia(int sem_id){
   struct sembuf sem_b;
   sem_b.sem_num = 0;
   sem_b.sem_op = -1;
   sem_b.sem_flg = SEM_UNDO;
   if(semop(sem_id, &sem_b, 1) == -1){
       fprintf(stderr, "ERRO: Falha ao fechar semaforo!");
       return -1;
   }
   return 0;
}
