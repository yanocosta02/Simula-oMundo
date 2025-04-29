CFLAGS = -Wall -g
all: mundo

# regras de ligação
mundo: mundo.o libconjunto.o libfila.o liblef.o libmundo.o
	gcc mundo.o libconjunto.o libfila.o liblef.o libmundo.o -o mundo -lm $(CFLAGS)
 
# regras de compilação
mundo.o: mundo.c libconjunto.h libfila.h liblef.h libmundo.h
	gcc -c mundo.c $(CFLAGS)
 
libconjunto.o: libconjunto.c libconjunto.h
	gcc -c libconjunto.c $(CFLAGS)

libfila.o: libfila.c libfila.h
	gcc -c libfila.c $(CFLAGS)

liblef.o: liblef.c liblef.h
	gcc -c liblef.c $(CFLAGS)

libmundo.o: libmundo.c libmundo.h
	gcc -c libmundo.c $(CFLAGS)

# remove arquivos temporários
clean:
	-rm -f *~ *.o

# remove tudo o que não for o código-fonte original
purge: clean
	-rm -f mundo
