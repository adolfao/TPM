#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serie.h"

Serie *series;
Historico *historico;

void cadastrarSerie(int *contadorSeries, Serie **series)
{
    Serie novaSerie;
    novaSerie.codigo = *contadorSeries + 2;
    setbuf(stdin, NULL);
    printf("TITU: ");
    fgets(novaSerie.titulo, 50, stdin);
    novaSerie.titulo[strcspn(novaSerie.titulo, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("genero: ");
    fgets(novaSerie.genero, 50, stdin);
    novaSerie.genero[strcspn(novaSerie.genero, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("classificacao: ");
    scanf("%d", &novaSerie.classificacao);
    setbuf(stdin, NULL);

    printf("Plataforma: ");
    fgets(novaSerie.plataforma, 50, stdin);
    novaSerie.plataforma[strlen(novaSerie.plataforma) - 1] = '\0';
    setbuf(stdin, NULL);

    printf("Temporadas: ");
    scanf("%d", &novaSerie.temporadas);

    printf("número de episódios por temporada:\n");
    for (int j = 0; j < novaSerie.temporadas; j++)
    {
        printf("Temporada %d: ", j + 1);
        setbuf(stdin, NULL);
        char episodios[100];
        setbuf(stdin, NULL);
        fgets(episodios, 100, stdin);
        episodios[strcspn(episodios, "\n")] = '\0';
        strcat(novaSerie.episodiosPorTemp, episodios);
        strcat(novaSerie.episodiosPorTemp, " ");
        setbuf(stdin, NULL);
    }

    printf("Duração média dos episódios (em minutos): ");
    scanf("%d", &novaSerie.duracaoMediaep);
    (*contadorSeries)++;
    *series = (Serie *)realloc(*series, (*contadorSeries) * sizeof(Serie));
    if (*series == NULL)
    {
        printf("Erro ao alocar memória para a serie.\n");
        perror("Erro.");
        return;
    }
    for (int i = 0; i < *contadorSeries; i++)
    {
        if ((*series)[i].codigo == -1)
        {
            (*series)[i] = novaSerie;
            (*contadorSeries)--;
        }
        else
        {
            (*series)[*contadorSeries - 1] = novaSerie;
        }
    }
}

void listarSeries(int contador, Serie *series)
{
    setbuf(stdin, NULL);
    printf("Lista de series:\n");
    for (int i = 0; i < contador; i++)
    {
        if (series[i].codigo == -1)
        {
            printf("Serie apagada.");
            continue;
        }
        else
        {
            printf("codigo: %d\n", series[i].codigo);
            printf("nome: %s\n", series[i].titulo);
            printf("genero: %s\n", series[i].genero);
            printf("classificacao: %d\n", series[i].classificacao);
            printf("plataforma: %s\n", series[i].plataforma);
            printf("duracao media: %d\n", series[i].duracaoMediaep);
            printf("temporadas: %d\n", series[i].temporadas);
            printf("Quantidade de ep por temporada: %s\n", series[i].episodiosPorTemp);
            printf("\n");
        }
    }
}

void excluirSeries(int *contadorSeries, Serie **series)
{
    setbuf(stdin, NULL);
    char apaga[50];
    printf("Digite o TITU da serie que deseja excluir: ");
    scanf("%s", apaga);

    for (int i = 0; i < *contadorSeries; i++)
    {
        if (strcmp(apaga, (*series)[i].titulo) == 0)
        {
            (*series)[i].codigo = -1;
            printf("serie excluída com sucesso.\n");
            return;
        }
    }

    printf("serie não encontrada.\n");
}

void modificarSerie(int contador, Serie **series)
{
    setbuf(stdin, NULL);
    char modifica[50];
    printf("Digite o TITU da serie que deseja modificar: ");
    fgets(modifica, 50, stdin);
    modifica[strcspn(modifica, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < contador; i++)
    {
        if (strcmp(modifica, (*series)[i].titulo) == 0)
        {
            Serie serieModificada;

            setbuf(stdin, NULL);
            serieModificada.codigo = (*series)[i].codigo;
            setbuf(stdin, NULL);
            printf("Novo TITULO: ");
            fgets(serieModificada.titulo, 50, stdin);
            serieModificada.titulo[strcspn(serieModificada.titulo, "\n")] = '\0';
            setbuf(stdin, NULL);

            printf("Novo genero: ");
            fgets(serieModificada.genero, 50, stdin);
            serieModificada.genero[strcspn(serieModificada.genero, "\n")] = '\0';
            setbuf(stdin, NULL);

            printf("Nova classificacao: ");
            scanf("%d", &serieModificada.classificacao);
            setbuf(stdin, NULL);

            setbuf(stdin, NULL);
            printf("Nova plataforma: ");
            fgets(serieModificada.plataforma, 50, stdin);
            serieModificada.plataforma[strcspn(serieModificada.plataforma, "\n")] = '\0';
            setbuf(stdin, NULL);

            printf("Novo número de temporadas: ");
            scanf("%d", &serieModificada.temporadas);
            setbuf(stdin, NULL);

            *serieModificada.episodiosPorTemp = (char *)malloc(serieModificada.temporadas * 50);

            printf("Novo número de episódios por temporada:\n");
            for (int j = 0; j < serieModificada.temporadas; j++)
            {
                printf("Temporada %d: ", j + 1);
                setbuf(stdin, NULL);
                char episodios[100];
                setbuf(stdin, NULL);
                fgets(episodios, 100, stdin);
                episodios[strcspn(episodios, "\n")] = '\0';
                strcat(serieModificada.episodiosPorTemp, episodios);
                strcat(serieModificada.episodiosPorTemp, " ");
                setbuf(stdin, NULL);
            }

            printf("Nova duração média dos episódios: ");
            scanf("%d", &serieModificada.duracaoMediaep);
            setbuf(stdin, NULL);

            (*series)[i] = serieModificada;
            printf("serie modificada com sucesso!\n");
            return;
        }
    }

    printf("serie não encontrada.\n");
}

void pesquisaSerieSerie(int contador, Serie *series)
{
    setbuf(stdin, NULL);
    char string[30];
    int achouSeriePESQUISAR = 0;
    int naoachouSeriePESQUISAR = 0;
    int escolhaPESQUISAR = 0;

    printf("Você escolheu pesquisar uma serie em nossa base de dados!\n");
    printf("  - Digite \"1\" se quiser continuar para a pesquisa de uma serie;\n");
    printf("  - Digite \"0\" Se quiser voltar ao menu de ações de histórico.\n");
    printf("Digite a opção escolhida:");
    scanf("%d", &escolhaPESQUISAR);
    setbuf(stdin, NULL);
    if (escolhaPESQUISAR == 0)
    {
        printf("Você escolheu retornar ao menu de ações de series.\n");
        return;
    }

    do
    {
        printf("Para pesquisar, digite o nome de uma serie:");
        fgets(string, 30, stdin);
        string[strcspn(string, "\n")] = '\0';
        setbuf(stdin, NULL);
        for (int i = 0; i < (contador); i++)
        {
            if (strcasecmp(string, series[i].titulo) == 0)
            {
                if (series[i].classificacao == -1)
                {
                    printf("A serie \"%s\" foi excluída anteriormente.\n", series[i].titulo);
                }
                printf("- \"%s\", possui %d temporadas e uma duração média de episódio de %d minutos.\n",
                       series[i].titulo, series[i].temporadas, series[i].duracaoMediaep);
                achouSeriePESQUISAR++;
            }
        }

        if (achouSeriePESQUISAR == 0)
        {
            printf("Não foi possível localizar a serie, pesquise novamente.\n");
            naoachouSeriePESQUISAR++;
        }

        if (naoachouSeriePESQUISAR == 3)
        {
            printf("As series pesquisadas não foram encontradas, tente novamente mais tarde.\n");
            return;
        }

    } while (achouSeriePESQUISAR == 0);

    naoachouSeriePESQUISAR = 0;
    achouSeriePESQUISAR = 0;
}

void salvarAlteracoes(int contadorSeries, Serie *series)
{
    setbuf(stdin, NULL);
    FILE *arq;
    arq = fopen("streaming_db.csv", "w");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        perror("Erro.");
        return;
    }

    for (int i = 0; i < contadorSeries; i++)
    {
        if (series[i].codigo == -1)
        {
            continue;
        }
        fprintf(arq, "%d,%s,%s,%d,%s,%d,%d,%s\n", series[i].codigo, series[i].titulo, series[i].genero, series[i].classificacao, series[i].plataforma, series[i].duracaoMediaep, series[i].temporadas, series[i].episodiosPorTemp);
    }

    fclose(arq);
}

void visualizarSeriesPorGenero(int contadorSeries, Serie *series)
{
    char genero[50];
    setbuf(stdin, NULL);
    printf("Digite o genero que deseja filtrar.\n");
    scanf("%49[^\n]%*c", &genero);

    printf("series do genero %s:\n", genero);
    int encontradas = 0;

    for (int i = 0; i < contadorSeries; i++)
    {
        if (strcmp(series[i].genero, genero) == 0)
        {
            encontradas++;
            printf("TITULO: %s\n", series[i].titulo);
            printf("genero: %s\n", series[i].genero);
            printf("classificacao: %d\n", series[i].classificacao);
            printf("------------------------------\n");
        }
    }

    if (encontradas == 0)
    {
        printf("Nenhuma serie encontrada para o genero %s.\n", genero);
    }
}

void cadastrarHistorico(int *contadorHistorico, Historico **historico, Serie *series, int contadorSeries)
{
    setbuf(stdin, NULL);
    Historico novoHistorico;

    printf("nome da serie: ");
    fgets(novoHistorico.nomeSerie, 50, stdin);
    novoHistorico.nomeSerie[strcspn(novoHistorico.nomeSerie, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("ultima temporada assistida: ");
    scanf("%d", &novoHistorico.ultimaTempAssistida);

    printf("ultimo episódio assistido: ");
    scanf("%d", &novoHistorico.ultimoEpAssistido);

    for (int i = 0; i < contadorSeries; i++)
    {
        if (strcmp(novoHistorico.nomeSerie, series[i].titulo) == 0)
        {
            strcpy(novoHistorico.genero, series[i].genero);
            novoHistorico.classificacao = series[i].classificacao;
            break;
        }
    }

    (*contadorHistorico)++;
    Historico *temp = (Historico *)realloc(*historico, (*contadorHistorico) * sizeof(Historico));
    if (temp == NULL)
    {
        printf("Erro ao alocar memória para o histórico.\n");
        perror("Erro.");
        return;
    }
    *historico = temp;
    int teste = 0;
    for (int i = 0; i < *contadorHistorico - 1; i++)
    {
        if ((*historico)[i].ultimaTempAssistida == -1)
        {
            (*historico)[i] = novoHistorico;
            (*contadorHistorico)--;
            teste = 1;
            break;
        }
    }

    if (teste == 0)
    {
        (*historico)[*contadorHistorico - 1] = novoHistorico;
    }
}


void listarHistorico(int contador, Historico *historico)
{
    setbuf(stdin, NULL);
    printf("Histórico de series:\n");
    for (int i = 0; i < contador; i++)
    {
        if (historico[i].ultimaTempAssistida == -1)
        {
            printf("serie apagada do histórico.\n");
            continue;
        }
        else
        {
            printf("nome da serie: %s\n", historico[i].nomeSerie);
            printf("ultima temporada assistida: %d\n", historico[i].ultimaTempAssistida);
            printf("ultimo episodios assistido: %d\n", historico[i].ultimoEpAssistido);
            printf("genero: %s\n", historico[i].genero);
            printf("classificacao etaria: %d\n", historico[i].classificacao);
            printf("\n");
        }
    }
}

void excluirHistorico(int *contadorHistorico, Historico *historico)
{
    setbuf(stdin, NULL);
    char nomeSerie[50];
    setbuf(stdin, NULL);
    printf("nome da serie a ser excluída do histórico: ");
    fgets(nomeSerie, 50, stdin);
    nomeSerie[strcspn(nomeSerie, "\n")] = '\0';
    setbuf(stdin, NULL);

    int excluido = 0;
    for (int i = 0; i < *contadorHistorico; i++)
    {
        if (strcmp(nomeSerie, historico[i].nomeSerie) == 0)
        {
            historico[i].ultimaTempAssistida = -1;
            historico[i].ultimoEpAssistido = -1;
            excluido = 1;
            break;
        }
    }

    if (excluido)
    {
        printf("serie excluída do histórico.\n");
    }
    else
    {
        printf("serie não encontrada no histórico.\n");
    }
}

void modificarHistorico(int contador, Historico *historico)
{
    setbuf(stdin, NULL);
    char nomeSerie[50];
    setbuf(stdin, NULL);
    printf("nome da serie a ser modificada: ");
    fgets(nomeSerie, 50, stdin);
    nomeSerie[strcspn(nomeSerie, "\n")] = '\0';
    setbuf(stdin, NULL);

    int encontrado = 0;
    for (int i = 0; i < contador; i++)
    {
        if (strcmp(nomeSerie, historico[i].nomeSerie) == 0)
        {
            printf("Digite a nova temporada assistida: ");
            scanf("%d", &historico[i].ultimaTempAssistida);

            printf("Digite o novo episódio assistido: ");
            scanf("%d", &historico[i].ultimoEpAssistido);

            encontrado = 1;
            break;
        }
    }

    if (encontrado)
    {
        printf("Histórico da serie modificado.\n");
    }
    else
    {
        printf("serie não encontrada no histórico.\n");
    }
}
