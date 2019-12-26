#ifndef ERR_H
#define ERR_H

/* this isn't really necessary for this assignment but its become my preferred way of handling errors, makes code much easier to read */

void print_err(char *msg);
void exit_err(int r,char *msg);

#endif
