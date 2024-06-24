#include <stdio.h>
#include <stdlib.h>
#include "../include/mun.h"
#include "../include/avl.h"
#include "../include/range_query.h"
#include "../include/hash.h"
#include "../include/jsense.h"

#define QTD_MUNICIPIOS 5570
#define TAM_HASH 11139

#define INT 1
#define FLOAT 2
#define STR 3

Mun * acessa_mun_json(JSENSE * arq, int pos);

int main() {
   JSENSE * arq = jse_from_file("./files/municipios.json");

   /* instanciação das árvores relativas aos queries */
   ArvAVL arvMunNome;
   constroi_avl(&arvMunNome, cmp_str);

   ArvAVL arvMunLat;
   constroi_avl(&arvMunLat, cmp_float);

   ArvAVL arvMunLon;
   constroi_avl(&arvMunLon, cmp_float);

   ArvAVL arvMunUF;
   constroi_avl(&arvMunUF, cmp_int);

   ArvAVL arvMunDDD;
   constroi_avl(&arvMunDDD, cmp_int);

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

   int continuar;

   do {
      menu_inicial(&continuar);

      switch(continuar) {
         case 0:
            printf("Encerrando execução...\n");
            break;
         case 1:
            int * ret;

            for(int i = 1; i <= 5; i++) {
               int op;

               printf("\n");

               switch(i) {
                  case 1:
                     menu_escolha("Nome", &op);
                     int * nomes = (op == 1) ? query(ArvMunNome, STR) : NULL;
                     break;
                  case 2:
                     menu_escolha("Latitude", &op);
                     int * lats = (op == 1) ? query(ArvMunLats, FLOAT) : NULL;
                     break;
                  case 3:
                     menu_escolha("Longitude", &op);
                     int * lons = (op == 1) ? query(ArvMunLons, FLOAT) : NULL;
                     break;
                  case 4:
                     menu_escolha("UF", &op);
                     int * ufs = (op == 1) ? query(ArvMunUF, INT) : NULL;
                     break;
                  case 5:
                     menu_escolha("DDD", &op);
                     int * ddds = (op == 1) ? query(ArvMunDDD, INT) : NULL;
                     break;
               }
            }
            ret = comb_query(nomes, lats, QTD_MUNICIPIOS);
            ret = comb_query(ret, lons, QTD_MUNICIPIOS);
            ret = comb_query(ret, ufs, QTD_MUNICIPIOS);
            ret = comb_query(ret, ddds, QTD_MUNICIPIOS);

            int * pret = ret;

            if(pret) {
               for(int qtd = 1; pret < ret + QTD_MUNICIPIOS && *pret != 0; qtd++) {
                  printf("Registro %d\n", qtd);
                  exibe_mun((Mun *) busca_hash_int(&hashMun, *pret++));
               }
            } 
            else printf("Nenhum retorno!\n")

            free(ret);
            break;
         default:
            printf("INVÁLIDA!!!\n");

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

   /* acessa e retorna município de json  */
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
