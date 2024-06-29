###############
## váriaveis ##

SRC = ./src
INCLUDE = ./include

LIB = ./lib
BIN = ./bin

APP = app

CC = gcc
LIBS = -l technical

###############
## diretivas ##

all: $(BIN)/ appmun

#####################################
# avalia se caminhos existem e os cria caso não

$(BIN)/:
	mkdir $@

#####################################
# compila o programa

appmun: $(BIN)/$(APP)

$(BIN)/$(APP): $(SRC)/*.c
	$(CC) $^ -I $(INCLUDE) -L $(LIB) $(LIBS) -o $@

# gcc main.c -I include/ -L lib/ -l ... -o /bin/main

#################
## manualmente ##

# executa
run:
	$(BIN)/$(APP)

# exclui arquivos gerados
clean:
	rm -rf $(BIN)
