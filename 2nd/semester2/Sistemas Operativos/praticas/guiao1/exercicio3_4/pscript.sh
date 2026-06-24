#!/bin/bash

set -e

if [ "$#" -lt 1 ]; then
  echo "Usage: $0 <number_of_people_to_add>"
  exit 1
fi

for ((i = 1; i <= $1; i++))
do
    AGE=$(((RANDOM % 100)+1))
    echo "./people -i Person${i} $AGE"

    ./people -i Person${i} $AGE

done
