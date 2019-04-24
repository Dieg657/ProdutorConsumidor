#include "sinaleiro.h"
#include <sys/sem.h>
#include <stdio.h>

static int constroi(int sem_id)
{
   union semun sem_union;
   sem_union.val = 1;
   if (semctl(sem_id, 0, SETVAL, sem_union) == -1) return(0);
   return(1);
}

static void destroi(int sem_id)
{
   union semun sem_union;
   if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
       fprintf(stderr, "ERRO: Falha ao deletar o semaforo\n");
}

static void libera(int sem_id){
   struct sembuf sem_b;
   sem_b.sem_num = 0;
   sem_b.sem_op = 1; /* P() */
   sem_b.sem_flg = SEM_UNDO;
   semop(sem_id, &sem_b, 1);
}

static void bloqueia(int sem_id){
   struct sembuf sem_b;
   sem_b.sem_num = 0;
   sem_b.sem_op = -1;
   sem_b.sem_flg = SEM_UNDO;
   semop(sem_id, &sem_b, 1);
}