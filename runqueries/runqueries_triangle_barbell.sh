output_file="/mnt/c/Users/crist/Documents/ccqQDAGS/runqueries/outputs/ha_triangle_barbell_mj.txt"
params_file="/mnt/c/Users/crist/Documents/query-pattern-finder/tr_barbell.txt"
touch $output_file

while IFS= read -r params; do
    # Run the program with a timeout
    echo "Running experiment with parameters: $params"
    timeout 1800 ./build/triangle_barbell $params

    # Check if the program timed out
    if [ $? -eq 124 ]; then
        # Log the timeout message
        echo "timeout" >> "$output_file"
    fi
done < "$params_file"
