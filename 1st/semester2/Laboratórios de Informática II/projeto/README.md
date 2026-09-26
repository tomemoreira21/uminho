<div align="center">

# 🧩 Board Game Solver

A command-line board game puzzle solver written in **C**.

![C](https://img.shields.io/badge/-C-A8B9CC?style=for-the-badge\&logo=c\&logoColor=white)
![GCC](https://img.shields.io/badge/-GCC-4EAA25?style=for-the-badge\&logo=gnu\&logoColor=white)
![Makefile](https://img.shields.io/badge/-Makefile-427819?style=for-the-badge\&logo=gnu\&logoColor=white)
![CUnit](https://img.shields.io/badge/-CUnit-orange?style=for-the-badge)

</div>

## 📖 About the Project

**Board Game Solver** is a command-line board game developed in **C**, where the goal is to solve a puzzle while following a specific set of rules.

The player can mark cells, cross out positions, check for rule violations, undo moves, request hints, or automatically solve the board.

## 🎮 Available Commands

| Command          | Description                                      |
| ---------------- | ------------------------------------------------ |
| `g <board_name>` | Save the current board.                          |
| `l <board_name>` | Load a board.                                    |
| `b <coordinate>` | Mark the selected cell with an uppercase letter. |
| `r <coordinate>` | Place a `#` in the selected position.            |
| `v`              | Display rule violations.                         |
| `d`              | Undo the last command.                           |
| `a`              | Give the player a hint.                          |
| `A`              | Give the best possible hint.                     |
| `R`              | Automatically solve the board.                   |
| `s`              | Exit the game.                                   |

## 📋 Game Rules

1. Each cell contains a symbol, initially represented by a lowercase letter.

2. Each row and column can contain **only one occurrence of each symbol** marked in uppercase.

3. All remaining occurrences of that symbol must be replaced with `#`.

4. If a cell is marked with `#`, all of its orthogonally adjacent cells — up, down, left, and right — must remain active.

5. All active cells must form a **single connected orthogonal path**, meaning that every active cell must be reachable from every other active cell.

## ⚙️ Compilation

The project uses a **Makefile** to automate compilation.

### 🔨 Compile the Game

```bash
make jogo
```

### ▶️ Run the Game

```bash
./jogo
```

### 🧪 Compile the Tests

```bash
make test
```

### ✅ Run the Tests

```bash
make testar
```

### 🧹 Clean Generated Files

```bash
make clean
```

## 🛠️ Technologies

* 🇨 — **C**
* ⚙️ — **GCC**
* 🔨 — **Makefile**
* 💻 — **Command-Line Interface (CLI)**
* 🧪 — **HUnit**

## 📁 Project Structure

```text
.
├── src/          # Source code
├── tests/        # Test files
├── Makefile      # Build automation
└── README.md     # Project documentation
```

## 🎯 Objective

The main objective of the project is to provide a solver capable of handling the board's constraints, detecting invalid states, assisting the player with hints, and automatically finding a solution when requested.

---

<div align="center">

