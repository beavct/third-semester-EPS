#!/bin/bash
# vai ser utilizado para a MEDIÇÃO DE TEMPO
NP=1
TEMPO=0
MEDIA=0
AUX=0
    
    echo $(make)

    echo -e "\nRESULTADO DOS TESTES\n" >> resultados.txt

    echo -e "\narray_size= 2^10\n" >> resultados.txt
    while [ $NP -le 32 ]; do

        echo -e "\nnp= "${NP} "\n" >> resultados.txt

        for i in $(seq 1 10); do
            AUX=$(mpirun —np ${NP} ./broadcast ——array_size 2^10 [--root ] [——custom])
            echo $(echo ${AUX} | tr '.' ',') >> resultados.txt
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
        done

        MEDIA=$(echo "${AUX}/10" | bc -l)
        echo -e $(echo "tempo = $MEDIA\n" | tr '.' ',') >> resultados

        let TEMPO=0 #ok
        let AUX=0 #ok
        let MEDIA=0 #ok

        let NP=${NP}*2 #ok
    done 

    let NP=1

    echo -e "\narray_size= 2^11\n" >> resultados.txt
    while [ $NP -le 32 ]; do

        echo -e "\nnp= "${NP} "\n" >> resultados.txt

        for i in $(seq 1 10); do
            AUX=$(mpirun —np ${NP} ./broadcast ——array_size 2^11 [--root ] [——custom])
            echo $(echo ${AUX} | tr '.' ',') >> resultados.txt
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
        done

        MEDIA=$(echo "${AUX}/10" | bc -l)
        echo -e $(echo "tempo = $MEDIA\n" | tr '.' ',') >> resultados

        let TEMPO=0 #ok
        let AUX=0 #ok
        let MEDIA=0 #ok

        let NP=${NP}*2 #ok
    done 

    let NP=1
    echo -e "\narray_size= 2^12\n" >> resultados.txt
    while [ $NP -le 32 ]; do

        echo -e "\nnp= "${NP} "\n" >> resultados.txt

        for i in $(seq 1 10); do
            AUX=$(mpirun —np ${NP} ./broadcast ——array_size 2^12 [--root ] [——custom])
            echo $(echo ${AUX} | tr '.' ',') >> resultados.txt
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
        done

        MEDIA=$(echo "${AUX}/10" | bc -l)
        echo -e $(echo "tempo = $MEDIA\n" | tr '.' ',') >> resultados

        let TEMPO=0 #ok
        let AUX=0 #ok
        let MEDIA=0 #ok

        let NP=${NP}*2 #ok
    done 

    let NP=1

    echo -e "\narray_size= 2^13\n" >> resultados.txt
    while [ $NP -le 32 ]; do

        echo -e "\nnp= "${NP} "\n" >> resultados.txt

        for i in $(seq 1 10); do
            AUX=$(mpirun —np ${NP} ./broadcast ——array_size 2^13 [--root ] [——custom])
            echo $(echo ${AUX} | tr '.' ',') >> resultados.txt
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
        done

        MEDIA=$(echo "${AUX}/10" | bc -l)
        echo -e $(echo "tempo = $MEDIA\n" | tr '.' ',') >> resultados

        let TEMPO=0 #ok
        let AUX=0 #ok
        let MEDIA=0 #ok

        let NP=${NP}*2 #ok
    done 

    let NP=1

    echo -e "\narray_size= 2^14\n" >> resultados.txt
    while [ $NP -le 32 ]; do

        echo -e "\nnp= "${NP} "\n" >> resultados.txt

        for i in $(seq 1 10); do
            AUX=$(mpirun —np ${NP} ./broadcast ——array_size 2^14 [--root ] [——custom])
            echo $(echo ${AUX} | tr '.' ',') >> resultados.txt
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
        done

        MEDIA=$(echo "${AUX}/10" | bc -l)
        echo -e $(echo "tempo = $MEDIA\n" | tr '.' ',') >> resultados

        let TEMPO=0 #ok
        let AUX=0 #ok
        let MEDIA=0 #ok

        let NP=${NP}*2 #ok
    done 

    let NP=1

    echo -e "\narray_size= 2^15\n" >> resultados.txt
    while [ $NP -le 32 ]; do

        echo -e "\nnp= "${NP} "\n" >> resultados.txt

        for i in $(seq 1 10); do
            AUX=$(mpirun —np ${NP} ./broadcast ——array_size 2^15 [--root ] [——custom])
            echo $(echo ${AUX} | tr '.' ',') >> resultados.txt
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
        done

        MEDIA=$(echo "${AUX}/10" | bc -l)
        echo -e $(echo "tempo = $MEDIA\n" | tr '.' ',') >> resultados

        let TEMPO=0 #ok
        let AUX=0 #ok
        let MEDIA=0 #ok

        let NP=${NP}*2 #ok
    done 

    let NP=1

    echo -e "\narray_size= 2^16\n" >> resultados.txt
    while [ $NP -le 32 ]; do

        echo -e "\nnp= "${NP} "\n" >> resultados.txt

        for i in $(seq 1 10); do
            AUX=$(mpirun —np ${NP} ./broadcast ——array_size 2^16 [--root ] [——custom])
            echo $(echo ${AUX} | tr '.' ',') >> resultados.txt
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
        done

        MEDIA=$(echo "${AUX}/10" | bc -l)
        echo -e $(echo "tempo = $MEDIA\n" | tr '.' ',') >> resultados

        let TEMPO=0 #ok
        let AUX=0 #ok
        let MEDIA=0 #ok

        let NP=${NP}*2 #ok
    done 

    let NP=1

    echo -e "\narray_size= 2^17\n" >> resultados.txt
    while [ $NP -le 32 ]; do

        echo -e "\nnp= "${NP} "\n" >> resultados.txt

        for i in $(seq 1 10); do
            AUX=$(mpirun —np ${NP} ./broadcast ——array_size 2^17 [--root ] [——custom])
            echo $(echo ${AUX} | tr '.' ',') >> resultados.txt
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
        done

        MEDIA=$(echo "${AUX}/10" | bc -l)
        echo -e $(echo "tempo = $MEDIA\n" | tr '.' ',') >> resultados

        let TEMPO=0 #ok
        let AUX=0 #ok
        let MEDIA=0 #ok

        let NP=${NP}*2 #ok
    done 

    let NP=1
    
exit 0