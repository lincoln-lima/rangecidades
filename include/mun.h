#ifndef __MUNICIPIO__
#define __MUNICIPIO__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int cod_ibge;
    char nome[35];
    double coord[2];
    int capital;
    int cod_uf;
    int siafi_id;
    int ddd;
    char fuso[50];
} Mun;

void * aloca_mun(int ibge, char * nome, double latitude, double longitude, int capital, int uf, int id, int ddd, char * fuso);
int get_key_mun(void * mun);
void exibe_mun(void * cid);
#endif
