#include <stdio.h>
#include <stdlib.h>
#include "../include/mun.h"
#include "../include/avl.h"
#include "../include/jsense.h"

#define QTD_MUNICIPIOS 5570

Mun * acessa_mun_json(JSENSE * arq, int pos);

int main() {
	JSENSE * arq = jse_from_file("./files/municipios.json");

	Arv arvMunNome;
	constroi_avl(&arvMunNome, cmp_str);

	Arv arvMunLat;
	constroi_avl(&arvMunLat, cmp_double);

	Arv arvMunLon;
	constroi_avl(&arvMunLon, cmp_double);

	Arv arvMunUF;
	constroi_avl(&arvMunUF, cmp_int);

	Arv arvMunDDD;
	constroi_avl(&arvMunDDD, cmp_int);

	for(int i = 0; i < QTD_MUNICIPIOS; i++) {
        Mun * mun = acessa_mun_json(arq, i);
		insere_avl(&arvMunNome, &mun->nome, mun->cod_ibge);
		insere_avl(&arvMunLat, &mun->coord[0], mun->cod_ibge);
		insere_avl(&arvMunLon, &mun->coord[1], mun->cod_ibge);
		insere_avl(&arvMunUF, &mun->cod_uf, mun->cod_ibge);
		insere_avl(&arvMunDDD, &mun->ddd, mun->cod_ibge);
	}

    int op;

    do {
        printf("----------------------------------------------------\n");
        printf("INFORME\n");
        printf("Busca de munícipios por\n");
        printf("1 - Nome\n");
        printf("2 - Latitude\n");
        printf("3 - Longitude\n");
        printf("4 - UF\n");
        printf("5 - DDD\n");
        printf("0 - Encerrar\n");
        printf("\nOpção: ");
        scanf("%d", &op);

        Reg * aux;

        printf("\n");

        switch(op) {
            case 0:
                printf("Encerrando execução...\n");
            break;
            case 1:
                char nome[35];

                printf("Nome: ");
                scanf(" %[^\n]", nome);

                aux = busca_avl(&arvMunNome, nome);
                
                printf("\n");

                while(aux) {
                    printf("IBGE: %d -> %s\n", aux->cod_ibge, (char *) aux->chave);
                    aux = aux->prox;
                }
            break;
            case 2:
                double lat;

                printf("Latitude: ");
                scanf("%lf", &lat);

                aux = busca_avl(&arvMunLat, &lat);

                printf("\n");

                while(aux) {
                    printf("IBGE: %d -> %lf\n", aux->cod_ibge, *((double *) aux->chave));
                    aux = aux->prox;
                }
            break;
            case 3:
                double lon;

                printf("Longitude: ");
                scanf("%lf", &lon);

                aux = busca_avl(&arvMunLon, &lon);
                
                printf("\n");

                while(aux) {
                    printf("IBGE: %d -> %lf\n", aux->cod_ibge, *((double *) aux->chave));
                    aux = aux->prox;
                }
            break;
            case 4:
                int uf;

                printf("UF: ");
                scanf("%d", &uf);

                aux = busca_avl(&arvMunUF, &uf);

                printf("\n");

                while(aux) {
                    printf("IBGE: %d -> %d\n", aux->cod_ibge, *((int *) aux->chave));
                    aux = aux->prox;
                }
            break;
            case 5:
                int ddd;

                printf("DDD: ");
                scanf("%d", &ddd);

                aux = busca_avl(&arvMunDDD, &ddd);
                
                printf("\n");

                while(aux) {
                    printf("IBGE: %d -> %d\n", aux->cod_ibge, *((int *) aux->chave));
                    aux = aux->prox;
                }
            break;
            default:
                printf("INVÁLIDA!!!\n");
        }
    } while(op != 0);
    
    libera_avl(&arvMunNome);
    libera_avl(&arvMunLat);
    libera_avl(&arvMunLon);
    libera_avl(&arvMunUF);
    libera_avl(&arvMunDDD);

    jse_free(arq);

    return EXIT_SUCCESS;
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
