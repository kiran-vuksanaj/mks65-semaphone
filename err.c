#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void print_err(char *msg){
  printf("err #%d during [%s]: [%s]\n",errno,msg,strerror(errno));
}

void exit_err(int r,char *msg){
  if( r < 0 ){
    print_err(msg);
    exit(errno);
  }
}
