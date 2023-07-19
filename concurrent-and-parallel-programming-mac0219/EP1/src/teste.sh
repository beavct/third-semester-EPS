#!/bin/bash
# parâmetros: 1<time_test ou check> 2<grid_size> 3<num_threads> 4<omp/pth/seq>

# não sei se o bash script ta fazendo certinho pq as vezes uns testes parecem ser muito rápidos

TEMPO=0
AUX=0

    if [ $1 == "check" ];then
        echo $(make check)
        echo $(./check --grid_size $2 --num_threads $3)

    elif [ $1 ==  "time_test" ];then
        echo $(make time_test)
        
        for i in $(seq 1 10); do
            #echo $(./time_test --grid_size $2 --impl $4 --num_threads $3)
            TEMPO=$(echo "$(./time_test --grid_size $2 --impl $4 --num_threads $3)+${TEMPO}" | bc -l)
        done

        TEMPO=$(echo "${TEMPO}/10" | bc -l) 

        echo -e "\nRESULTADO DOS TESTES\n" 
        echo -e "grid_size = $2\nnum_threads = $3\n" 
        echo -e "tempo = $TEMPO"
    fi

exit 0