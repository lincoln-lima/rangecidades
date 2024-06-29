###############
## váriaveis ##

SRC = ./src
INCLUDE = ./include

OBJ = ./obj
LIB = ./lib
BIN = ./bin

MAIN = main

CC = gcc
FLAG-OBJ = -c -fpic
FLAG-LIB = -shared -o
LIBS = -l avl -l hashint -l mun -l rangequery -l technical

###############
## diretivas ##

all: dir objs libs mymain

#####################################
# avalia se caminhos existem e os cria caso não

dir: $(OBJ)/ $(LIB)/ $(BIN)/ 

$(OBJ)/:
	mkdir $@

$(LIB)/:
	mkdir $@

$(BIN)/:
	mkdir $@

#####################################
# cria objetos caso não existam, ou haja uma alteração em seu .c ou .h

objs: $(OBJ)/avl.o $(OBJ)/hashint.o $(OBJ)/mun.o $(OBJ)/rangequery.o $(OBJ)/technical.o

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(CC) $(FLAG-OBJ) $< -I $(INCLUDE) -o $@

# gcc -c -fpic <>.c -I include/ -o <>.o

#####################################
# cria bibliotecas dinâmicas caso não existam, ou haja uma alteração em seu objeto

libs: $(LIB)/libavl.so $(LIB)/libhashint.so $(LIB)/libmun.so $(LIB)/librangequery.so $(LIB)/libtechnical.so

$(LIB)/lib%.so: $(OBJ)/%.o
	$(CC) $(FLAG-LIB) $@ $<

# gcc -shared -o lib<>.so <>.o 

#####################################
# compila o arquivo principal mediante seu .c e as bibliotecas referidas

mymain: $(BIN)/$(MAIN)

$(BIN)/$(MAIN): $(SRC)/$(MAIN).c
	$(CC) $< -I $(INCLUDE) -L $(LIB) $(LIBS) -o $@

# gcc main.c -I include/ -L lib/ -l lib... -o /bin/main

#################
## manualmente ##

# executa
run:
	$(BIN)/$(MAIN)

# exclui arquivos gerados
clean:
	rm -rf $(OBJ) $(LIB) $(BIN)
