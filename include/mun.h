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

Mun * aloca_mun(int ibge, char * nome, float latitude, float longitude, int capital, int uf, int id, int ddd, char * fuso);
int get_key_mun(void * mun);
void exibe_mun(void * cid);
int cmp_int(void * a, void * b);
int cmp_float(void * a, void * b);
int cmp_str(void * a, void * b);
#endif
