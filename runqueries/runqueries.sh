pattern="square_barbell"
params_file="/mnt/c/Users/crist/Documents/query-pattern-finder/${pattern}.txt"

for method in "yk" "yk_par" "mj"
do
    # create output file
    output_file="/mnt/c/Users/crist/Documents/ccqQDAGS/runqueries/outputs/ha_${pattern}_${method}.txt"
    touch $output_file

    while IFS= read -r params; do
        # Run the program with a timeout
        printf "Running ${pattern} - ${method} with parameters:\n\t${params}\n"
        timeout 1800 ./build/${pattern} $params $method $output_file
        
        # check errors
        if  [ $? -eq 124 ]; then
            echo "timeout" >> $output_file
        elif [ $? -eq 139 ]; then
            echo "segfault" >> $output_file
        fi
    done < $params_file
done
