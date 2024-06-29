#include <stdio.h>
#include <stdlib.h>
#include "include/mun.h"
#include "include/avl.h"
#include "include/range_query.h"
#include "include/hash_int.h"
#include "include/jsense.h"

#define QTD_MUNICIPIOS 5570
#define TAM_HASH 11139
#define N_CAMPOS 5

typedef int boolean;
#define SIM 1
#define NAO 0

void menu_inicial(int * op); //menu que encerra ou continua execução do programa
Mun * acessa_mun_json(JSENSE * arq, int pos); //declaração da função que retorna município do json

int main() {
   JSENSE * arq = jse_from_file("./file/municipios.json"); //abertura do arquivo json

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

   /* instanciação da tabela hash */
   HashInt hashMun;
   constroi_hash_int(&hashMun, TAM_HASH, get_key_mun);

   /*
    * busca dos municípios no json
    * inserção das chaves com código em sua árvore
    * e adição de todos na tabela hash, como chave tendo código ibge
    * */
   for(int i = 0; i < QTD_MUNICIPIOS; i++) {
      Mun * mun = acessa_mun_json(arq, i);
      insere_avl(&arvMunNome, &mun->nome, mun->cod_ibge);
      insere_avl(&arvMunLat, &mun->coord[0], mun->cod_ibge);
      insere_avl(&arvMunLon, &mun->coord[1], mun->cod_ibge);
      insere_avl(&arvMunUF, &mun->cod_uf, mun->cod_ibge);
      insere_avl(&arvMunDDD, &mun->ddd, mun->cod_ibge);
      insere_hash_int(&hashMun, mun);
   }

   /* conjunto de todas as árvores  */
   ArvAVL * jungle[N_CAMPOS] = {&arvMunNome, &arvMunLat, &arvMunLon, &arvMunUF, &arvMunDDD};

   printf("Busca de munícipios por range query\n");

   boolean continuar;
   do {
      menu_inicial(&continuar);

      switch(continuar) {
         case NAO:
            printf("-----------------------------------\n");
            printf("Execução encerrada.\n");
            break;
         case SIM:
            /* campos para armazenar queries  */
            int * nomes = NULL;
            int * lats = NULL;
            int * lons = NULL;
            int * ufs = NULL;
            int * ddds = NULL;

            int * campos[N_CAMPOS] = {nomes, lats, lons, ufs, ddds}; //conjunto dos campos
            int * res = NULL; //ponteiro para armazenar resultado

            /* ponteiros de ponteiro para manipulação  */
            int ** auxpp = campos;
            int ** ppres = &res; 

            /* nomes dos campos */
            char * labels[N_CAMPOS] =
            {
               "Nome",
               "Latitude",
               "Longitude",
               "UF",
               "DDD"
            };

            boolean op; //escolher se campo será buscado
            Faixa eq; //definir tipo de intervalo

            for(int i = 0; i < N_CAMPOS; i++) {
               menu_escolha(labels[i], &op);

               switch(op) {
                  case SIM:
                     if(jungle[i]->tipo != STR) menu_range(&eq); //chamada de intervalo apenas caso não seja string
                     else eq = IGUAL;

                     campos[i] = query(jungle[i], eq, QTD_MUNICIPIOS); //campo armazena retorno da query
                     *ppres = comb_query(*auxpp, campos[i], QTD_MUNICIPIOS); //resultado prévio e final já são armazenados

                     auxpp = ppres; //auxiliar agora aponta para resultado, assim combinando suas queries

                     free(campos[i]); //liberação do campo da iteração
                     break;
                  case NAO:
                     if(*auxpp == campos[i]) auxpp++; //auxiliar permanece apontando para os campos
                     break;
                  default:
                     printf("!!!INVÁLIDA!!!\n");
               }
            }

            if(res) { //exibição dos municípios encontrados
               int qtd = 0;
               for(int * pres = res; pres < res + QTD_MUNICIPIOS && *pres != 0; pres++) {
                  printf("-----------------------------------\n");
                  exibe_mun((Mun *) busca_hash_int(&hashMun, *pres)); //busca na hash a partir do código armazenado no resultado
                  printf("-----------------------------------\n");

                  qtd++;
               }

               printf("Municípios encontrados: %d\n", qtd);
            } 
            else printf("Nenhum município encontrado!\n");

            /* desalocação do resultado */
            free(res);
            break;
         default:
            printf("!!!INVÁLIDA!!!\n");
      }

   } while(continuar);

   /* desalocação de todas as estruturas  */
   libera_avl(&arvMunNome);
   libera_avl(&arvMunLat);
   libera_avl(&arvMunLon);
   libera_avl(&arvMunUF);
   libera_avl(&arvMunDDD);
   libera_hash_int(&hashMun);

   jse_free(arq); //liberação do arquivo json

   return EXIT_SUCCESS;
}

void menu_inicial(int * op) { 
   printf("-----------------------------------\n");
   printf("\n");

   printf("[0] Encerrar\n");
   printf("[1] Continuar\n");
   printf("\n--> ");
   scanf("%d", op);

   *op = (*op == 1) ? *op : 0;

   printf("\n");
}

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
