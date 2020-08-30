# GRR20190374 Tiago Henrique Conte
# define as flags para compilação
CFLAGS = -Wall
CC = gcc
 
objs = ortografia.o dicionario.o
 
# regra default
all: ortografia
 
# regras de ligacao
ortografia: $(objs)
 
# regras de compilação
ortografia.o: ortografia.c dicionario.h
dicionario.o: dicionario.c dicionario.h

# compila com flags de depuração
debug: CFLAGS += -DDEBUG -g
debug: all

# remove arquivos temporários
clean:
	-rm -f $(objs)

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f ortografia