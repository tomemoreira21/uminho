# SO_Pratico

O projeto implementa um controlador de execução de processos e utilitários (runners) em C, com comunicação por FIFO e suporte a políticas de escalonamento.

## Stack
- Linguagem: C (principal)
- Ferramentas: Make (Makefile)
- Testes: scripts Shell em tests/

## O que faz
- Controlador (controller): recebe pedidos de submissão, lista de estado, notificações de fim e pedido de encerramento via mensagem (FIFO).
- Runner(s): executam os comandos recebidos pelo controlador (comunicação via pipes/FIFO).
- Suporte a execução paralela limitada (número máximo de processos em simultâneo) e a diferentes políticas de escalonamento (passadas como argumento ao controlador).

## Organização do repositório
```
Makefile                 # build rules
.gitignore
include/                 # headers: tipos e definições (FIFO_PATH, controllers, pipes, etc.)
src/                     # código-fonte em C (controller, runner, parser, process, common, ...)
tests/                   # scripts de teste e benchmark (run_tests.sh, analyze.sh, benchmark.sh, ...)
relatorio/               # relatório em PDF do trabalho
```

Como isto se integra: o binário do controlador coordena os pedidos recebidos por um FIFO global (macro FIFO_PATH nos headers). Os runners recebem notificações do controlador e executam os comandos. O Makefile compila os objetos e gera os binários (bin/controller, bin/runner).

## Como compilar
No directório do repositório:
```sh
make
```
(Isto usa o Makefile incluído; gera os binários no diretório `bin/` conforme as regras do Makefile.)

Para compilar apenas o controlador ou apenas o runner:
```sh
make controller
make runner
```

## Como executar (exemplos)
1. Iniciar o controlador (ex.: 4 processos em paralelo, política "FCFS"):
```sh
./bin/controller <max_parallel> <scheduling_policy>
# Exemplo:
./bin/controller 4 FCFS
```
Observação: o primeiro argumento é o número máximo de processos em paralelo; o segundo é a política de escalonamento (o nome exacto das políticas suportadas está definido no código / nos headers).

2. Iniciar um runner (exemplo):
```sh
./bin/runner
```
(Os detalhes exatos de argumentos do runner e do formato de mensagens estão nas implementações em `src/` e nos headers em `include/`.)

3. Para ver exemplos de uso e jornadas de teste, executar os scripts:
```sh
bash tests/run_tests.sh
bash tests/benchmark.sh
bash tests/analyze.sh
```

## Testes
Existem vários scripts em `tests/`:
- `run_tests.sh` — script principal de execução de testes.
- `benchmark.sh` — testes de desempenho.
- `analyze.sh` — análise/coleção de resultados.
- `test_consc.sh`, `test_fairness.sh` — testes específicos (concorrência, fairness, ...).

Executa-os em ambiente controlado (p. ex. shell em Linux) e verifica a saída/relatórios gerados.