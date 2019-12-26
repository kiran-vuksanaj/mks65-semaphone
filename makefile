ifeq ($(DEBUG),true)
	CFLAGS = -g
endif

all: write.o control.o err.o
	gcc -o control control.o err.o
	gcc -o write write.o err.o
write.o: write.c write.h err.h
	gcc -c write.c
control.o: control.c control.h err.h
	gcc -c control.c
err.o: err.c err.h
	gcc -c err.c
