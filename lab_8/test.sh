#!/bin/bash
make;
./gen_test
echo
echo "----------FIFO----------"
cat testInput.txt | ./FIFO 10 
echo
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./LRU 10 
echo
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./2_chance 10
echo
echo "----------End Second Chance----------"
echo
echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./FIFO 10
cat accesses.txt | ./FIFO 50
cat accesses.txt | ./FIFO 100
cat accesses.txt | ./FIFO 250
cat accesses.txt | ./FIFO 500
echo
echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./LRU 10
cat accesses.txt | ./LRU 50
cat accesses.txt | ./LRU 100
cat accesses.txt | ./LRU 250
cat accesses.txt | ./LRU 500
echo
echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./2_chance 10
cat accesses.txt | ./2_chance 50
cat accesses.txt | ./2_chance 100
cat accesses.txt | ./2_chance 250
cat accesses.txt | ./2_chance 500
echo
make clean;
echo