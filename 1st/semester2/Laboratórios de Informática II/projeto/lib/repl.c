#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void comandosJogo(Jogo j, StackJogadas s) {
    ListaConflitos lista = NULL;
    char nomeTabuleiro[1024];
    char nomeFicheiroSave[1024] = "stackSave.txt";
    int leJogo = 0, jogoAtivo = 0;

    if (tentarRestaurarJogo(j, s,nomeFicheiroSave, nomeTabuleiro)) {
        leJogo = 1;
        jogoAtivo = 1;
    }

    leituraInicialJogo(j,&leJogo, &jogoAtivo, nomeTabuleiro);
    if (!leJogo) printf("É preciso ler um jogo para começar a jogar!\n");
        
    while (jogoAtivo) {
        imprimeTabuleiro(j->tabuleiro);

        if (j->venceu == 0) {
            lista = verificaConflitos(j->tabuleiro, lista);
            verificaVitoria(j, lista);
        }

        if (j->estadoJogo == 0) encerraJogo (j,s,&lista,nomeTabuleiro,&jogoAtivo);

        if (jogoAtivo) {
            char comando;
            if (scanf(" %c", &comando) != 1) {
                printf("Erro ao ler o comando.\n");
                while (getchar() != '\n');  
            } else {
                liberaLista(lista);
                lista = NULL;

                processaComando(comando, j, s, nomeTabuleiro, &lista);

                if (comando == 's') jogoAtivo = 0;
            }

            liberaLista(lista);
            lista = NULL;
        }
        
    }
}

// Funções auxiliares que tratam de cada comando individualmente
void carregaNovoTabuleiro(Jogo j, char *nomeTabuleiro) {
    Tabuleiro novo = malloc(sizeof(struct tabuleiro));
    char nomeNovoTabuleiro[1024];
    int sucesso = 0;

    while (!sucesso) {
        printf("Nome do novo tabuleiro que pretende carregar: ");
        while (getchar() != '\n');

        if (scanf(" %1023s", nomeNovoTabuleiro) == 1) {
            if (!strstr(nomeNovoTabuleiro, ".txt"))
                strcat(nomeNovoTabuleiro, ".txt");

            if (strcmp (nomeTabuleiro,nomeNovoTabuleiro) == 0) {
                    printf("\033[1;31mO tabuleiro que estás a carregar é o atual! Por favor carrega um tabuleiro novo.\n\033[0m");
            }

            else {
                if (comandoL(novo, nomeNovoTabuleiro) == 0) {
                    liberaTabuleiro(j->tabuleiro);
                    j->tabuleiro = novo;
                    strcpy(nomeTabuleiro, nomeNovoTabuleiro);
                    j->estadoJogo = 1;
                    j->venceu = 0;
                    printf("Jogo carregado com sucesso!\n");
                    imprimeTabuleiro(j->tabuleiro);
                    sucesso = 1;
                } else {
                    printf("Erro ao carregar o tabuleiro. Tenta novamente.\n");
                }
            }
        } else {
            printf("Erro ao ler o nome do tabuleiro. Tenta novamente.\n");
            while (getchar() != '\n');
        }
    }
}

void encerraJogo(Jogo j,StackJogadas s,ListaConflitos *lista, char *nomeTabuleiro,int *jogoAtivo) {
    imprimeResultado(j);

    if (j->venceu == 1) {
        printf("Queres gravar o jogo do tabuleiro %s resolvido? (s/n): ", nomeTabuleiro);
        char resposta;
        if (scanf(" %c", &resposta) == 1 && (resposta == 's' || resposta == 'S')) {
            if (comandoG(j->tabuleiro, nomeTabuleiro) == 0) {
                printf("Jogo gravado com sucesso!\n");
            } else {
                printf("Erro ao gravar o jogo.\n");
            }
        }
    } 

    printf("Queres continuar a jogar este mesmo tabuleiro? (s/n): ");
    char continuar;
    if (scanf(" %c", &continuar) == 1 && (continuar == 's' || continuar == 'S')) {
        imprimeTabuleiro (j->tabuleiro);
        j->estadoJogo = 1;
        j->venceu = 0;
        *jogoAtivo = 1;
    } else {
        printf ("Queres carregar um novo tabuleiro? (s/n): ");
        if (scanf(" %c", &continuar) == 1 && (continuar == 's' || continuar == 'S')) {
            liberaJogadas (s);
            carregaNovoTabuleiro (j,nomeTabuleiro);
            *jogoAtivo = 1;
        } else *jogoAtivo = 0;
    }

    liberaLista (*lista);
    *lista = NULL;
}

void leituraInicialJogo(Jogo j,int *leJogo, int *jogoAtivo, char *nomeTabuleiro) {
    char comando;
    char str[1024];

    while (!*leJogo) {
        if (scanf(" %c", &comando) != 1) while (getchar() != '\n');

        else if (comando == 's') {
            *leJogo = 1;
            j->estadoJogo = 0;
            *jogoAtivo = 0;
            free(j->tabuleiro);
            j->tabuleiro = NULL;
        }

        else if (comando != 'l') {
            printf("É preciso ler um jogo para começar a jogar!\n");
            while (getchar() != '\n');
        }

        else {
            if (scanf("%1023s", str) != 1) {
                printf("Erro ao ler o nome do ficheiro.\n");
                while (getchar() != '\n');
            } else {
                if (strstr(str, ".txt") == NULL) strcat(str, ".txt");

                if (comandoL(j->tabuleiro, str) == 0) {
                    strcpy(nomeTabuleiro, str);
                    *leJogo = 1;
                    *jogoAtivo = 1;
                } else {
                    printf("Erro ao carregar o tabuleiro.\n");
                }
            }
        }
    }
}

void processaComando(char comando, Jogo j, StackJogadas s, char *nomeTabuleiro, ListaConflitos *lista) {

    if (comando == 'b') trataComandoB(s, j->tabuleiro);
    else if (comando == 'r') trataComandoR(s, j->tabuleiro);
    else if (comando == 'g') trataComandoG(j, s);
    else if (comando == 'l') trataComandoNovoJogo(j, s, nomeTabuleiro);
    else if (comando == 'd') trataComandoD(j, s);
    else if (comando == 'v') trataComandoV(j, lista);
    else if (comando == 'a') trataComandoAjuda(j, s, lista);
    else if (comando == 'A') trataComandoA(s, j->tabuleiro);
    else if (comando == 'R') trataComandoResolve(j, s, lista);
    else if (comando == 's') {
        liberaLista(*lista);
        *lista = NULL;
    } else {
        printf("Esse comando não se encontra disponível.\n");
    }
}

int tentarRestaurarJogo(Jogo j, StackJogadas s, char *nomeFicheiroSave,char *nomeTabuleiro) {
    FILE *file = fopen(nomeFicheiroSave, "r");
    if (file == NULL) return 0;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    if (size == 0) return 0;

    if (restauraStack(s, nomeFicheiroSave, nomeTabuleiro) != 0) return 0;

    printf("Existe um jogo do %s guardado. Queres continuar? (s/n): ", nomeTabuleiro);
    char resposta;
    if (scanf(" %c", &resposta) != 1 || (resposta != 's' && resposta != 'S')) {
        liberaJogadas(s);
        return 0;
    }

    Tabuleiro temp = malloc(sizeof(struct tabuleiro));
    if (comandoL(temp, nomeTabuleiro) != 0) {
        free(temp);
        liberaJogadas(s);
        printf("Erro ao carregar o tabuleiro guardado. Começa um novo jogo.\n");
        return 0;
    }

    free(j->tabuleiro);
    j->tabuleiro = temp;
    j->estadoJogo = 1;
    printf("Jogo restaurado com sucesso.\n");
    return 1;
}

void trataComandoB(StackJogadas s, Tabuleiro t) {
    char coordenada[1024];

    if (scanf("%1023s", coordenada) != 1) {
        printf("Erro ao ler a coordenada.\n");
        return;
    }

    if (comandoB(s, t, coordenada, 0) != 0) {
        printf("Coordenada inválida.\n");
    }
}

void trataComandoR(StackJogadas s, Tabuleiro t) {
    char coordenada[1024];

    if (scanf("%1023s", coordenada) != 1) {
        printf("Erro ao ler a coordenada.\n");
        return;
    }

    if (comandoR(s, t, coordenada, 0) != 0) {
        printf("Coordenada inválida.\n");
    }
}

void trataComandoG(Jogo j, StackJogadas s) {
    char nome[1024];
    
    if (scanf("%1023s", nome) != 1) {
        printf("Erro ao ler o nome do ficheiro.\n");
        while (getchar() != '\n');
    }

    if (strstr(nome, ".txt") == NULL) strcat(nome, ".txt");
    
    if (comandoG(j->tabuleiro, nome) != 0) {
        printf("Ficheiro Inexistente.\n");
    } else {
        printf("Jogo gravado com sucesso!\n");
        gravaStack(s, "stackSave.txt", nome);
    }
}

void trataComandoD(Jogo j, StackJogadas s) {
    if (comandoD(j->tabuleiro, s) != 0) {
        printf("Já estás no estado inicial do jogo.\n");
    }
}

void trataComandoV(Jogo j, ListaConflitos *lista) {
    *lista = verificaConflitos(j->tabuleiro, *lista);
    int caminhoValido = existeCaminho(j->tabuleiro);
    
    if (*lista == NULL && caminhoValido) {
        printf("\033[32mNão há qualquer violação de restrições no tabuleiro.\033[0m\n");
    } else {
        if (!caminhoValido) {
            printf("\033[1;31mNão existe um caminho válido entre todas as brancas.\033[0m\n");
        }
        if (*lista != NULL) {
            imprimirConflitos(*lista, j->tabuleiro);
            liberaLista(*lista);
            *lista = NULL;
        }
    }
}

void trataComandoAjuda(Jogo j, StackJogadas s, ListaConflitos *lista) {
    *lista = verificaConflitos(j->tabuleiro, *lista);

    int topoStackAntes = s->sp;
    int resultado = ajudaUtilizador(s, j->tabuleiro, *lista, 0);
    int topoStackApos = s->sp;

    if (resultado == 0) {
        printf("Não existe qualquer ajuda disponível.\n");
    } else {
        imprimeAjuda(s, j->tabuleiro, topoStackAntes, topoStackApos);
    }

    liberaLista(*lista);
    *lista = NULL;
}

void trataComandoA(StackJogadas s, Tabuleiro t) {
    int resultado = comandoA (s,t,0);

    if (resultado == 0) {
        printf ("Não existem quaisquer ajudas disponíveis.\n");
    } else if (resultado == -1) {
        printf("Ajudas não aplicadas para evitar piorar a situação atual.\n");
        printf("\033[1;31m[DICA]\033[0m Aplica o comando d.\n");
    }       
}

void trataComandoResolve(Jogo j, StackJogadas s, ListaConflitos *lista) {
    int topoStackAntes = s->sp;
    
    if (resolveJogo(j->tabuleiro, s) != 1) {
        backTrack (j->tabuleiro,s,topoStackAntes);
        int resultado = resolveJogoEstadoInvalido (j->tabuleiro,s);

        if (resultado == 1) {
            printf("\033[31mEstado Inválido!\033[0m\n");
            printf("Resolução a partir do estado inicial do tabuleiro.\n");
        } else {
           backTrack (j->tabuleiro,s,topoStackAntes);
           printf("\033[1;31mO tabuleiro não possui solução.\033[0m\n");
           j->venceu = -1;
           j->estadoJogo = 0;
        }
    }

    liberaLista(*lista);
    *lista = NULL;
}

void trataComandoNovoJogo(Jogo j, StackJogadas s, char *nomeTabuleiro) {
    char nomeNovoTabuleiro[1024]; 

    if (scanf("%1023s", nomeNovoTabuleiro) != 1) {
        printf("Erro ao ler o nome do ficheiro.\n");
        while (getchar() != '\n');
        return;
    }

    if (strstr(nomeNovoTabuleiro, ".txt") == NULL) {
        strcat(nomeNovoTabuleiro, ".txt");
    }

    Tabuleiro temp = malloc(sizeof(struct tabuleiro));
    if (comandoL(temp, nomeNovoTabuleiro) == 0) {
        strcpy(nomeTabuleiro, nomeNovoTabuleiro); 
        liberaTabuleiro(j->tabuleiro);
        j->tabuleiro = temp;
        liberaJogadas(s);
        printf("Novo jogo carregado com sucesso.\n");
    } else {
        free(temp);
        printf("Erro ao carregar o novo tabuleiro.\n");
    }
}

