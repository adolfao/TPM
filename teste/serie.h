#ifndef SERIES_H
#define SERIES_H

typedef struct {
    int codigo;
    char titulo[50];
    char genero[50];
    int classificacao;
    char plataforma[50];
    int temporadas;
    char episodiosPorTemp[100];
    int duracaoMediaep;
} Serie;
typedef struct {
    char nomeSerie[50];
    int ultimaTempAssistida;
    int ultimoEpAssistido;
    char genero[50];
    int classificacao;
} Historico;

void cadastrarSerie(int *contadorSeries, Serie **series);
void listarSeries(int contador, Serie *series);
void excluirSeries(int *contadorSeries, Serie **series);
void modificarSerie(int contador, Serie **series);
void pesquisaSerieSerie(int contador, Serie* series);
void salvarAlteracoes(int contadorSeries, Serie *series);
void visualizarSeriesPorGenero(int contadorSeries, Serie *series);

void cadastrarHistorico(int *contadorHistorico, Historico **historico, Serie *series, int contadorSeries);
void listarHistorico(int contador, Historico *historico);
void excluirHistorico(int *contadorHistorico, Historico *historico);
void modificarHistorico(int contador, Historico *historico);


#endif
