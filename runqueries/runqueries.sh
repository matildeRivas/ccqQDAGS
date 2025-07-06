#!/bin/bash
input_folder="patterns"
output_folder="runqueries/outputs"

declare -A ghd_confs
ghd_confs=(
    ["bowtie"]="1"
    ["j3_ghd"]="3"
    ["j4_ghd"]="3"
    ["triangle_barbell"]="1"
    ["triangle_tadpole"]="1"
    ["ti4_ghd"]="3"
    ["square_tadpole"]="1"
    ["square_barbell"]="1"
    ["penta_barbell"]="1"
    ["t3_ghd"]="3"
    ["t4_ghd"]="3"
    ["ti3_ghd"]="3"
)

for pattern in "bowtie" "j3_ghd" "j4_ghd" "ti4_ghd" "t3_ghd" "t4_ghd" "ti3_ghd" "triangle_tadpole" "square_tadpole" "triangle_barbell" "square_barbell" "penta_barbell"
do
    params_file="${input_folder}/${pattern}.txt"
    # create output file
    output_file="${output_folder}/ha_${pattern}_mj.txt"
    touch $output_file
    i=1

    while IFS= read -r params; do
        printf "\nRunning ${pattern} - mj - ${i}:\n\t${params}\n"
        i=$((i+1))
        # Run the program with a timeout
        timeout 1800 ./build/${pattern} $params mj $output_file 0
        exit_code=$?

        # check errors
        if  [ $exit_code -eq 124 ]; then
            echo "timeout" >> $output_file
            echo "##### timeout #####"
        elif [ $exit_code -eq 139 ]; then
            echo "segfault" >> $output_file
            echo "##### segfault #####"
        fi
    done < ${params_file}

    for method in "yk" "yk_par"
    do
        for (( ghd_conf=1; ghd_conf<=${ghd_confs[$pattern]}; ghd_conf++ ));
        do
            # create output file
            output_file="${output_folder}/ha_${pattern}_${method}_${ghd_conf}.txt"
            touch $output_file
            i=1

            while IFS= read -r params; do
                printf "\nRunning ${pattern}_${method}_${ghd_conf} ${i}:\n\t${params}\n"
                i=$((i+1))
                # Run the program with a timeout
                timeout 1800 ./build/${pattern} $params $method $output_file $ghd_conf
                exit_code=$?

                # check errors
                if  [ $exit_code -eq 124 ]; then
                    echo "timeout" >> $output_file
                    echo "##### timeout #####"
                elif [ $exit_code -eq 139 ]; then
                    echo "segfault" >> $output_file
                    echo "##### segfault #####"
                fi
            done < ${params_file}
        done
    done
done
