#!/bin/sh

# TODO: pass in folders as parameters, could be an env file for the docker-compose
input_folder="patterns"
output_folder="runqueries/outputs"

# TODO: run all patterns inside a for
pattern="bowtie"

for pattern in "bowtie" "j3_ghd" "j4_ghd" "tr_barbell" "triangle_tadpole" "ti4_ghd" "square_tadpole" "square_barbell" "penta_barbell"
do
    params_file="${input_folder}/${pattern}.txt"
    for method in "yk" "yk_par" "mj"
    do
        # create output file
        output_file="${output_folder}/ha_${pattern}_${method}_1.txt"
        touch $output_file
        i=1

        while IFS= read -r params; do
            printf "\nRunning ${pattern} - ${method} - ${i}:\n\t${params}\n"
            i=$((i+1))
            # TODO: add variations per pattern as a new parameter
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
            break
        done < ${params_file}
    done
done
