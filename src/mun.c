#include "../include/mun.h"

//a partir da passagem de parâmetros, constrói um "objeto" Município
void * aloca_mun(int ibge, char * nome, double latitude, double longitude, int capital, int uf, int id, int ddd, char * fuso) {
    Mun * mun = malloc(sizeof(Mun));

    mun->cod_ibge = ibge;
    strcpy(mun->nome, nome);
    mun->coord[0]= latitude;
    mun->coord[1]= longitude;
    mun->capital = capital;
    mun->cod_uf = uf;
    mun->siafi_id = id;
    mun->ddd = ddd;
    strcpy(mun->fuso, fuso);

    return mun;
}

//define a chave de cada município
int get_key_mun(void * mun) {
    return (*((Mun *) mun)).cod_ibge;
}

//informe um ponteiro de Municipio e todas suas informações serão mostradas
void exibe_mun(void * cid) {
    Mun * mun = (Mun *) cid;

    printf("---------------------------------\n");
    printf("codigo_ibge: %d\n", mun->cod_ibge);
    printf("nome: %s\n", mun->nome);
    printf("latitude: %f\n", mun->coord[0]);
    printf("longitude: %f\n", mun->coord[1]);
    printf("capital: %d\n", mun->capital);
    printf("codigo_uf: %d\n", mun->cod_uf);
    printf("siafi_id: %d\n", mun->siafi_id);
    printf("ddd: %d\n", mun->ddd);
    printf("fuso_horario: %s\n", mun->fuso);
    printf("\n");
}