#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "err.h"
#include "sem_util.h"
#include "standards.h"

int main(){
  int SEMD,SHMD,fd;
  char *shm;
  SEMD = semget(KEY,0,0);
  exit_err(SEMD,"conecting to semaphore");
  SHMD = shmget(KEY,0,0);
  exit_err(SHMD,"connecting to shared memory");
  shm = shmat(SHMD,0,0);
  fd = open(FILENAME,O_WRONLY|O_APPEND);
  exit_err(fd,"opening file");
  
  semdown(SEMD);

  printf("last addition: %s\n",shm);
  printf("your addition: ");
  fgets(shm,SHM_SIZE,stdin);
  //  sleep(10);
  write(fd,shm,strlen(shm));
  
  semup(SEMD);
  shmdt(shm);
}
