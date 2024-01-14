//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "locadora.h"
#include <sys/time.h>
#include <time.h>

int selecaoNaturalDvd(FILE *arq, int tam, FILE *logSelecaoDvd) {
     struct timespec inicioTime, fimTime;
     double tempoGasto;
     clock_t inicioClock, fimClock;

    int pos = 0;
    int quantidadeParticoes = 0;
    int menor = 10000000;
    int posMenor = 0;
    int tamReservatorio = 0;
    int opc = 0;

    TDvd dvd[6];

    int auxDvdVet[6] = {0, 0, 0, 0, 0, 0};


    clock_gettime(CLOCK_MONOTONIC, &inicioTime);
    rewind(arq);

    while (!feof(arq)) {

        FILE *arqReservatorio = fopen("reservatoriod.dat", "wb+");

        if (arqReservatorio == NULL) {
            printf("ERRO AO ABRIR ARQUIVO");
        }

        char nomeParticao[100];
        char nome1[100];
        char nome2[100] = ".dat";

        itoa(quantidadeParticoes, nome1, 10);
        strcat(strcpy(nomeParticao, "selecaoNaturald"), nome1);
        strcat(nomeParticao, nome2);

        FILE *arqParticao = fopen(nomeParticao, "wb+");

        //preenche o vetor com registros do arquivo
        if (opc == 0) {
            for (int i = 0; i < 6; ++i) {

                TDvd *auxDvd = lerDvd(arq);
                pos++;

                dvd[i] = *auxDvd;
                auxDvdVet[i] = auxDvd->id_dvd;
            }
        }

        //fclose(arqReservatorio);

        while (!feof(arq)) {
            for (int i = 0; i < 6; ++i) {
                if (auxDvdVet[i] < menor) {
                    menor = auxDvdVet[i];
                    posMenor = i;
                }
            }

            TDvd *auxDvd = lerDvd(arq);
            pos++;
            if (auxDvd->id_dvd < dvd[posMenor].id_dvd) {
                salvarDvd(auxDvd, arqReservatorio);
                tamReservatorio++;

                if (tamReservatorio == 6) {

                    break;
                }

            } else {
                salvarDvd(&dvd[posMenor], arqParticao);
                auxDvdVet[posMenor] = auxDvd->id_dvd;
                dvd[posMenor] = *auxDvd;
            }

            menor = 999999999;

            if (pos >= tam) {
                break;
            }

        }

        TDvd aux;

        int k, j;

        for (k = 1; k < 6; k++) {

            for (j = 0; j < 6 - 1; j++) {
                if (dvd[j].id_dvd > dvd[j + 1].id_dvd) {
                    aux = dvd[j];
                    dvd[j] = dvd[j + 1];
                    dvd[j + 1] = aux;
                }
            }
        }

        for (int i = 0; i < 6; ++i) {
            salvarDvd(&dvd[i], arqParticao);
        }

        rewind(arqReservatorio);

        for (int i = 0; i < tamReservatorio; ++i) {
            TDvd *auxDvdReservatorio = lerDvd(arqReservatorio);
            dvd[i] = *auxDvdReservatorio;
            auxDvdVet[i] = auxDvdReservatorio->id_dvd;
            opc = 1;
        }


        fclose(arqReservatorio);
        fclose(arqParticao);

        if (pos >= tam) {
            break;
        }

        tamReservatorio = 0;
        quantidadeParticoes++;

    }

    for (int i = 0; i <= quantidadeParticoes; ++i) {

        char nomeParticao[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(i, str1, 10);
        strcat(strcpy(nomeParticao, "selecaoNaturald"), str1);
        strcat(strcpy(nomeParticao, nomeParticao), str2);

        FILE *arqParticao = fopen(nomeParticao, "rb+");
        fclose(arqParticao);
    }

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    //Escrevendo no arquivo de log
    fprintf(logSelecaoDvd, "SELECAO NATURAL DVD - Tempo de execucao em milissegundos: %f\n", tempoGasto);
    fclose(logSelecaoDvd);

    return quantidadeParticoes;

}

int selecaoNaturalCliente(FILE *arq, int tam, FILE *logSelecaoCliente) {
     struct timespec inicioTime, fimTime;
     double tempoGasto;
     clock_t inicioClock, fimClock;

    int pos = 0;
    int quantidadeParticoes = 0;
    int menor = 10000000;
    int posMenor = 0;
    int tamReservatorio = 0;
    int opc = 0;

    TCliente cliente[6];

    int auxClienteVet[6] = {0, 0, 0, 0, 0, 0};


    clock_gettime(CLOCK_MONOTONIC, &inicioTime);
    rewind(arq);

    while (!feof(arq)) {

        FILE *arqReservatorio = fopen("reservatorioc.dat", "wb+");

        if (arqReservatorio == NULL) {
            printf("ERRO AO ABRIR ARQUIVO");
        }

        char nomeParticao[100];
        char nome1[100];
        char nome2[100] = ".dat";

        itoa(quantidadeParticoes, nome1, 10);
        strcat(strcpy(nomeParticao, "selecaoNaturalc"), nome1);
        strcat(nomeParticao, nome2);

        FILE *arqParticao = fopen(nomeParticao, "wb+");

        //preenche o vetor com registros do arquivo
        if (opc == 0) {
            for (int i = 0; i < 6; ++i) {

                TCliente *auxCliente = lerCliente(arq);
                pos++;

                cliente[i] = *auxCliente;
                auxClienteVet[i] = auxCliente->idC;
            }
        }

        //fclose(arqReservatorio);

        while (!feof(arq)) {
            for (int i = 0; i < 6; ++i) {
                if (auxClienteVet[i] < menor) {
                    menor = auxClienteVet[i];
                    posMenor = i;
                }
            }

            TCliente *auxCliente = lerCliente(arq);
            pos++;
            if (auxCliente->idC < cliente[posMenor].idC) {
                salvarCliente(auxCliente, arqReservatorio);
                tamReservatorio++;

                if (tamReservatorio == 6) {

                    break;
                }

            } else {
                salvarCliente(&cliente[posMenor], arqParticao);
                auxClienteVet[posMenor] = auxCliente->idC;
                cliente[posMenor] = *auxCliente;
            }

            menor = 999999999;

            if (pos >= tam) {
                break;
            }

        }

        TCliente aux;

        int k, j;

        for (k = 1; k < 6; k++) {

            for (j = 0; j < 6 - 1; j++) {
                if (cliente[j].idC > cliente[j + 1].idC) {
                    aux = cliente[j];
                    cliente[j] = cliente[j + 1];
                    cliente[j + 1] = aux;
                }
            }
        }

        for (int i = 0; i < 6; ++i) {
            salvarCliente(&cliente[i], arqParticao);
        }

        rewind(arqReservatorio);

        for (int i = 0; i < tamReservatorio; ++i) {
            TCliente *auxDvdReservatorio = lerCliente(arqReservatorio);
            cliente[i] = *auxDvdReservatorio;
            auxClienteVet[i] = auxDvdReservatorio->idC;
            opc = 1;
        }


        fclose(arqReservatorio);
        fclose(arqParticao);

        if (pos >= tam) {
            break;
        }

        tamReservatorio = 0;
        quantidadeParticoes++;

    }

    for (int i = 0; i <= quantidadeParticoes; ++i) {

        char nomeParticao[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(i, str1, 10);
        strcat(strcpy(nomeParticao, "selecaoNaturalc"), str1);
        strcat(strcpy(nomeParticao, nomeParticao), str2);

        FILE *arqParticao = fopen(nomeParticao, "rb+");
        fclose(arqParticao);
    }

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    //Escrevendo no arquivo de log
    fprintf(logSelecaoCliente, "SELECAO NATURAL CLIENTE: Tempo de execucao em milissegundos: %f\n", tempoGasto);
    fclose(logSelecaoCliente);

    return quantidadeParticoes;
}
