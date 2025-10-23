#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep((x)*1000)
#endif

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

int verificar_vitoria(Sudoku *sudoku) {
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (sudoku->tabuleiro[i][j] != sudoku->solucao[i][j])
                return 0;
        }
    }
    return 1;
}

// Mostra o menu de comandos
void mostrar_menu() {
    printf("\n========================================\n");
    printf("COMANDOS:\n");
    printf("  linha(1 - 9) coluna(1 - 9) número(1 - 9) - Preencher célula\n");
    printf("  0 0 0 - Sair do jogo\n");
    printf("  0 0 1 - Ver solução\n");
    printf("  0 0 9 - Mostrar este menu\n");
    printf("========================================\n");
}

// Loop de jogo com vidas
void jogar(Sudoku *sudoku) {
    mostrar_menu();
    while (sudoku->vidas > 0) {
        int linha, coluna, num;
        printf("\nVidas restantes: %d\n", sudoku->vidas);
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

        // Mostrar menu
        if (linha == 0 && coluna == 0 && num == 9) {
            mostrar_menu();
            continue;
        }

        linha--; coluna--;

        if (linha < 0 || linha >= 9 || coluna < 0 || coluna >= 9 || num < 1 || num > 9) {
            printf("Entrada inválida.\n");
            continue;
        }

        if (sudoku->tabuleiro[linha][coluna] != 0) {
            printf("Essa posição já está preenchida.\n");
            continue;
        }

        if (sudoku->solucao[linha][coluna] != num) {
            printf("NÚmero incorreto! Você perdeu uma vida...\n");
            sudoku->vidas--;
            if (sudoku->vidas == 0) {
                printf("\n*** GAME OVER - Você perdeu todas as vidas! ***\n");
                printf("\n=== SOLUÇÃO ===\n");
                mostrar(sudoku->solucao);
                break;
            } else {
                mostrar(sudoku->tabuleiro);
            }
            continue;
        } else {
            sudoku->tabuleiro[linha][coluna] = num;
            printf("Correto!\n");
            mostrar(sudoku->tabuleiro);
            if (verificar_vitoria(sudoku)) {
                printf("\n");
                printf("+-----------------------------------+\n");
                printf("|  *** PARABÉNS! VOCÊ VENCEU! ***   |\n");
                printf("|   Sudoku completado com sucesso!  |\n");
                printf("+-----------------------------------+\n");
                break;
        }}
        
    }
}

void loading_animation(int seconds) {
    const char spinner[] = {'|', '/', '-', '\\'};
    int i = 0;
    clock_t start_time = clock();
    while (((double)(clock() - start_time) / CLOCKS_PER_SEC) < seconds) {
        printf("\rGerando Sudoku completo... %c", spinner[i++ % 4]);
        fflush(stdout);
        Sleep(100);  // 100 ms
    }
    printf("\rGerando Sudoku completo... concluído!  \n");
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);  // UTF-8
    #endif
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));
    int easy = 40;
    int normal = 49;
    int hard = 56;
    int impossible = 60;
    int difficulty;
    int difset;

    Sudoku jogo;
    jogo.vidas = VIDAS_INICIAIS;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            jogo.tabuleiro[i][j] = 0;

    loading_animation(1);  // Animação de 1 segundo
    gerar_completo(jogo.tabuleiro);
    copiar_grid(jogo.tabuleiro, jogo.solucao);

    printf("Selecione a dificuldade:\n 1 - Fácil\n 2 - Normal\n 3 - Difícil\n 4 - Impossível\n");
    scanf("%d", &difficulty);
    switch(difficulty) {
        case 1:
            difset = easy;
            break;
        case 2:
            difset = normal;
            break;
        case 3:
            difset = hard;
            break;
        case 4:
            difset = impossible;
            break;
        default:
            printf("Dificuldade inválida, usando normal.\n");
            difset = normal;
            break;
    }


    criar_desafio(jogo.tabuleiro, difset);
    printf("\nSudoku para jogar:\n");
    mostrar(jogo.tabuleiro);

    jogar(&jogo);

    return 0;
}
