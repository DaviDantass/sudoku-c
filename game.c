#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9
#define VIDAS_INICIAIS 3  // Quantas vidas o jogador começa

// Struct para o Sudoku
typedef struct {
    int tabuleiro[N][N];   // Sudoku que o jogador vai preencher
    int solucao[N][N];     // Sudoku completo
    int vidas;             // Sistema de vidas
} Sudoku;

// Função que verifica se podemos colocar um número em uma célula
int pode_colocar(int grid[N][N], int linha, int coluna, int num) {
    for (int x = 0; x < N; x++)
        if (grid[linha][x] == num || grid[x][coluna] == num)
            return 0;

    int startLinha = linha - linha % 3;
    int startColuna = coluna - coluna % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startLinha + i][startColuna + j] == num)
                return 0;

    return 1;
}

// Resolver Sudoku usando backtracking
int resolver(int grid[N][N]) {
    for (int linha = 0; linha < N; linha++) {
        for (int coluna = 0; coluna < N; coluna++) {
            if (grid[linha][coluna] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (pode_colocar(grid, linha, coluna, num)) {
                        grid[linha][coluna] = num;
                        if (resolver(grid))
                            return 1;
                        grid[linha][coluna] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

// Embaralha números para gerar Sudokus diferentes
void embaralhar(int *nums) {
    for (int i = 0; i < 9; i++) {
        int j = rand() % 9;
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}

// Gera Sudoku completo usando backtracking
int gerar_completo(int grid[N][N]) {
    int nums[9] = {1,2,3,4,5,6,7,8,9};

    for (int linha = 0; linha < N; linha++) {
        for (int coluna = 0; coluna < N; coluna++) {
            if (grid[linha][coluna] == 0) {
                embaralhar(nums);
                for (int i = 0; i < 9; i++) {
                    int num = nums[i];
                    if (pode_colocar(grid, linha, coluna, num)) {
                        grid[linha][coluna] = num;
                        if (gerar_completo(grid))
                            return 1;
                        grid[linha][coluna] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

// Cria desafio removendo números aleatórios
void criar_desafio(int grid[N][N], int holes) {
    while (holes > 0) {
        int linha = rand() % N;
        int coluna = rand() % N;
        if (grid[linha][coluna] != 0) {
            grid[linha][coluna] = 0;
            holes--;
        }
    }
}

// Copia grid para outro grid
void copiar_grid(int origem[N][N], int destino[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            destino[i][j] = origem[i][j];
}

// Mostra o Sudoku no terminal
void mostrar(int grid[N][N]) {
    // Cabeçalho com números das colunas
    printf("    1 2 3   4 5 6   7 8 9\n");
    printf("  +-------+-------+-------+\n");
    
    for (int i = 0; i < N; i++) {
        // Número da linha
        printf("%d | ", i+1);
        
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0)
                printf(". ");
            else
                printf("%d ", grid[i][j]);
            if ((j+1)%3 == 0)
                printf("| ");
        }
        printf("\n");
        
        if ((i+1)%3 == 0)
            printf("  +-------+-------+-------+\n");
    }
}

// Loop de jogo com vidas
void jogar(Sudoku *sudoku) {
    while (sudoku->vidas > 0) {
        int linha, coluna, num;
        printf("\nVidas restantes: %d\n", sudoku->vidas);
        printf("Digite linha(1-9) coluna(1-9) numero(1-9) ");
        printf("(0 0 0 para sair, 0 0 1 para ver solucao): ");
        scanf("%d %d %d", &linha, &coluna, &num);

        // Sair
        if (linha == 0 && coluna == 0 && num == 0) {
            printf("Saindo...\n");
            break;
        }

        // Mostrar solução
        if (linha == 0 && coluna == 0 && num == 1) {
            printf("\nSudoku resolvido:\n");
            mostrar(sudoku->solucao);
            printf("Saindo...\n");
            break;
        }

        linha--; coluna--;

        if (linha < 0 || linha >= 9 || coluna < 0 || coluna >= 9 || num < 1 || num > 9) {
            printf("Entrada invalida.\n");
            continue;
        }

        if (sudoku->tabuleiro[linha][coluna] != 0) {
            printf("Essa posicao ja esta preenchida.\n");
            continue;
        }

        if (sudoku->solucao[linha][coluna] != num) {
            printf("Numero incorreto!\n");
            sudoku->vidas--;
            if (sudoku->vidas == 0) {
                printf("Voce perdeu todas as vidas!\n");
                mostrar(sudoku->solucao);
                break;
            }
        } else {
            sudoku->tabuleiro[linha][coluna] = num;
            printf("Correto!\n");
        }

        mostrar(sudoku->tabuleiro);
    }
}

int main() {
    srand(time(NULL));

    Sudoku jogo;
    jogo.vidas = VIDAS_INICIAIS;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            jogo.tabuleiro[i][j] = 0;

    printf("Gerando Sudoku completo...\n");
    gerar_completo(jogo.tabuleiro);
    copiar_grid(jogo.tabuleiro, jogo.solucao);

    criar_desafio(jogo.tabuleiro, 40);
    printf("\nSudoku para jogar:\n");
    mostrar(jogo.tabuleiro);

    jogar(&jogo);

    return 0;
}
