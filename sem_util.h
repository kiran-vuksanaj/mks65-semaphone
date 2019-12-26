#ifndef SEM_UTIL_H
#define SEM_UTIL_H

/* this is probably not necessary but it makes it so much nicer to read the code */
union semun {
  int              val;    /* Value for SETVAL */
  struct  semid_ds *buf;     /*  Buffer for  IPC_STAT,
				 IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL
			    */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
			      (Linux-specific) */
};

int create_sem(int key,int ival);
void remove_sem(int semd);

void semdown(int semd);
void semup(int semd);
#endif
