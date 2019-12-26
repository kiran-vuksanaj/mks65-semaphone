#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "err.h"
#include "sem_util.h"

int create_sem(int key,int ival){
  int semd = semget(key,1,IPC_CREAT|IPC_EXCL|0644);
  exit_err(semd,"get semaphore identifier");
  union semun sem_un;
  sem_un.val = ival;
  exit_err(  semctl(semd,0,SETVAL,sem_un), "set initial value"  );
  return semd;
}

void remove_sem(int semd){
  exit_err(  semctl(semd,0,IPC_RMID), "remove semaphore" );
}

void semdown(int semd){
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  sb.sem_flg = 0;
  exit_err(  semop(semd,&sb,1), "downing semaphore" );
}

void semup(int semd){
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = 1;
  sb.sem_flg = 0;
  exit_err(  semop(semd,&sb,1), "upping semaphore" );
}
