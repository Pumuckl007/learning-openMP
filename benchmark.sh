#!/bin/bash

function runBattery (){
  export OMP_NUM_THREADS=$1
  ./a.out -b -csv ${2} ${3} ${4} >> /dev/null
  for (( THREADS=1; THREADS<=$1; THREADS+=3 ))
  do
    export OMP_NUM_THREADS=${THREADS}
    ./a.out -b -csv ${2} ${3} ${4} >> $5
  done
}

echo -n "" > $1

for THREADS in 1 2 3 4
do
  for ROWS in 100 10000 15000 20000
  do
    export OMP_NUM_THREADS=${THREADS}
    (./a.out -b -csv ${ROWS} 100 1000) >> $1
  done
done
