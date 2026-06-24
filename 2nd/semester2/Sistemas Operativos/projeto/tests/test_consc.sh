#!/bin/bash

DIR="$(cd "$(dirname "$0")" && pwd)"
RUNNER="$DIR/../bin/runner"

echo "Forçando FCFS a ganhar por larga margem..."

#Ocupar os 2 slots com algo rápido (para a fila começar a formar-se atrás) (no caso de maxparalell=2)
$RUNNER -e 1 "sleep 0.1" &
$RUNNER -e 2 "sleep 0.1" &

#USER 1: Lança muitos jobs curtos
for i in {1..10}; do
    $RUNNER -e 1 "echo User 1 - Job $i" &
done

#estes users lançam jobs muito pesados
$RUNNER -e 3 "sleep 10" &
$RUNNER -e 4 "sleep 10" &
$RUNNER -e 5 "sleep 10" &

wait
echo "Teste finalizado."