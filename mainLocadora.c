#include <stdio.h>
#include <stdlib.h>
#include "locadora.c"

int main() {

    FILE *arqClientes, *arqDvds, *arqLocadora, *arqFuncionarios;
    TCliente *cliente;
    TDvd *dvd;
    TLocadora *locacao;


    if ((arqClientes = fopen("clientes.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arqDvds = fopen("Dvds.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arqLocadora = fopen("locadora.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }


    criarBaseDvd(arqDvds, 10);
    criarBaseCliente(arqClientes, 10);
    criarBaseLocadora(arqLocadora, arqClientes, arqDvds, 3);
    int gerador_id_locadora = 3;

    int opcao = -1,
            gerador_id_dvd = 1,
            gerador_id_cliente = 1,c;


    while (opcao != 0) {
        system("clear");
        printf("\n***************************** LOCADORA TAGEO  ********************************");
        printf("\n1. Cadastrar DVD \n2. Buscar DVD \n3. Excluir DVD \n4. Imprimir todos os DVDs \n-----------------------------\n"
               "5. Cadastrar cliente \n6. Buscar cliente \n7. Excluir cliente \n8. Imprimir todos os clientes \n-----------------------------"
               "\n9. Alugar DVD\n10. Buscar locacao \n11. Imprimir todas as locacoes\n12. Devolver DVD\n---------------------------\n0. Sair\n\nEscolha uma opção: ");
        scanf("%d", &opcao);
        //fflush(arq);

        switch (opcao) {
            case 1:
                system("clear");
                printf("\n************************* CADASTRAR DVD *******************************\n");

                dvd = (TDvd *) malloc(sizeof(TDvd));

                // Limpar o buffer, consumindo o caractere de nova linha remanescente
                while (getchar() != '\n');

                dvd->id_dvd = 10 + gerador_id_dvd;
                gerador_id_dvd++;

                printf("ID: %d", dvd->id_dvd);

                printf("\nTítulo: ");
                fgets(dvd->nome_dvd, 100, stdin);

                printf("Gênero: ");
                fgets(dvd->genero, 100, stdin);

                dvd->emprestimo = 0;

                salvarDvd(dvd, arqDvds);
                printf("\nDVD salvo com sucesso!");
                opcao = -1;

                free(dvd);
                break;
            case 2:
                printf("\n**************************** BUSCAR DVD ******************************\n");

                int id_dvd;

                printf("Informe o codigo: ");
                scanf("%d", &id_dvd);

                dvd = buscaSequencialDvds(id_dvd, arqDvds, "buscaDvds-log.txt");
                if (dvd != NULL) {
                    imprimeDvd(dvd);
                } else {
                    printf("DVD não encontrado.");
                }

                free(dvd);
                break;
            case 3:
                printf("\n**************************** EXCLUIR DVD ****************************\n");

                printf("Informe o codigo: ");
                scanf("%d", &id_dvd);

                excluiDvd(id_dvd, arqDvds);

                break;
            case 4:
                printf("\n********************** IMPRIMIR BASE DE DADOS DE DVDs ************************\n");
                imprimirBaseDvd(arqDvds);
                break;
            case 5:
                system("clear");
                printf("\n****************** CADASTRAR CLIENTE ************************\n");

                cliente = (TCliente *) malloc(sizeof(TCliente));

                // Limpar o buffer, consumindo o caractere de nova linha remanescente
                while ((c = getchar()) != '\n' && c != EOF);

                cliente->idC = 10 + gerador_id_cliente;
                gerador_id_cliente++;

                printf("ID: %d", cliente->idC);

                printf("\nNome: ");
                fgets(cliente->nomeC, 100, stdin);

                printf("\nData nascimento: ");
                fgets(cliente->dataNascimentoC, 49, stdin);

                printf("CPF: ");
                fgets(cliente->cpfC, 49, stdin);

                printf("Telefone: ");
                fgets(cliente->telefoneC, 49, stdin);

                salvarCliente(cliente, arqClientes);
                printf("\nCliente salvo com sucesso!");
                opcao = -1;

                free(cliente);

                break;
            case 6:
                printf("\n******************* BUSCAR CLIENTE *******************\n");

                int id_cliente;

                printf("Informe o codigo: ");
                scanf("%d", &id_cliente);

                cliente = buscaSequencialCliente(id_cliente, arqClientes, "clientes-log.txt");
                if (cliente != NULL) {
                    imprimeCliente(cliente);
                } else {
                    printf("Cliente não encontrado.");
                }

                free(cliente);
                break;
            case 7:
                printf("\n**************************** EXCLUIR CLIENTE ****************************\n");

                printf("Informe o codigo: ");
                scanf("%d", &id_cliente);

                excluiCliente(id_cliente, arqClientes);
                break;
            case 8:
                printf("\n****************** IMPRIMIR BASE DE DADOS DE CLIENTES ********************\n");
                imprimirBaseCliente(arqClientes);
                break;
            case 9:
                printf("\n*************************** ALUGAR DVD **************************");

                gerador_id_locadora++;
                alugaDvd(gerador_id_locadora, arqClientes, arqDvds, arqLocadora);

                //imprimirDvdAlugado(arqLocadora, arqDvds, arqClientes);

                break;
            case 10:
                printf("*************************** BUSCAR LOCACAOO ********************************");
                int id_locacao;

                printf("\nInforme o codigo da locacao: ");
                scanf("%d", &id_locacao);

                locacao = buscaBinariaLocacao(id_locacao, arqLocadora, 0, tamanho_arquivo(arqLocadora)-1);

                if (locacao != NULL) {
                    imprimeLocadora(locacao);
                } else
                    printf("Locacao não encontrada.");
                break;
            case 11:
                printf("\n********************** IMPRIMIR TODAS AS LOCACOES *************************\n");
                imprimirBaseLocadora(arqLocadora);
                break;
            case 12:
                printf("\n********************** DEVOLVER DVD *************************\n");
                devolverDvd(arqDvds);
                break;
        }
    }
}