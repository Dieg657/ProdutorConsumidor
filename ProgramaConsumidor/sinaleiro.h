#ifndef SINALEIRO_H
#define SINALEIRO_H

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
   /* union semun is defined by including <sys/sem.h> */
#else
   union semun
   {
       int val;                /* value for SETVAL */
       struct semid_ds *buf;   /* buffer for IPC_STAT & IPC_SET */
       ushort *array;          /* array for GETALL & SETALL */
       struct seminfo *__buf;  /* buffer for IPC_INFO */
       void *__pad;
   };
#endif




#endif // SINALEIRO_H
