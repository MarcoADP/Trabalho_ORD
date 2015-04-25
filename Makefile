CC     = gcc
CFLAGS = 
RM     = rm
#------------------------------------------------

# chama o linker
trabalho:  main.o util.o indice.o
	$(CC) main.o util.o indice.o -o trabalho

main.o: main.c util.h indice.h
	$(CC) $(CFLAGS) -c main.c 

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c 

indice.o: indice.c indice.h
	$(CC) $(CFLAGS) -c indice.c 

clean: 
	rm -f *.o 