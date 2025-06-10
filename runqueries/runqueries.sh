pattern="ti4_ghd"
params_file="/mnt/c/Users/crist/Documents/query-pattern-finder/${pattern}.txt"

for method in "yk" "yk_par" # "mj"
do
    # create output file
    output_file="/mnt/c/Users/crist/Documents/ccqQDAGS/runqueries/outputs/ha_${pattern}_${method}_2.txt"
    touch $output_file
    i=1

    while IFS= read -r params; do
        printf "\nRunning ${pattern} - ${method} - ${i}:\n\t${params}\n"
        ((i++))

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
