Dubin Nam, Alonzo Ortiz-Sanchez

Chromosome.cc: 

Constructor:
Just a simple constructor consisting of cities_ptr_, order_, generator_, and size_ for the initial size

Mutate: 
1. we created a random permutation with the size of city ptr, then two variables for the back 
   element and front element of the random permutation. 
2. Next, we obtained the random positions of those two elements and saved them
3. Trade the spots of those two positions

Recombine:
1. we created a random permutation with the size of city ptr, then two variables for the back 
   element and front element of the random permutation. 
2. Next, we obtained the random positions of those two elements and saved them.
3. if the position 1 is bigger than the position 2, trade positions.
4. Then we use the given create_crossover_child to recombine and make new children
5. Now a new pair has been generated. 
Create_crossover_child:
1. This is a given helper function for Recombine.

Get_fitness: 
1. fitness is the total path distance of a permutation, so just return calculate_total_distance().

Is_valid:
1. This method checks whether a chromosome has repeated values or indices above the range. 
2. A vector "newPermutation" created for comparison. 
3. We used std::is_permutation to check it 
4. It returns true only if the random permutation is a valid permutation.

Is_in_range:
1. We set a for loop to scan from "begin" to "end" of                random_permutation, and if "value" is detected within the range    of random_permutation, it returns true.
