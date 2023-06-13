#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define LARGURA 30           // Largura da matriz
#define ALTURA 30          // Altura da matriz
#define MAX_GERACAO 50   // Número máximo de gerações

// Função que conta o número de vizinhos vivos de uma célula
int count_vizinhos(int** borda, int x, int y, int largura, int altura) {
    int count = 0;

    // Verifica vizinhos na esquerda
    if (x > 0) {
        // Verifica vizinho à esquerda
        if (borda[x-1][y] == 1) {
            count++;
        }
        // Verifica vizinho na diagonal superior esquerda
        if (y > 0 && borda[x-1][y-1] == 1) {
            count++;
        }
        // Verifica vizinho na diagonal inferior esquerda
        if (y < altura-1 && borda[x-1][y+1] == 1) {
            count++;
        }
    }

    // Verifica vizinhos na direita
    if (x < largura-1) {
        // Verifica vizinho à direita
        if (borda[x+1][y] == 1) {
            count++;
        }
        // Verifica vizinho na diagonal superior direita
        if (y > 0 && borda[x+1][y-1] == 1) {
            count++;
        }
        // Verifica vizinho na diagonal inferior direita
        if (y < altura-1 && borda[x+1][y+1] == 1) {
            count++;
        }
    }

    // Verifica vizinhos acima
    if (y > 0 && borda[x][y-1] == 1) {
        count++;
    }

    // Verifica vizinhos abaixo
    if (y < altura-1 && borda[x][y+1] == 1) {
        count++;
    }

    return count;
}

// Função que atualiza o estado da matriz
void atualiza_borda(int **borda) {

    // Cria uma nova matriz vazia
    int **nova_borda = malloc(LARGURA * sizeof(int *));
        for (int i = 0; i < LARGURA; i++) {
        nova_borda[i] = malloc(ALTURA * sizeof(int));
        for (int j = 0; j < ALTURA; j++) {
        nova_borda[i][j] = 0;
    }
}
    // Verifica cada célula da matriz
    for (int i = 0; i < LARGURA; i++) {
        for (int j = 0; j < ALTURA; j++) {

            int vizinho = count_vizinhos(borda, i, j, LARGURA, ALTURA);  // Conta o número de vizinhos vivos
            // Se a célula estiver viva...
            if (borda[i][j] == 1) {
                // ... e tiver menos de 2 ou mais de 3 vizinhos vivos, morre
                if (vizinho < 2 || vizinho > 3) {
                    nova_borda[i][j] = 0;
                }
                // ... caso contrário, sobrevive
                else {
                    nova_borda[i][j] = 1;
                }
            }
            // Se a célula estiver morta...
            else {
                // ... e tiver exatamente 3 vizinhos vivos, nasce
                if (vizinho == 3) {
                    nova_borda[i][j] = 1;
                }
            }
        }
    }

    // Copia a nova matriz para a matriz original
    for (int i = 0; i < LARGURA; i++) {
        for (int j = 0; j < ALTURA; j++) {
            borda[i][j] = nova_borda[i][j];
        }
    }

    for (int i = 0; i < LARGURA; i++) {
    free(nova_borda[i]);
    }
    free(nova_borda);

}

// Função para medir o tempo
double get_current_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double) time.tv_sec + (double) time.tv_usec * 1e-6;
}


int main() {
    // Inicializa a semente do gerador de números aleatórios com o valor do relógio do sistema
    //srand(time(NULL));
    srand(1234);

    // Aloca memória para o tabuleiro
    int **borda = malloc(LARGURA * sizeof(int *));
    for (int i = 0; i < LARGURA; i++) {
        borda[i] = malloc(ALTURA * sizeof(int));

        // Inicializa as células do tabuleiro com valores aleatórios (0 ou 1)
        for (int j = 0; j < ALTURA; j++) {
            borda[i][j] = rand() % 2;
        }
    }

    // Imprime o primeiro tabuleiro gerado
    /*
    printf("Tabuleiro Origem: ");
    printf("\n");
    for (int i = 0; i < LARGURA; i++) {
            for (int j = 0; j < ALTURA; j++) {
                printf("%c", borda[i][j] ? '#' : '.');
            }
            printf("\n");
        }
     printf("\n");
     */

    int geracao = 0;

    double start, finish;

    start = get_current_time();

    // Executa o loop principal do jogo da vida
    while (geracao < MAX_GERACAO) {
        // atualiza a matriz
        atualiza_borda(borda);

        if(geracao + 1 == MAX_GERACAO){
            printf("Tabuleiro Final: ");
            printf("\n");

        // imprime a matriz
        /*
        for (int i = 0; i < LARGURA; i++) {
            for (int j = 0; j < ALTURA; j++) {
                printf("%c", borda[i][j] ? '#' : '.');
            }
            printf("\n");
        }

        printf("\n");
        printf("\n");
    }
    */
        // incrementa o número de gerações
        geracao++;
    }

    finish = get_current_time();

    // Libera a memória alocada para o tabuleiro
    for (int i = 0; i < LARGURA; i++) {
        free(borda[i]);
    }
        free(borda);

    printf("Elapsed time: %f seconds\n", finish - start);
    printf("O total de gerações foi: %d", geracao);


    return 0;
}

