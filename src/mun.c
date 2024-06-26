#include "../include/mun.h"

/* constroi objeto Municipio */
Mun * aloca_mun(int ibge, char * nome, float latitude, float longitude, int capital, int uf, int id, int ddd, char * fuso) {
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

/* retorna chave do Municipio */
int get_key_mun(void * mun) {
   return (*((Mun *) mun)).cod_ibge;
}

/* mostra todos os campos do Municipio */
void exibe_mun(void * cid) {
   Mun * mun = (Mun *) cid;

   printf("codigo_ibge: %d\n", mun->cod_ibge);
   printf("nome: %s\n", mun->nome);
   printf("latitude: %f\n", mun->coord[0]);
   printf("longitude: %f\n", mun->coord[1]);
   printf("capital: %d\n", mun->capital);
   printf("codigo_uf: %d\n", mun->cod_uf);
   printf("siafi_id: %d\n", mun->siafi_id);
   printf("ddd: %d\n", mun->ddd);
   printf("fuso_horario: %s\n", mun->fuso);
}
