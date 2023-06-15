#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serie.h"

int main()
{
    FILE *arq = NULL;
    char c;
    Serie *series;
    Historico *historico;
    int contadorHistorico = 0;
    int contadorDeLinhasArquivo = 0;
    int testaAbertura = 0;
    char nome[50];

    arq = fopen("streaming_dbBinario.dat", "rb");

    if (arq == NULL)
    {
    
        printf("\n\n\n\nDigite o seu nome: ");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = '\0';
        setbuf(stdin, NULL);
        printf("\n\n\n\nBem-vindo, %s ao concorrente da Netflix.", nome);
        
    }
    else
    {
        fclose(arq);
        testaAbertura = 1;
        arq = fopen("streaming_dbBinario.dat", "wb");

        series = (Serie *)malloc(sizeof(Serie) * contadorDeLinhasArquivo);
        fread(series, sizeof(Serie), contadorDeLinhasArquivo, arq);

        fclose(arq);

        arq = fopen("streaming_dbHistoricoBinario.dat", "wb");

        historico = (Historico *)malloc(sizeof(Serie) * contadorDeLinhasArquivo);
        fread(historico, sizeof(historico), contadorHistorico, arq);

        fclose(arq);

        arq = fopen("Tamanhobinario.txt", "w");

        fscanf(arq, "%i", contadorDeLinhasArquivo);

        fclose(arq);
    }
    if (testaAbertura == 0)
    {
        arq = fopen("streaming_db.csv", "r");
        if (arq == NULL)
        {
            printf("Erdsad\n");
            perror("Erro.");
        }
        while ((c = fgetc(arq)) != EOF)
        {
            if (c == '\n')
            {
                contadorDeLinhasArquivo++;
            }
        }
        fclose(arq);
        arq = fopen("streaming_db.csv", "r");
        series = (Serie *)malloc(sizeof(Serie) * contadorDeLinhasArquivo);
        historico = (Historico *)malloc(sizeof(Serie) * contadorDeLinhasArquivo);
        if (series == NULL)
        {
            printf("Erro ao alocar memória para series.1\n");
            perror("Erro.");
        }
        for (int i = 0; i < contadorDeLinhasArquivo; i++)
        {
            char linha[200];
            fgets(linha, sizeof(linha), arq);
            sscanf(linha, "%d, %[^,], %[^,], %d, %[^,], %d, %d, %[^,\n]", &series[i].codigo, series[i].titulo, series[i].genero, &series[i].classificacao, series[i].plataforma,
                   &series[i].duracaoMediaep, &series[i].temporadas, series[i].episodiosPorTemp);
            fflush(NULL);
        }
        fclose(arq);
    }

    int opcao, opcao2;
    char generos[50];
    do
    {
        printf("Menu Séries: ERRO COM BINARIO\n");
        printf("1. Cadastrar série\n");
        printf("2. Listar séries\n");
        printf("3. Excluir série\n");
        printf("4. Modificar série\n");
        printf("5. Salvar alterações\n");
        printf("6. Pesquisar série\n");
        printf("7. Listar por genero.\n");
        printf("0. Histórico\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarSerie(&contadorDeLinhasArquivo, &series);
            break;
        case 2:
            listarSeries(contadorDeLinhasArquivo, series);
            break;
        case 3:
            excluirSeries(&contadorDeLinhasArquivo, &series);
            break;
        case 4:
            modificarSerie(contadorDeLinhasArquivo, series);
            break;
        case 5:
            salvarAlteracoes(contadorDeLinhasArquivo, series);
            break;
        case 6:
            pesquisaSerieSerie(contadorDeLinhasArquivo, series);
            break;
        case 7:
            visualizarSeriesPorGenero(contadorDeLinhasArquivo, series);
            break;
        case 0:
            printf("Acessando o menu Histórico...\n");

            printf("\nMenu Histórico:\n");
            printf("1. Cadastrar histórico\n");
            printf("2. Listar histórico\n");
            printf("3. Excluir histórico\n");
            printf("4. Modificar histórico\n");
            printf("5. Voltar para Séries\n");
            printf("0. Finalizar Programa\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            printf("\n");
            switch (opcao)
            {
            case 1:
                cadastrarHistorico(&contadorHistorico, &historico, series, contadorDeLinhasArquivo);
                break;
            case 2:
                listarHistorico(contadorHistorico, historico);
                break;
            case 3:
                excluirHistorico(&contadorHistorico, historico);
                break;
            case 4:
                modificarHistorico(contadorHistorico, historico);
                break;
            case 5:
                printf("Programa Finalizado.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
            }

        default:
            break;
        }

        printf("\n");

    } while (opcao != 0);

    arq = fopen("streaming_dbBinario.dat", "wb");

    fwrite(series, sizeof(Serie), contadorDeLinhasArquivo, arq);

    fclose(arq);

    arq = fopen("streaming_dbHistoricoBinario.dat", "wb");

    fwrite(historico, sizeof(historico), contadorHistorico, arq);

    fclose(arq);

    arq = fopen("Tamanhobinario.txt", "w");

    fprintf(arq, "%i", contadorDeLinhasArquivo);

    fclose(arq);

    free(series);
    free(historico);

    return 0;
}
