#!/bin/bash
# vai ser utilizado para a MEDIÇÃO DE TEMPO 
# $1 = 1, roda o custom, $1  = 0, roda o normal
# $2 - root
# $3 - número de cores do computador

NP=1
TEMPO=0
MEDIA=0
AUX=0
SIZES=(1024 2048 4096 8192 16384 32768 65536 131072)
ISCUSTOM=""

    if [ $1 -eq 1 ]; then
        ISCUSTOM="[--custom]"
    fi
    
    echo $(make)

    echo -e "" > resultados.txt
    echo -e "\nRESULTADO DOS TESTES\n" >> resultados.txt

    for size in ${SIZES[@]}; do
        echo -e "\narray_size= $size\n" >> resultados.txt

        let NP=1
        while [ $NP -le 8 ]; do

            echo -e "\nnp= "${NP} "\n" >> resultados.txt

            for i in $(seq 1 10); do

                if [ $NP -le $3 ];then
                    AUX=$(mpirun -np ${NP} ./broadcast --array_size 1024 [--root $2] ${ISCUSTOM})
                elif [ $NP -gt $3 ];then
                    AUX=$(mpirun --oversubscribe -np ${NP} ./broadcast --array_size 1024 [--root $2] ${ISCUSTOM})
                fi

                echo -e ${AUX}"\n" >> resultados.txt
                TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
            done

            MEDIA=$(echo "${TEMPO}/10" | bc -l)
            echo -e "media = "$MEDIA"\n" >> resultados.txt

            let TEMPO=0 #ok
            let AUX=0 #ok
            let MEDIA=0 #ok

            let NP=${NP}*2 #ok
        done
    done 

exit 0
