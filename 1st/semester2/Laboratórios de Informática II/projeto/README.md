# Board Game Solver

Projeto desenvolvido em **C**.
É um jogo de tabuleiro executado na linha de comandos, onde o objetivo é resolver um puzzle respeitando um conjunto de regras.
O jogador pode marcar casas, riscar posições, verificar violações das regras, desfazer jogadas, pedir ajuda ou resolver automaticamente o tabuleiro.

## 🎮 Comandos disponíveis

* `g <nome do tabuleiro>` – Gravar o tabuleiro atual.
* `l <nome do tabuleiro>` – Ler um tabuleiro.
* `b <coordenada>` – Colocar a letra em maiúsculas.
* `r <coordenada>` – Colocar um `#` na posição indicada.
* `v` – Mostrar as violações das regras do jogo.
* `d` – Desfazer o último comando.
* `a` – Dar uma ajuda ao jogador.
* `A` – Dar a melhor ajuda possível.
* `R` – Resolver automaticamente o tabuleiro.
* `s` – Sair do jogo.

## 📋 Regras do jogo

1. Cada casa contém um símbolo (inicialmente uma letra minúscula).
2. Em cada linha e coluna pode existir apenas uma ocorrência de cada símbolo marcada em maiúsculas.
3. As restantes ocorrências desse símbolo devem ser substituídas por `#`.
4. Se uma casa estiver marcada com `#`, todas as casas ortogonalmente adjacentes (cima, baixo, esquerda e direita) devem permanecer ativas.
5. Todas as casas ativas devem formar um único caminho ortogonal, ou seja, devem estar todas ligadas.

## ⚙️ Compilação

O projeto utiliza um **Makefile** para automatizar a compilação.

### Compilar o jogo

```bash
make jogo
```

### Executar o jogo

```bash
./jogo
```

### Compilar os testes

```bash
make test
```

### Executar os testes

```bash
make testar
```

### Limpar os ficheiros gerados

```bash
make clean
```

## 🛠️ Tecnologias

* Linguagem **C**
* **GCC**
* **Makefile**
* Interface de linha de comandos (CLI)
