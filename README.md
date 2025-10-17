# 🧩 Sudoku em C

Projeto desenvolvido para a disciplina **Técnica e Desenvolvimento de Algoritmo**.
A ideia foi implementar um **Sudoku jogável no terminal**, usando **backtracking** pra gerar e resolver o tabuleiro de forma automática.

---

## 💡 Sobre o projeto

O programa cria um Sudoku completo via **recursão e tentativa sistemática**, depois remove números pra formar o desafio que o jogador precisa resolver.
O jogador tem um número limitado de vidas, e pode sair ou pedir pra ver a solução a qualquer momento.

Foi um projeto pensado pra exercitar:

* **Recursividade** aplicada em um problema concreto
* **Manipulação de matrizes** e controle de fluxo
* **Organização de código** em funções pequenas e objetivas

---

## ⚙️ O que o código faz

* Gera um **tabuleiro completo** de Sudoku (9x9)
* Cria um **desafio aleatório** removendo posições
* **Valida jogadas** linha, coluna e bloco
* **Gerencia vidas** do jogador
* **Mostra solução** quando solicitado

---

## 📂 Estrutura principal

| Função             | Papel                                          |
| ------------------ | ---------------------------------------------- |
| `pode_colocar()`   | Checa se o número pode ser colocado na posição |
| `resolver()`       | Resolve o tabuleiro via backtracking           |
| `gerar_completo()` | Gera Sudoku válido embaralhando números        |
| `criar_desafio()`  | Remove células aleatórias pra gerar o desafio  |
| `mostrar()`        | Exibe o tabuleiro formatado                    |
| `jogar()`          | Controla a lógica do jogo e o sistema de vidas |

---

## 🕹️ Como rodar

### Compilar

```bash
gcc sudoku.c -o sudoku
```

### Executar

```bash
./sudoku
```

---

## 💻 Durante o jogo

* `linha coluna número` → faz uma jogada (ex: `3 5 8`)
* `0 0 0` → sair
* `0 0 1` → mostrar solução e encerrar

---

## 🔍 Exemplo de saída

```
+-------+-------+-------+
| . . 4 | 8 3 . | . . 2 |
| 1 . . | . . 7 | 2 . . |
| . . . | . 6 . | 4 1 . |
+-------+-------+-------+
| . 5 . | . . . | . 3 . |
| . 2 6 | . 9 . | 8 . . |
| . . . | . 5 3 | . . . |
+-------+-------+-------+
| 2 . . | 3 . . | . . 5 |
| . 4 . | 9 . . | 3 . . |
| . . . | . 2 . | . 9 . |
+-------+-------+-------+
Vidas restantes: 3
Digite linha(1-9) coluna(1-9) numero(1-9)
```

---

## 🧠 Conceitos aplicados

* **Backtracking recursivo**
* **Structs e manipulação de dados**
* **Matrizes bidimensionais**
* **Aleatoriedade e embaralhamento**
* **Entrada e saída de dados (stdio)**
* **Modularização do código**



