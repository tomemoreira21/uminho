#!/bin/bash

DIR="$(cd "$(dirname "$0")" && pwd)"
RUNNER="$DIR/../bin/runner"

echo "Starting fairness test..."

# USER 1 - SPAM (muitos jobs longos)
for i in {1..20}; do
    $RUNNER -e 1 "sleep 1" &
done

# Pequeno delay para garantir que entram primeiro (importante para FCFS)
sleep 0.2

# USERS 2, 3, 4 - jobs curtos
$RUNNER -e 2 "echo hello from user 2" &
$RUNNER -e 3 "echo hello from user 3" &
$RUNNER -e 4 "echo hello from user 4" &

wait

echo "Fairness test done."
