#include <stdio.h>
#include <stdlib.h>
#include "../include/mun.h"
#include "../include/avl.h"
#include "../include/jsense.h"

#define QTD_MUNICIPIOS 5570

Mun * acessa_mun_json(JSENSE * arq, int pos);
void menu(int * op);

int main() {
	JSENSE * arq = jse_from_file("./files/municipios.json");

	Arv arvMunLat;
	constroi_avl(&arvMunLat, cmp_double);

	Arv arvMunLon;
	constroi_avl(&arvMunLon, cmp_double);

	Arv arvMunDDD;
	constroi_avl(&arvMunDDD, cmp_int);

	for(int i = 0; i < QTD_MUNICIPIOS; i++) {
        Mun * mun = acessa_mun_json(arq, i);
		insere_avl(&arvMunLat, &mun->coord[0], mun->cod_ibge);
		insere_avl(&arvMunLon, &mun->coord[1], mun->cod_ibge);
		insere_avl(&arvMunDDD, &mun->ddd, mun->cod_ibge);
	}

    int op;

    do {
        menu(&op);

        if(op == 1) {
            int eq;
            int * ret;
            int * lats, * lons, * ddds;

            for(int i = 1; i <= 3; i++) {
                printf("\n");

                switch(i) {
                    case 1:
                        double lat;

                        printf("Latitude: ");
                        scanf("%lf", &lat);

                        printf("\n0 - Igual\n1 - Maior\n2 - Menor\n\n");
                        scanf("%d", &eq);

                        eq = (eq == 2) ? -1 : eq;

                        lats = query_simp_avl(&arvMunLat, &lat, eq);
                    break;
                    case 2:
                        double lon;

                        printf("Longitude: ");
                        scanf("%lf", &lon);

                        printf("\n0 - Igual\n1 - Maior\n2 - Menor\n\n");
                        scanf("%d", &eq);

                        eq = (eq == 2) ? -1 : eq;

                        lons = query_simp_avl(&arvMunLon, &lon, eq);
                    break;
                    case 3:
                        int ddd;

                        printf("DDD: ");
                        scanf("%d", &ddd);

                        printf("\n0 - Igual\n1 - Maior\n2 - Menor\n\n");
                        scanf("%d", &eq);

                        eq = (eq == 2) ? -1 : eq;

                        ddds = query_simp_avl(&arvMunDDD, &ddd, eq);
                    break;
                }
            }
            
            ret = query_comb_avl(lats, lons);
            ret = query_comb_avl(ret, ddds);

            int qtd = 0;
            for(int * pret = ret; pret < ret + QTD_MUNICIPIOS && *pret != 0; pret++) printf("%d: %d\n", ++qtd, *pret);
            
            free(ret);
        }
        else if(op == 0) printf("Encerrando execução...\n");
        else printf("INVÁLIDA!!!\n");

    } while(op != 0);
    
    libera_avl(&arvMunLat);
    libera_avl(&arvMunLon);
    libera_avl(&arvMunDDD);

    jse_free(arq);

    return EXIT_SUCCESS;
}

//menu
void menu(int * op) {
    printf("----------------------------------------------------\n");
    printf("INFORME\n");
    printf("Busca de munícipios por queries\n");
    printf("0 - Encerrar\n");
    printf("1 - Realizar\n");
    printf("\nOpção: ");
    scanf("%d", op);
}

//informe o json JSENSE e a posição do município no arquivo
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
    double latitude, longitude;

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
