#include "../include/hash_int.h"

u_int32_t int32hash(u_int32_t a)
{
	/*
	 * Robert Jenkins' 32 bit integer hash function
	 * Source: https://github.com/JeffBezanson/libsupport/blob/master/hashing.c
	*/
	a = (a+0x7ed55d16) + (a<<12);
	a = (a^0xc761c23c) ^ (a>>19);
	a = (a+0x165667b1) + (a<<5);
	a = (a+0xd3a2646c) ^ (a<<9);
	a = (a+0xfd7046c5) + (a<<3);
	a = (a^0xb55a4f09) ^ (a>>16);
	return a;
}

unsigned int fiftyhash(unsigned int x) {
    /*
     * Source:
     * https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
    */
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

int _calcula_pos(HashInt * hash, int key, int i) {
    // hash duplo dos elementos
    return (fiftyhash(key) + i * int32hash(key)) % hash->max_size;
}

int insere_hash_int(HashInt * hash, void * bucket) {
    int ret;

    //checagem se o array da tabela está cheio
    if(hash->size == hash->max_size) {
		free(bucket);
		ret = EXIT_FAILURE;
    }
    else {
		int pos;
		int key = hash->get_key(bucket);
		int i = 0;
		
		//garante que a posição para alocação da estrutura esteja desocupada
		for(pos = _calcula_pos(hash, key, i); hash->array[pos] != 0; pos = _calcula_pos(hash, key, ++i));

		//armazena ponteiro para o bucket específico
		hash->array[pos] = (uintptr_t) bucket;
		hash->size++;
		//acréscimo ao tamanho ocupado pelo vetor;

		ret = EXIT_SUCCESS;
    }

    return ret;
}

void * busca_hash_int(HashInt * hash, int key) {
    //criação do objeto para retorno
    void * ret = NULL; 

    int i = 0;

    for(int pos = _calcula_pos(hash, key, i); hash->array[pos] != 0 && !ret; i++) {
		if (hash->get_key((void *) hash->array[pos]) == key) ret = (void *) hash->array[pos];
		else pos = _calcula_pos(hash, key, i); 
    }

    return ret;
}

int constroi_hash_int(HashInt * hash, int n_buckets, int (* get_key)(void *)) {
    int ret;
    //aloca espaco para array da tabela
    hash->array = calloc(sizeof(void *), n_buckets + 1);

    //em caso de falha na alocação
    if(hash->array == NULL) ret = EXIT_FAILURE;
    else {
		//inicialização dos parâmetros necessários
		hash->size = 0;
		hash->max_size = n_buckets + 1;
		hash->get_key = get_key;

		ret = EXIT_SUCCESS;
    }

    return ret;
}

//elimina todos os registros da tabela
void libera_hash_int(HashInt * hash) {
    //libera posição a posição do array
    for(int pos = 0; pos < hash->max_size; pos++) {
		if(hash->array[pos] != 0) free((void *) hash->array[pos]);
    }

    //libera o array
    free(hash->array);
}

void exibe_hash_int(HashInt * hash) {
    for(int pos = 0; pos < hash->max_size; pos++) {
        printf("%d: ", pos);
		if(hash->array[pos] != 0) printf("%d\n\n", hash->get_key((void *) hash->array[pos]));
		else printf("%ld\n\n", hash->array[pos]);
    }
}
