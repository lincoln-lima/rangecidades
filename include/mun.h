#ifndef __MUN__
#define __MUN__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
   int cod_ibge;
   char nome[35];
   float coord[2];
   int capital;
   int cod_uf;
   int siafi_id;
   int ddd;
   char fuso[50];
} Mun;

/* constrói */
Mun * aloca_mun(int ibge, char * nome, float lat, float lon, int capital, int uf, int id, int ddd, char * fuso);
/* retorna chave */
int get_key_mun(void * mun);
/* mostra todos os campos */
void exibe_mun(Mun * mun);
#endif
