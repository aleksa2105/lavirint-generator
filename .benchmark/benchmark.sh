#!/bin/bash


# To use script first modify limits in maze_generator/Settings.h 
# Second, make sure to comment out Game::run function inside main.cpp
# Third, save generation time to ".benchmark/time.txt"

# Path to executable
EXEC="build/maze"
RESULT_FILE=".benchmark/benchmark.csv" # Output file for benchmark
echo "rows,cols,items,time" > $RESULT_FILE

TIME_FILE=".benchmark/time.txt" # Temporary file that saves generation time for each run

# Loop through different sizes
for rows in {15..515..50}; do
	for cols in {15..515..50}; do
		items=3
		$EXEC $rows $cols $items > /dev/null
		TIME=$(cat $TIME_FILE)
		echo "$rows,$cols,$items,$TIME" >> $RESULT_FILE
		echo "$rows,$cols,$items,$TIME"
	done
done

# remove time temp file
rm $TIME_FILE
