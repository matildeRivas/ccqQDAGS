output_file="/home/anouk/Documents/qdags/qdags-main/runqueries/outputs/triangle_barbell_yk.txt"
params_file="/home/anouk/Documents/wikidata/property_getter/query-pattern-finder/tr_barbell.txt"


while IFS= read -r params; do
    # Run the program with a timeout
    echo "Running experiment with parameters: $params"
    timeout 1800 ./tr_barbell $params

    # Check if the program timed out
    if [ $? -eq 124 ]; then
        # Log the timeout message
        echo "timeout" >> "$output_file"
    fi
done < "$params_file"
