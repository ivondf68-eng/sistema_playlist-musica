#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"

void criaLista(ListaDE *lt){
	lt->inicio = NULL;
	lt->fim = NULL;
	lt->n = 0;
}

void criaPilha(PilhaSE *p){
	p->topo = NULL;
}

int adicionarMusicaTopo(ListaDE *lt, Musica m){ 
	Nodo *pNodo;
	pNodo = (Nodo *) malloc (sizeof (Nodo));
	if(pNodo == NULL){
		return FALTOU_MEMORIA;
	}
	else{
		pNodo->info = m;
		pNodo->prox = lt->inicio;
		pNodo->ant = NULL;
		
		if(lt->n == 0){
			lt->fim = pNodo;
		}
		else{
			lt->inicio->ant = pNodo;
		}
		lt->inicio = pNodo;
		lt->n++;
		return SUCESSO;
	}
}

int adicionarMusicaFinal(ListaDE *lt, Musica m){ 
	Nodo *pNodo;
	pNodo = (Nodo *) malloc (sizeof (Nodo));
	if(pNodo == NULL){
		return FALTOU_MEMORIA;
	}
	else{
		pNodo->info = m;
		pNodo->prox = NULL;
		pNodo->ant = lt->fim;
		if(lt->n == 0){
			lt->inicio = pNodo;
		}
		else{
			lt->fim->prox = pNodo;
		}
		lt->fim = pNodo;
		lt->n++;
		return SUCESSO;
	}
}

int personalizarMusica(ListaDE *lt, char titulo[50], char artista[50], Musica m){ 
	Nodo *pAux, *pNodo;
	int c;
	
	pNodo = (Nodo *) malloc(sizeof(Nodo));
	if(pNodo == NULL){
		return FALTOU_MEMORIA;
	}
	if(lt->n == 0){
		return PLAYLIST_VAZIA;
	}
	pAux = lt->inicio;
	c=0;
	while(pAux!=NULL){
		if(strcmp(pAux->info.titulo, titulo)==0 && strcmp(pAux->info.artista, artista)==0){
			pNodo->info = m;
			pNodo->ant = pAux;
			pNodo->prox = pAux->prox;
			
			if(pAux->prox!=NULL){
				pAux->prox->ant = pNodo;
			}
			else{
				lt->fim = pNodo;
			}
			pAux->prox = pNodo;
			lt->n++;
			return SUCESSO;
		}
		pAux = pAux->prox;
	}
	if(c==0){
		return MUSICA_INEXISTENTE;
	}
}

int pularFaixa(ListaDE *lt, PilhaSE *p, Musica *m){ 
	Nodo *pNodo;
	int r;

    if(lt->n == 0){
        return PLAYLIST_VAZIA;
    }

    *m = lt->inicio->info;  
    pNodo = lt->inicio;
    lt->inicio = lt->inicio->prox;

    if(lt->n == 1){
        lt->fim = NULL;
    } else {
        lt->inicio->ant = NULL;
    }
    lt->n--;
    empilhaHistorico(p, pNodo);
    
	return SUCESSO;
}

int tocarFaixa(ListaDE *lt, PilhaSE *p, char titulo[50], char artista[50], Musica *m){ 
	Nodo *pNodo;
	int c=0;
	
	if(lt->n==0){
		return PLAYLIST_VAZIA;
	}
	pNodo = lt->inicio;
	while(pNodo!=NULL){
		if(strcmp(pNodo->info.titulo, titulo)==0 && strcmp(pNodo->info.artista, artista)==0){
			c++;
			*m = pNodo->info;
			
			if(pNodo == lt->inicio){
				lt->inicio = pNodo->prox;
				if(lt->inicio!=NULL){
					lt->inicio->ant = NULL;
				}
				else{
					lt->fim = NULL;
				}
			}
			else{
				if(pNodo == lt->fim){
					lt->fim = pNodo->ant;
					lt->fim->prox = NULL;
				}
				else{
					pNodo->ant->prox = pNodo->prox;
					pNodo->prox->ant = pNodo->ant;
				}
			}
			lt->n--;
		    empilhaHistorico(p, pNodo);
		    
			return SUCESSO;
		}
		pNodo = pNodo->prox;
	}
	if(c==0){
		return MUSICA_INEXISTENTE;
	}
}

int remover(ListaDE *lt, char titulo[50], char artista[50]){ 
	Nodo *pNodo;
	int c=0;
	
	if(lt->n==0){
		return PLAYLIST_VAZIA;
	}
	pNodo = lt->inicio;
	while(pNodo!=NULL){
		if(strcmp(pNodo->info.titulo, titulo)==0 && strcmp(pNodo->info.artista, artista)==0){
			c++;
			
			if(pNodo == lt->inicio){
				lt->inicio = pNodo->prox;
				if(lt->inicio!=NULL){
					lt->inicio->ant = NULL;
				}
				else{
					lt->fim = NULL;
				}
			}
			else{
				if(pNodo == lt->fim){
					lt->fim = pNodo->ant;
					lt->fim->prox = NULL;
				}
				else{
					pNodo->ant->prox = pNodo->prox;
					pNodo->prox->ant = pNodo->ant;
				}
			}
			lt->n--;
		    free(pNodo);
		    
			return SUCESSO;
		}
		pNodo = pNodo->prox;
	}
	if(c==0){
		return MUSICA_INEXISTENTE;
	}
}

int estaVazia(ListaDE lt){
	if(lt.n == 0){
		return PLAYLIST_VAZIA;
	}
	else{
		return SUCESSO;
	}
}

void exibePlaylist(ListaDE lt, PilhaSE p){ 
	Nodo *pLista, *pPilha;
	pLista = lt.inicio;
	pPilha = p.topo;
	
	printf("\n                   Sua Playlist de reproducao:");
	if(lt.n==1){
		printf("\n                   A Playlist possui 1 Musica!");
	}
	else{
		printf("\n                   A Playlist possui %d Musicas!", lt.n);
	}
	printf("\n                   [Titulo] - [Artista] - (Duracao)");
	while(pLista != NULL){
		printf("\n                   %s - %s  (%.2f)", pLista->info.titulo, pLista->info.artista, pLista->info.duracao);
		pLista = pLista->prox;
	}
	if(pPilha != NULL){
		printf("\n\nHistorico de musicas tocadas:");
		printf("\n[Titulo] - [Artista] - (Duracao)");
	}
	while(pPilha !=NULL){
		printf("\n%s - %s  (%.2f)", pPilha->info.titulo, pPilha->info.artista, pPilha->info.duracao);
		pPilha = pPilha->prox;
	}
}

int limpaPlaylist(ListaDE *lt){
	if(lt->inicio==NULL){
		return PLAYLIST_VAZIA;
	}
	else{
		Nodo *pNodo;
		while(lt->inicio!=NULL){
			pNodo = lt->inicio;
			lt->inicio = pNodo->prox;
			free(pNodo);
		}
		return SUCESSO;
	}
}

void empilhaHistorico(PilhaSE *p, Nodo *pNodo){
	pNodo->prox = p->topo;
	p->topo = pNodo;
}

int desempilhaHistorico(PilhaSE *p, ListaDE *lt){
	Nodo *pNodo, *i;
	int r;
	
	if(p->topo==NULL){
		return HISTORICO_VAZIO;
	}
	else{
		while(p->topo!=NULL){
			pNodo = p->topo;
			p->topo = pNodo->prox;
			
			r = adicionarMusicaTopo(lt, pNodo->info);
			
			if(r == FALTOU_MEMORIA){
				return FALTOU_MEMORIA;
			}
			
			free(pNodo);
		}
		return SUCESSO;
	}
}

int limpaHistorico(PilhaSE *p){
	if(p->topo==NULL){
		return HISTORICO_VAZIO;
	}
	else{
		Nodo *pNodo;
		while(p->topo!=NULL){
			pNodo = p->topo;
			p->topo = pNodo->prox;
			free(pNodo);
		}
		return SUCESSO;
	}
}

void salvarPlaylist(ListaDE *lt, char *nomeArquivo){
	FILE *arquivo;
	Nodo *aux;
	
	if((arquivo = fopen(nomeArquivo, "w")) == NULL){
		printf("Nao foi possivel abrir o arquivo!\n");
	}
	else{
		aux = lt->inicio;
		while(aux!=NULL){
			fprintf(arquivo, "%s - %s - %.2f\n", aux->info.titulo, aux->info.artista, aux->info.duracao);
			aux = aux->prox;
		}
		fclose(arquivo);
		printf("Gravacao realizada com sucesso!\n");
	}
}

int carregarPlaylist(ListaDE *lt, char *nomeArquivo){
	FILE *arquivo;
	int r;
	
	if((arquivo = fopen(nomeArquivo, "r")) == NULL){
		printf("Nao foi possivel abrir o arquivo!\n");
		return PLAYLIST_VAZIA;
	}
	else{
		criaLista(lt);
		Musica m;
		while(fscanf(arquivo, " %49[^-] - %49[^-] - %f", m.titulo, m.artista, &m.duracao)==3){
			r = adicionarMusicaFinal(lt, m);
			if(r == FALTOU_MEMORIA){
				fclose(arquivo);
				return FALTOU_MEMORIA;
			}
		}
		fclose(arquivo);
		if(lt->inicio == NULL){
			return PLAYLIST_VAZIA;
		}
		
		printf("Importacao realizada com sucesso!\n");
		return SUCESSO;
	}
}

void salvarHistorico(PilhaSE *p, char *nomeArquivo){
	FILE *arquivo;
	Nodo *aux;
	
	if((arquivo = fopen(nomeArquivo, "w")) == NULL){
		printf("Nao foi possivel abrir o arquivo!\n");
	}
	else{
		aux = p->topo;
		while(aux!=NULL){
			fprintf(arquivo, "%s - %s - %.2f", aux->info.titulo, aux->info.artista, aux->info.duracao);
			aux = aux->prox;
		}
		fclose(arquivo);
		printf("Gravacao realizada com sucesso!\n");
	}
}

int carregarHistorico(PilhaSE *p, char *nomeArquivo){
	FILE *arquivo;
	
	if((arquivo = fopen(nomeArquivo, "r")) == NULL){
		printf("Nao foi possivel abrir o arquivo!\n");
		return HISTORICO_VAZIO;
	}
	else{
		criaPilha(p);
		Musica m;
		while(fscanf(arquivo, "%49[^-] - %49[^-] - %f", m.titulo, m.artista, &m.duracao)==3){
			Nodo *pNodo;
			pNodo = (Nodo*) malloc(sizeof(Nodo));
			if(pNodo == NULL){
				fclose(arquivo);
				return FALTOU_MEMORIA;
			}
			pNodo->info = m;
			empilhaHistorico(p, pNodo);
		}
		fclose(arquivo);
		if(p->topo==NULL){
			return HISTORICO_VAZIO;
		}
		printf("Importacao realizada com sucesso!\n");
		return SUCESSO;
	}
}
