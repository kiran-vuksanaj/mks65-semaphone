ifeq ($(DEBUG),true)
	CFLAGS = -g
endif

all: write.o control.o err.o sem_util.o
	gcc -o control control.o err.o sem_util.o
	gcc -o write write.o err.o sem_util.o
write.o: write.c err.h sem_util.h standards.h
	gcc -c write.c
control.o: control.c err.h sem_util.h standards.h
	gcc -c control.c
err.o: err.c err.h
	gcc -c err.c
sem_util.o: sem_util.c sem_util.h
	gcc -c sem_util.c
