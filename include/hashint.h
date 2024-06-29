#ifndef __HASHINT__
#define __HASHINT__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct {
   uintptr_t * array;
   int size;
   int max_size;
   int (* get_key)(void *);
} HashInt;

/* hash  */
uint32_t int32hash(u_int32_t a);
unsigned int fiftyhash(unsigned int x);
/* posição com duplo hash  */
int _calcula_pos_hash_int(HashInt * hash, int key, int i); 
/* inserção  */
int insere_hash_int(HashInt * hash, void * bucket);
/* busca  */
void * busca_hash_int(HashInt * hash, int key);
/* constrói*/
int constroi_hash_int(HashInt * hash, int n_buckets, int (* get_key)(void *));
/* destrói */
void libera_hash_int(HashInt * hash);
#endif
