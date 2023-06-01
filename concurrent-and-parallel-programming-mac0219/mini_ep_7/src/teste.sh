#!/bin/bash

NUM_THREADS=10
NUM_ARRAY=10
TEMPO=0
MEDIA=0

    echo -e "\nRESULTADO DOS TESTES\n" >> resultados.txt

    echo -e "\nNUM_ARRAY=" ${NUM_ARRAY}"\n" >> resultados.txt

    while [ $NUM_THREADS -le 10000 ]; do

        for i in $(seq 1 10); do
            TEMPO=$(./contention ${NUM_THREADS} ${NUM_ARRAY})
            TEMPO=${TEMPO:: -1}
            MEDIA=${MEDIA}+${TEMPO}
        done

        MEDIA=$(echo "${MEDIA}/10" | bc -l)

        echo -e $(echo ${MEDIA} | tr '.' ',') >> resultados.txt

        let TEMPO=0
        let MEDIA=0

        let NUM_THREADS=${NUM_THREADS}*10
    done 

    let NUM_THREADS=10
    let NUM_ARRAY=${NUM_ARRAY}*10


    echo -e "\nNUM_ARRAY=" ${NUM_ARRAY}"\n" >> resultados.txt

    while [ $NUM_THREADS -le 10000 ]; do

        for i in $(seq 1 10); do
            TEMPO=$(./contention ${NUM_THREADS} ${NUM_ARRAY})
            TEMPO=${TEMPO:: -1}
            MEDIA=${MEDIA}+${TEMPO}
        done

        MEDIA=$(echo "${MEDIA}/10" | bc -l)

        echo -e $(echo ${MEDIA} | tr '.' ',') >> resultados.txt

        let TEMPO=0
        let MEDIA=0

        let NUM_THREADS=${NUM_THREADS}*10
    done 

    let NUM_THREADS=10
    let NUM_ARRAY=${NUM_ARRAY}*10


    echo -e "\nNUM_ARRAY=" ${NUM_ARRAY}"\n" >> resultados.txt

    while [ $NUM_THREADS -le 10000 ]; do

        for i in $(seq 1 10); do
            TEMPO=$(./contention ${NUM_THREADS} ${NUM_ARRAY})
            TEMPO=${TEMPO:: -1}
            MEDIA=${MEDIA}+${TEMPO}
        done

        MEDIA=$(echo "${MEDIA}/10" | bc -l)

        echo -e $(echo ${MEDIA} | tr '.' ',') >> resultados.txt

        let TEMPO=0
        let MEDIA=0

        let NUM_THREADS=${NUM_THREADS}*10
    done 

    let NUM_THREADS=10
    let NUM_ARRAY=${NUM_ARRAY}*10


    echo -e "\nNUM_ARRAY=" ${NUM_ARRAY}"\n" >> resultados.txt

    while [ $NUM_THREADS -le 10000 ]; do

        for i in $(seq 1 10); do
            TEMPO=$(./contention ${NUM_THREADS} ${NUM_ARRAY})
            TEMPO=${TEMPO:: -1}
            MEDIA=${MEDIA}+${TEMPO}
        done

        MEDIA=$(echo "${MEDIA}/10" | bc -l)

        echo -e $(echo ${MEDIA} | tr '.' ',') >> resultados.txt

        let TEMPO=0
        let MEDIA=0

        let NUM_THREADS=${NUM_THREADS}*10
    done 


    let NUM_THREADS=10
    let NUM_ARRAY=${NUM_ARRAY}*10


    echo -e "\nNUM_ARRAY=" ${NUM_ARRAY}"\n" >> resultados.txt

    while [ $NUM_THREADS -le 10000 ]; do

        for i in $(seq 1 10); do
            TEMPO=$(./contention ${NUM_THREADS} ${NUM_ARRAY})
            TEMPO=${TEMPO:: -1}
            MEDIA=${MEDIA}+${TEMPO}
        done

        MEDIA=$(echo "${MEDIA}/10" | bc -l)

        echo -e $(echo ${MEDIA} | tr '.' ',') >> resultados.txt

        let TEMPO=0
        let MEDIA=0

        let NUM_THREADS=${NUM_THREADS}*10
    done 


    let NUM_THREADS=10
    let NUM_ARRAY=${NUM_ARRAY}*10


    echo -e "\nNUM_ARRAY=" ${NUM_ARRAY}"\n" >> resultados.txt

    while [ $NUM_THREADS -le 10000 ]; do

        for i in $(seq 1 10); do
            TEMPO=$(./contention ${NUM_THREADS} ${NUM_ARRAY})
            TEMPO=${TEMPO:: -1}
            MEDIA=${MEDIA}+${TEMPO}
        done

        MEDIA=$(echo "${MEDIA}/10" | bc -l)

        echo -e $(echo ${MEDIA} | tr '.' ',') >> resultados.txt

        let TEMPO=0
        let MEDIA=0

        let NUM_THREADS=${NUM_THREADS}*10
    done 


    let NUM_THREADS=10
    let NUM_ARRAY=${NUM_ARRAY}*10


    echo -e "\nNUM_ARRAY=" ${NUM_ARRAY}"\n" >> resultados.txt

    while [ $NUM_THREADS -le 10000 ]; do

        for i in $(seq 1 10); do
            TEMPO=$(./contention ${NUM_THREADS} ${NUM_ARRAY})
            TEMPO=${TEMPO:: -1}
            MEDIA=${MEDIA}+${TEMPO}
        done

        MEDIA=$(echo "${MEDIA}/10" | bc -l)

        echo -e $(echo ${MEDIA} | tr '.' ',') >> resultados.txt

        let TEMPO=0
        let MEDIA=0

        let NUM_THREADS=${NUM_THREADS}*10
    done 


    let NUM_THREADS=10
    let NUM_ARRAY=${NUM_ARRAY}*10


exit 0