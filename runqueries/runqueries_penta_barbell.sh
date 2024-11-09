output_file="/home/anouk/Documents/qdags/qdags-main/runqueries/outputs/penta_barbell_mj.txt"
params_file="/home/anouk/Documents/wikidata/property_getter/query-pattern-finder/penta_barbell.txt"


while IFS= read -r params; do
    # Run the program with a timeout
    echo "Running experiment with parameters: $params"
    timeout 1800 ./penta_barbell $params

    # Check if the program timed out
    if [ $? -eq 124 ]; then
        # Log the timeout message
        echo "timeout" >> "$output_file"
    fi
done < "$params_file"
