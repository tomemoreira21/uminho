#!/bin/bash

DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="$DIR/.."
CONTROLLER="$ROOT/bin/controller"
RUNNER="$ROOT/bin/runner"

# Função para evitar repetição de código
run_test_case() {
    local MAX_P=$1 #max paralel é o 1 arg
    local SCHED=$2  #o tipo de escalonamento é 2 arg
    local TEST_SCRIPT=$3 #o sript de testes é o 3 arg

    echo "-------------------------------------------------------"
    echo "Starting controller ($SCHED $MAX_P Max_paralel)"
    
    make -C "$ROOT" clean > /dev/null 2>&1
    make -C "$ROOT" > /dev/null 2>&1

    # Inicia o controller
    $CONTROLLER "$MAX_P" "$SCHED" &
    CTRL_PID=$!

    sleep 1

    echo "Running $TEST_SCRIPT..."
    "$DIR/$TEST_SCRIPT" > /dev/null 2>&1

    echo "Tests finished. Shutting down..."
    $RUNNER -s > /dev/null 2>&1


    wait $CTRL_PID 2>/dev/null

    echo "Controller exited. Analyzing..."
    "$DIR/analyze.sh"
    echo -e "\n"
}


run_test_case 2 "FCFS" "test_fairness.sh"
run_test_case 2 "RR" "test_fairness.sh"


run_test_case 2 "FCFS" "test_consc.sh"
run_test_case 2 "RR" "test_consc.sh"


echo "=== TESTES MAX PARALEL 100 ==="
run_test_case 100 "FCFS" "run_tests.sh"
run_test_case 100 "RR" "run_tests.sh"


echo "=== TESTES MAX PARALEL 2 ==="
run_test_case 2 "FCFS" "run_tests.sh"
run_test_case 2 "RR" "run_tests.sh"

echo "Full Benchmark finished."