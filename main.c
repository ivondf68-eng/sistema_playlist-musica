#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"

int main() {
	int op, r;
    ListaDE lt;
    PilhaSE p;
    Musica m;
    char titulo[50], artista[50];
    
    criaLista(&lt);
    criaPilha(&p);
    
	do{
		printf("\n\n|  1. Adicionar nova musica no topo da Playlist  |  2. Adicionar nova musica no final da Playlist  |  3. Adicionar e personalizar nova musica   |");
		printf("\n|  4. Reproduzir/Pular faixa                     |  5. Tocar outra faixa                           |  6. Remover musica da Playlist             |");
		printf("\n|  7. Restaurar playlist                         |  8. Limpar Historico                            |  9. Limpar Playlist                        |");
		printf("\n| 10. Salvar Playlist                            | 11. Mostrar Playlist salva                      | 12. Salvar Historico                       |");
		printf("\n| 13. Mostrar Historico salvo                    |  0. Fechar playlist                             |");
		printf("\n\nDigite a operacao: ");
		scanf("%d", &op);
		getchar();
		
		switch(op){
			case 1:
				printf("\nDigite o nome da musica: ");
				gets(m.titulo);
				printf("\nDigite o artista: ");
				gets(m.artista);
				printf("\nDigite a duracao: ");
				scanf("%f", &m.duracao);
				if(adicionarMusicaTopo(&lt, m)==SUCESSO){
					printf("\nMusica adicionada com sucesso!\n");
				}
				else{
					printf("\nMusica nao adicionada: Faltou Memoria!\n");
				}
				break;
				
			case 2:
				printf("\nDigite o nome da musica: ");
				gets(m.titulo);
				printf("\nDigite o artista: ");
				gets(m.artista);
				printf("\nDigite a duracao: ");
				scanf("%f", &m.duracao);
				if(adicionarMusicaFinal(&lt, m)==SUCESSO){
					printf("\nMusica adicionada com sucesso!\n");
				}
				else{
					printf("\nMusica nao adicionada: Faltou Memoria!\n");
				}
				break;
				
			case 3:
				if(estaVazia(lt)==PLAYLIST_VAZIA){  
					printf("\nA Playlist esta vazia!\n");
				}
				else{
					printf("\nVoce deseja adicionar uma nova musica apos qual musica da playlist? Digite o nome da musica na Playlist: ");
					gets(titulo);
					printf("\nDigite o artista da musica na Playlist: ");
					gets(artista);
					printf("\nNova musica: Digite o nome da nova musica: ");
					gets(m.titulo);
					printf("\nDigite o artista da nova musica: ");
					gets(m.artista);
					printf("\nDigite a duracao: ");
					scanf("%f", &m.duracao);
					
					r = personalizarMusica(&lt, titulo, artista, m);
					
					if(r==MUSICA_INEXISTENTE){
						printf("\nMusica nao encontrada!\n");
					}
					if(r==SUCESSO){
						printf("\nMusica adicionada com sucesso!\n");
					}
					if(r==FALTOU_MEMORIA){
							printf("\nMusica nao adicionada: Faltou Memoria!\n");
					}
				}
				break;
				
			case 4:
				if(estaVazia(lt)==PLAYLIST_VAZIA){
					printf("\nNao pode reproduzir! A Playlist esta vazia!\n");
				}
				else{
					if(pularFaixa(&lt, &p, &m)==SUCESSO){
						printf("\n.........................Tocando agora: %s - %s (%.2f)", m.titulo, m.artista, m.duracao);
					}	
					else{
						printf("\nA Playlist esta vazia!\n");
					}
				}
				break;
				
			case 5:
				if(estaVazia(lt)==PLAYLIST_VAZIA){
					printf("\nNao pode tocar outra faixa! A Playlist esta vazia!\n");
				}
				else{
					printf("\nQual musica voce quer ouvir? Digite o nome da musica na Playlist: ");
					gets(titulo);
					printf("\nDigite o artista da musica na Playlist: ");
					gets(artista);
					
					r = tocarFaixa(&lt, &p, titulo, artista, &m);
					
					if(r==MUSICA_INEXISTENTE){
						printf("\nMusica nao encontrada!\n");
					}
					if(r==SUCESSO){
						printf("\n.........................Tocando agora: %s - %s (%.2f)", m.titulo, m.artista, m.duracao);
					}
				}
				break;
				
			case 6:
				if(estaVazia(lt)==PLAYLIST_VAZIA){
					printf("\nA Playlist esta vazia!\n");
				}
				else{
					printf("\nQual o nome da musica que voce quer excluir? ");
					gets(titulo);
					printf("\nQual e o artista? ");
					gets(artista);
					
					r = remover(&lt, titulo, artista);
					
					if(r == MUSICA_INEXISTENTE){
						printf("\nMusica nao encontrada!\n");
					}
					if(r == SUCESSO){
						printf("\nMusica removida com sucesso!\n");
					}
				}
				break;
				
			case 7:
				if(lt.n!=0){
					printf("\nNao e possivel restaurar a Playlist: A Playlit nao esta vazia ainda!\n");
				}
				else{
					r = desempilhaHistorico(&p, &lt);
					
					if(r == HISTORICO_VAZIO){
						printf("\nOperacao nao concluida: O historico esta vazio!\n");
					}
					if(r == FALTOU_MEMORIA){
						printf("\nOperacao nao concluida: Faltou Memoria!\n");
					}
					if(r == SUCESSO){
						printf("\nA sua Playlist foi restaurada!\n");
					}
				}
				break;
				
			case 8:
				if(limpaHistorico(&p)==HISTORICO_VAZIO){
					printf("\nOperacao nao concluida: O historico ja esta vazio!\n");
				}
				else{
					printf("\nOperacao realizada com sucesso: O historico foi esvaziado!\n");
				}
				break;
				
			case 9:
				if(limpaPlaylist(&lt)==PLAYLIST_VAZIA){
					printf("\nOperacao nao concluida: A Playlist ja esta vazia!\n");
				}
				else{
					printf("\nOperacao realizada com sucesso: A Playlist foi esvaziada!\n");
				}
				break;
				
			case 10:
				salvarPlaylist(&lt, "playlist.txt");
				break;
				
			case 11:
				r = carregarPlaylist(&lt, "playlist.txt");
				if(r == FALTOU_MEMORIA){
					printf("\nOperacao nao concluida: Faltou Memoria!\n");
				}
				if(r == PLAYLIST_VAZIA){
					printf("\nPlaylist vazia!\n");
				}
				break;
				
			case 12:
				salvarHistorico(&p, "historico.txt");
				break;
				
			case 13:
				r = carregarHistorico(&p, "historico.txt");
				if(r == FALTOU_MEMORIA){
					printf("\nOperacao nao concluida: Faltou Memoria!\n");
				}
				if(r == HISTORICO_VAZIO){
					printf("\nHistorico vazio!\n");
				}
				break;
		}
		exibePlaylist(lt, p);
	}while(op!=0);
	
	return 0;
}
