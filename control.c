#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "err.h"
#include "sem_util.h"
#include "standards.h"

void print_filecontents();

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: ./control -[crv]\n");
    return EINVAL;
  }
  int SEMD,SHMD;
  char *shm;
  switch(argv[1][1]){
  case 'c':
    create_sem(KEY,1);
    printf("[semaphore created]\n");
    exit_err( shmget(KEY,SHM_SIZE,IPC_CREAT|IPC_EXCL|0644), "initializing shared memory" );
    printf("[shared memory initialized]\n");
    exit_err( open(FILENAME,O_CREAT|O_TRUNC,0644), "resetting/opening file" );
    printf("[file created/reset]\n");
    break;
  case 'r':
    SEMD = semget(KEY,1,0);
    exit_err( SEMD, "getting semaphore id" );
    
    semdown(SEMD);
    print_filecontents();
    // don't need to semup bc its getting removed anyways
    remove_sem( SEMD );
    printf("[semaphore removed]\n");
    SHMD = shmget(KEY,SHM_SIZE,0);
    exit_err( SHMD, "connecting to shared memory" );
    exit_err(  shmctl(SHMD,IPC_RMID,0), "removing shared memory"  );
    printf("[shared memory removed]\n");
    exit_err(  remove(FILENAME), "removing file" );
    printf("[file removed]\n");
    break;
  case 'v':
    print_filecontents();
    break;
  default:
    printf("usage: ./control -[crv]\n");
    return EINVAL;
  }
  return 0;
}

void print_filecontents(){
  char buf;
  int fd = open(FILENAME,O_RDONLY);
  exit_err( fd, "accessing file file" );
  printf("#### STORY CONTENTS ####\n");
  fd = open(FILENAME,O_RDONLY);
  exit_err( fd, "acessing file" );
  while( read(fd,&buf,1) ){
    putchar(buf);
  }
  printf("\n#### THE END ####\n");
}
