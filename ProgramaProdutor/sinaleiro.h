#ifndef SINALEIRO_H
#define SINALEIRO_H

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
   /* union semun is defined by including <sys/sem.h> */
#else
   union semun {
       int val;
       struct semid_ds *buf;
       unsigned short int *array;
       struct seminfo *__buf;
   };
#endif


#endif // SINALEIRO_H
