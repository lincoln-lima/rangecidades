#include <stdio.h>
#include <stdlib.h>
#include "../include/mun.h"
#include "../include/avl.h"
#include "../include/range_query.h"
#include "../include/hash_int.h"
#include "../include/jsense.h"

#define QTD_MUNICIPIOS 5570
#define TAM_HASH 11139
#define N_CAMPOS 5

Mun * acessa_mun_json(JSENSE * arq, int pos);

int main() {
   JSENSE * arq = jse_from_file("./files/municipios.json");

   /* instanciação das árvores relativas aos queries */
   ArvAVL arvMunNome;
   constroi_avl(&arvMunNome, STR);

   ArvAVL arvMunLat;
   constroi_avl(&arvMunLat, FLOAT);

   ArvAVL arvMunLon;
   constroi_avl(&arvMunLon, FLOAT);

   ArvAVL arvMunUF;
   constroi_avl(&arvMunUF, INT);

   ArvAVL arvMunDDD;
   constroi_avl(&arvMunDDD, INT);

   /* instanciação da tabela hash para código ibge */
   HashInt hashMun;
   constroi_hash_int(&hashMun, TAM_HASH, get_key_mun);

   /*
      busca dos municípios no json
      e inserção das chaves com código em sua árvore
    */
   for(int i = 0; i < QTD_MUNICIPIOS; i++) {
      Mun * mun = acessa_mun_json(arq, i);
      insere_avl(&arvMunNome, &mun->nome, mun->cod_ibge);
      insere_avl(&arvMunLat, &mun->coord[0], mun->cod_ibge);
      insere_avl(&arvMunLon, &mun->coord[1], mun->cod_ibge);
      insere_avl(&arvMunUF, &mun->cod_uf, mun->cod_ibge);
      insere_avl(&arvMunDDD, &mun->ddd, mun->cod_ibge);
      insere_hash_int(&hashMun, mun);
   }

   ArvAVL * jungle[N_CAMPOS] = {&arvMunNome, &arvMunLat, &arvMunLon, &arvMunUF, &arvMunDDD};

   int continuar;

   printf("Busca de munícipios por range query\n");

   do {
      menu_inicial(&continuar);

      switch(continuar) {
         case 0:
            printf("-----------------------------------\n");
            printf("Encerrando execução...\n");
            break;
         case 1:
            int * nomes = NULL;
            int * lats = NULL;
            int * lons = NULL;
            int * ufs = NULL;
            int * ddds = NULL;

            int * conj[N_CAMPOS+1] = {nomes, lats, lons, ufs, ddds, NULL};
            int ** auxpp = conj;

            int * res = NULL;
            int ** ppres = &res;

            char * labels[N_CAMPOS] =
            {
               "Nome",
               "Latitude",
               "Longitude",
               "UF",
               "DDD"
            };

            int op;
            int eq;

            for(int i = 0; i < N_CAMPOS; i++) {
               menu_escolha(labels[i], &op);

               printf("conj: %p\n", conj);
               printf("*conj: %p\n\n", *conj);
               printf("auxpp: %p\n", auxpp);
               printf("*auxpp: %p\n\n", *auxpp);
               printf("ppres: %p\n", ppres);
               printf("*ppres: %p\n\n", *ppres);

               if(op) {
                  if(jungle[i]->tipo != STR) menu_range(&eq);
                  else eq = IGUAL;

                  conj[i] = query(jungle[i], eq, QTD_MUNICIPIOS);
                  *ppres = comb_query(*auxpp, conj[i], QTD_MUNICIPIOS);

                  auxpp = ppres;
               }
               else if(*auxpp == conj[i]) auxpp++; 

               printf("conj: %p\n", conj);
               printf("*conj: %p\n\n", *conj);
               printf("auxpp: %p\n", auxpp);
               printf("*auxpp: %p\n\n", *auxpp);
               printf("ppres: %p\n", ppres);
               printf("*ppres: %p\n\n", *ppres);
            }

            if(res) {
               int qtd = 0;
               for(int * pres = res; pres < res + QTD_MUNICIPIOS && *pres != 0; pres++) {
                  printf("---------------------------------\n");
                  exibe_mun((Mun *) busca_hash_int(&hashMun, *pres));
                  printf("---------------------------------\n");

                  qtd++;
               }

               printf("Registros: %d\n", qtd);
            } 
            else printf("Nenhum registro!\n");

            /* desalocação de arrays */
            free(nomes);
            free(lats);
            free(lons);
            free(ufs);
            free(ddds);
            free(res);
            break;
         default:
            printf("INVÁLIDA!!!\n");
      }

   } while(continuar);

   libera_avl(&arvMunNome);
   libera_avl(&arvMunLat);
   libera_avl(&arvMunLon);
   libera_avl(&arvMunUF);
   libera_avl(&arvMunDDD);
   libera_hash_int(&hashMun);

   jse_free(arq);

   return EXIT_SUCCESS;
}

/* acessa e retorna município de json */
Mun * acessa_mun_json(JSENSE * arq, int pos) {
   int error;

   char * campos[9] = 
   {
      "codigo_ibge",
      "nome",
      "latitude",
      "longitude",
      "capital",
      "codigo_uf",
      "siafi_id",
      "ddd",
      "fuso_horario"
   };

   char operacao[20];

   int cod_ibge, capital, cod_uf, siafi_id, ddd;
   char nome[35];
   char fuso[50];
   float latitude, longitude;

   for(int i = 0; i < 9; i++) {
      sprintf(operacao, "[%d].%s", pos, campos[i]);

      switch(i) {
         case 0:
            cod_ibge = tec_string_to_int(jse_get(arq, operacao));
            break;
         case 1:
            strcpy(nome, jse_get(arq, operacao));
            break;
         case 2:
            latitude = tec_string_to_double(jse_get(arq, operacao), &error);
            break;
         case 3:
            longitude = tec_string_to_double(jse_get(arq, operacao), &error);
            break;
         case 4:
            capital = tec_string_to_int(jse_get(arq, operacao));
            break;
         case 5:
            cod_uf = tec_string_to_int(jse_get(arq, operacao));
            break;
         case 6:
            siafi_id = tec_string_to_int(jse_get(arq, operacao));
            break;
         case 7:
            ddd = tec_string_to_int(jse_get(arq, operacao));
            break;
         case 8:
            strcpy(fuso, jse_get(arq, operacao));
            break;
      }
   }

   return aloca_mun(cod_ibge, nome, latitude, longitude, capital, cod_uf, siafi_id, ddd, fuso);
}
