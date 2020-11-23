#!/bin/bash

mkdir results
for cores in 1 2 3 6 12 24 48 96; do
	echo -n $cores >> times-int.csv
	echo -n $cores >> times-csv-name.csv
	echo -n $cores >> times-csv-date.csv

	for run in 1 2 3 4 5; do
		echo -n , >> times-int.csv
		./sort $cores -i 1000000000 results/int-${cores}cores-${run}-unsorted results/int-${cores}cores-${run} >> times-int.csv
		diff -q <(sort -n results/int-${cores}cores-${run}-unsorted) results/int-${cores}cores-${run}

		echo -n , >> times-csv-name.csv
		./sort $cores -a -n alumni.csv results/csv-name-${cores}cores-${run} >> times-csv-name.csv
		diff -q results/csv-name-1cores-1run results/csv-name-${cores}cores-${run}

		echo -n , >> times-csv-date.csv
		./sort $cores -a -d alumni.csv results/csv-date-${cores}cores-${run} >> times-csv-date.csv
		diff -q results/csv-date-1cores-1run results/csv-date-${cores}cores-${run}
	done

	echo >> times-int.csv
	echo >> times-csv-name.csv
	echo >> times-csv-date.csv
done
