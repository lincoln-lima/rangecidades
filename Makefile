###############
## váriaveis ##

SRC = ./src
INCLUDE = ./include

LIB = ./lib
BIN = ./bin

APP = app

CC = gcc
LIBS = -L $(LIB) -l mun -l hashint -l technical

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

$(BIN)/$(APP): $(APP)/main.c $(SRC)/*.c
	$(CC) $^ -I $(INCLUDE) $(LIBS) -o $@

# gcc app/main.c src/*.c -I include/ -L lib/ -l ... -o /bin/main

#################
## manualmente ##

# executa
run:
	$(BIN)/$(APP)

# exclui arquivos gerados
clean:
	rm -rf $(BIN)
