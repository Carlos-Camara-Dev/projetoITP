#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int jogada_valida(int** m, int jogada);

int** tabuleiro;

// Função para exibir o tabuleiro
void exibir_matriz(int** m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                printf("%d ", i * 3 + j + 1); // Exibe números das células
            } else if (m[i][j] == 1) {
                printf("X ");
            } else if (m[i][j] == 2) {
                printf("O ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

//Função que cria o jogo da velha 
int** criar_jogo_da_velha() {
    int** tabuleiro = (int**)malloc(3 * sizeof(int*)); // Alocar as linhas
    if (tabuleiro == NULL) {
        printf("Erro: Falha na alocação de memória para o tabuleiro.\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        tabuleiro[i] = (int*)malloc(3 * sizeof(int)); // Alocar as colunas
        if (tabuleiro[i] == NULL) {
            printf("Erro: Falha na alocação de memória para as colunas.\n");
            exit(1);
        }
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = 0; // Inicializa o tabuleiro com zeros
        }
    }
    return tabuleiro;
}

// Função que liberar a memória do jogo da velha
void encerrar_jogo_da_velha(int** tabuleiro) {
    for (int i = 0; i < 3; i++) {
        free(tabuleiro[i]); // Libera cada linha
    }
    free(tabuleiro); // Libera o array de ponteiros
}

// Função que verifica as linhas
int verifica_linhas(int** m) {
    for (int i = 0; i < 3; i++) {
        if (m[i][0] == m[i][1] && m[i][1] == m[i][2] && m[i][0] != 0) {
            return m[i][0]; // Retorna o vencedor (1 para X, 2 para O)
        }
    }
    return 0; // Sem vencedor
}

// Função que verifica as colunas
int verifica_colunas(int** m) {
    for (int i = 0; i < 3; i++) {
        if (m[0][i] == m[1][i] && m[1][i] == m[2][i] && m[0][i] != 0) {
            return m[0][i];
        }
    }
    return 0;
}

// Função que verifica a diagonal principal
int verifica_diagonal_principal(int** m) {
    if (m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[0][0] != 0) {
        return m[0][0];
    }
    return 0;
}

// Função que verifica a diagonal secundária
int verifica_diagonal_secundaria(int** m) {
    if (m[0][2] == m[1][1] && m[1][1] == m[2][0] && m[0][2] != 0) {
        return m[0][2];
    }
    return 0;
}

// Função que faz a escolha do PC
int escolha_do_pc(int** m) {
    int gerador;
    do {
        gerador = rand() % 9 + 1;
    } while (!jogada_valida(m, gerador));
    int i = (gerador - 1) / 3; // linha
    int j = (gerador - 1) % 3; // coluna
    m[i][j] = 2; // Marca a jogada do PC
    return gerador; // posição escolhida pelo PC
}

// Função que verifica se a jogada é válida
int jogada_valida(int** m, int jogada) {
    if (jogada < 1 || jogada > 9) {
        return 0; // Jogada fora do intervalo
    }
    int i = (jogada - 1) / 3; // linha
    int j = (jogada - 1) % 3; // coluna
    return (m[i][j] == 0); // Retorna verdadeiro se a célula está vazia
}
// Função que escolhe o modo de jogo(Facil/Normal)

// Função principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int** jogo_da_velha = criar_jogo_da_velha(); //Cria o jogo da velha

    int vencedor = 0;

    for (int rodada = 1; rodada <= 9; rodada++) {
        exibir_matriz(jogo_da_velha);

        if (rodada % 2 != 0) { // jogador X
            printf("Escolha sua posição, jogador X: ");
            int jogadaX;
            scanf("%d", &jogadaX);
            while (!jogada_valida(jogo_da_velha, jogadaX)) {
                printf("Jogada inválida! Escolha novamente: ");
                scanf("%d", &jogadaX);
            }
            int i = (jogadaX - 1) / 3;
            int j = (jogadaX - 1) % 3;
            jogo_da_velha[i][j] = 1; // Marca a jogada do jogador X
        } else { // jogador O (PC)
            int jogadaO = escolha_do_pc(jogo_da_velha);
            printf("Escolha da máquina, jogador O: %d\n", jogadaO);
        }

        // Verifica vencedor apenas a partir da quinta rodada
        if (rodada >= 5) {
            vencedor = verifica_linhas(jogo_da_velha);
            if (vencedor != 0) break;

            vencedor = verifica_colunas(jogo_da_velha);
            if (vencedor != 0) break;

            vencedor = verifica_diagonal_principal(jogo_da_velha);
            if (vencedor != 0) break;

            vencedor = verifica_diagonal_secundaria(jogo_da_velha);
            if (vencedor != 0) break;
        }

        // Checar empates
        if (rodada == 9 && vencedor == 0) {
            exibir_matriz(jogo_da_velha);
            printf("Empate!\n");
        }
    }

    if (vencedor != 0) {
        exibir_matriz(jogo_da_velha);
        printf("O vencedor é: %c\n", vencedor == 1 ? 'X' : 'O');
    }
    encerrar_jogo_da_velha(jogo_da_velha);
    return 0;
}
