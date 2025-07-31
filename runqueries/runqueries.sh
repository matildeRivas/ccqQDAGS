#!/bin/bash
input_folder="patterns"
output_folder="runqueries/outputs"

for pattern in "bowtie" "j3_ghd" "j4_ghd" "ti4_ghd" "triangle_tadpole" "t3_ghd" "t4_ghd" "ti3_ghd"
do
    params_file="${input_folder}/${pattern}.txt"

    for method in "mj" "yk_par" "yk"
    do
        # create output file
        output_file="${output_folder}/${pattern}_${method}.txt"
        touch $output_file
        i=1

        while IFS= read -r params; do
            printf "\nRunning ${pattern}_${method} ${i}:\n\t${params}\n"
            i=$((i+1))

            # Run the program with a timeout
            timeout 1800 ./build/${pattern} $params $method $output_file
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
