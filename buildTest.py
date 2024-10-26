
with open('/home/anouk/Documents/wikidata/property_getter/query-pattern-finder/tr_barbell.txt') as file:
    with open('/home/anouk/Documents/qdags/qdags-main/runqueries/runqueries_triangle_barbell.sh', 'a') as out:
        for line in file:
            prop = line.split(',')
            out.write(f"./tr_barbell ../data/prop-direct-{prop[0]} ../data/prop-direct-{prop[1]} ../data/prop-direct-{prop[2]} ../data/prop-direct-{prop[3]} ../data/prop-direct-{prop[4]} ../data/prop-direct-{prop[5]} ../data/prop-direct-{prop[6]}")
