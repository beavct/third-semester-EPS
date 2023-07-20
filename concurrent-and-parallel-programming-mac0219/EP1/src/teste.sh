#!/bin/bash
# parâmetros: ./teste.sh 1<time_test ou check> 2<grid_size> 3<num_threads> 4<omp/pth/seq>

TEMPO=0
AUX=0
    
    echo -e "\nRESULTADO DOS TESTES\n" 

    if [ $1 == "check" ];then
        echo $(make check)
        echo $(./check --grid_size $2 --num_threads $3)

    elif [ $1 ==  "time_test" ];then
        echo $(make time_test)
        echo -e "\n"
        
        for i in $(seq 1 10); do
            AUX=$(echo "$(./time_test --grid_size $2 --impl $4 --num_threads $3)" | bc -l)
            TEMPO=$(echo "${TEMPO}+${AUX}" | bc -l)
            echo $(echo "${AUX}" | tr '.' ',')
        done

        TEMPO=$(echo "${TEMPO}/10" | bc -l) 

        echo -e "\ngrid_size = $2\nnum_threads = $3\nmétodo = $4\n" 
        echo -e $(echo "tempo = $TEMPO" | tr '.' ',')
    fi

exit 0
