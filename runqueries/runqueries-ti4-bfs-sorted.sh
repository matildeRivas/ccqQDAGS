output_file="/home/anouk/Documents/qdags/qdags-main/runqueries/outputs/ti4_mj.txt"
params_file="/home/anouk/Documents/wikidata/property_getter/query-pattern-finder/ti4.txt"


while IFS= read -r params; do
    # Run the program with a timeout
    echo "Running experiment with parameters: $params"
    timeout 1800 ./ti4_ghd $params

    # Check if the program timed out
    if [ $? -eq 124 ]; then
        # Log the timeout message
        echo "timeout"
        echo "timeout" >> "$output_file"
    fi
done < "$params_file"
