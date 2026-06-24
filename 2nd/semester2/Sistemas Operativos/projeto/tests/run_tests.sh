#!/bin/bash

DIR="$(cd "$(dirname "$0")" && pwd)"
RUNNER="$DIR/../bin/runner"


for i in {1..20}; do
    $RUNNER -e 1 "sleep 0.5" &
    $RUNNER -e 1 "sleep 0.1" &
    $RUNNER -e 1 "sleep 0.1" &
    $RUNNER -e 2 "sleep 0.1" &
    $RUNNER -e 3 "sleep 0.1" &
    $RUNNER -e 4 "sleep 0.1" &
done
wait