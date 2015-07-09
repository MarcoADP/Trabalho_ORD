CC     = gcc
CFLAGS = -Wall
RM     = rm
#------------------------------------------------

# chama o linker
trabalho:  main.o util.o indice.o arquivo.o operacoes.o
	$(CC) main.o util.o indice.o arquivo.o operacoes.o -o trabalho

main.o: main.c operacoes.h util.h
	$(CC) $(CFLAGS) -c main.c 

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c 

indice.o: indice.c indice.h arquivo.h
	$(CC) $(CFLAGS) -c indice.c 

arquivo.o: arquivo.c arquivo.h util.h
	$(CC) $(CFLAGS) -c arquivo.c 

operacoes.o: operacoes.c operacoes.h indice.h arquivo.h util.h
	$(CC) $(CFLAGS) -c operacoes.c 

clean: 
	rm -f *.o 