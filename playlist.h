#ifndef playlist_H
#define playlist_H

#define SUCESSO 0
#define PLAYLIST_VAZIA 1
#define FALTOU_MEMORIA 2
#define MUSICA_INEXISTENTE 3
#define HISTORICO_VAZIO 4


typedef struct {
	char titulo[50];
	char artista[50];
	float duracao;
}Musica;

typedef struct nodo Nodo;

struct nodo {
	Musica info;
	Nodo *ant;
	Nodo *prox;
};

typedef struct {
	Nodo *inicio;
	Nodo *fim;
	int n;
}ListaDE;

typedef struct {
	Nodo *topo;
}PilhaSE;

void criaLista(ListaDE *lt);
void criaPilha(PilhaSE *p);
int adicionarMusicaTopo(ListaDE *lt, Musica m);
int adicionarMusicaFinal(ListaDE *lt, Musica m); 
int personalizarMusica(ListaDE *lt, char titulo[50], char artista[50], Musica m); 
int pularFaixa(ListaDE *lt, PilhaSE *p, Musica *m); 
int tocarFaixa(ListaDE *lt, PilhaSE *p, char titulo[50], char artista[50], Musica *m); 
int remover(ListaDE *lt, char titulo[50], char artista[50]); 
int estaVazia(ListaDE lt);
void exibePlaylist(ListaDE lt, PilhaSE p); 
int limpaPlaylist(ListaDE *lt);
void empilhaHistorico(PilhaSE *p, Nodo *n);
int desempilhaHistorico(PilhaSE *p, ListaDE *lt);
int limpaHistorico(PilhaSE *p);
void salvarPlaylist(ListaDE *lt, char *nomeArquivo);
int carregarPlaylist(ListaDE *lt, char *nomeArquivo);
void salvarHistorico(PilhaSE *p, char *nomeArquivo);
int carregarHistorico(PilhaSE *p, char *nomeArquivo);

#endif
