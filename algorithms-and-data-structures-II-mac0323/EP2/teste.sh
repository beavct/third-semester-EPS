#!/bin/bash

TEMPO=0

    echo -e "\nRESULTADO DOS TESTES\n" >> resultados.txt

    #para textar o hamlet
    for i in $(seq 1 10); do
        let TEMPO=$(./ep2 hamlet.txt)+$TEMPO
    done

    TEMPO=$(echo "${TEMPO}/10000000" | bc -l)

    echo -e "\n HAMLET:\n" >> resultados.txt
    echo -e "Tempo médio: " ${TEMPO} >> resultados.txt

    let TEMPO=0

    # para textar o moby
    for i in $(seq 1 10); do
        let TEMPO=$(./ep2 mobydick.txt)+$TEMPO
    done

    TEMPO=$(echo "${TEMPO}/10000000" | bc -l)

    echo -e "\n MOBY DICK:\n" >> resultados.txt
    echo -e "Tempo médio: " ${TEMPO} >> resultados.txt

    let TEMPO=0


    # para textar o Oliver
    for i in $(seq 1 10); do
        let TEMPO=$(./ep2 oliver_twist.txt)+$TEMPO
    done

    TEMPO=$(echo "${TEMPO}/10000000" | bc -l)

    echo -e "\n OLIVER TWIST:\n" >> resultados.txt
    echo -e "Tempo médio: " ${TEMPO} >> resultados.txt

    let TEMPO=0

    # para textar o War and Peace
    for i in $(seq 1 10); do
        let TEMPO=$(./ep2 war_and_peace.txt)+$TEMPO
    done

    TEMPO=$(echo "${TEMPO}/10000000" | bc -l)

    echo -e "\n WAR AND PEACE:\n" >> resultados.txt
    echo -e "Tempo médio: " ${TEMPO} >> resultados.txt

    let TEMPO=0

    # para textar o Bible
    for i in $(seq 1 10); do
        let TEMPO=$(./ep2 The_Holy_Bible.txt)+$TEMPO
    done

    TEMPO=$(echo "${TEMPO}/10000000" | bc -l)

    echo -e "\n BIBLE:\n" >> resultados.txt
    echo -e "Tempo médio: " ${TEMPO} >> resultados.txt

    let TEMPO=0

    # para textar o In search of lost time
    for i in $(seq 1 10); do
        let TEMPO=$(./ep2 In_search_of_lost_time.txt)+$TEMPO
    done

    TEMPO=$(echo "${TEMPO}/10000000" | bc -l)

    echo -e "\n IN SEARCH OF LOST TIME:\n" >> resultados.txt
    echo -e "Tempo médio: " ${TEMPO} >> resultados.txt


exit 0
