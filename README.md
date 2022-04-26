Dubin Nam, Alonzo Ortiz-Sanchez

Asked for extension, and was told to write it here that it was "approved late".

---------------------------------------------------------------------------------------------------- 

<Chromosome.cc>

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
1. This function wants to give bigger "fit" number to the smaller value when computing the total distance of the cities.
2. This is done by simply taking the inverse. (1 / total_path_distance())

Is_valid:
1. This method checks whether a chromosome has repeated values or indices above the range. 
2. A vector "newPermutation" created for comparison. 
3. We used std::is_permutation to check it 
4. It returns true only if the random permutation is a valid permutation.

Is_in_range:
1. We set a for loop to scan from "begin" to "end" of random_permutation, and if "value" is detected within the range of random_permutation, it returns true.

Myrandom:
A helper function we implemented to use in compute_next_generation. It's a int type random number generator.
Which returns from the range [0-size of cities)

----------------------------------------------------------------------------------------------------
<Deme.cc>

Constructor:
Mut_rate, pop_size, and the cities_ptr->size()-1.
Random population constructor.

Myrandom:
A helper function we implemented to use in compute_next_generation. It's a double type random number generator.
Which returns from the range [0-1)

Compute_next_generation:
1. Select pop_size/2 pairs of chromosomes by using "select_parent()" in the for loop
2. Give a chance to each parent by using "Myrandom" to see if they will mutate based on "mut_rate"
3. We then create a pair of children from the two parents using "recombine"
4. Finally push it back to a vector holding all of the new children and end loop
5. To ensure memory is cleared. We reset some values for other functions, such as "total", "highest", and "organizedChance" back to 0
6. Then we delete all of the old chromosomes in "pop_" before saving the children into "pop_"

get_best:
1. We have some starting values defined
2. Using a for loop, we iterate all of the chromosomes
3. Each chromosome is checked against the currently saved lowest value
4. If the current chromosome surpasses our lowest value by being lower, we save it
5. returns the pointer to the best chromosome

get_fitness_proportion_total:
1. A simple helper function to obtain the sum total of fitness from all chromosomes

select_parent():
0. If this is a new populaiton made recently. We do steps 1-5. Otherwise we go directly to 6
1. Uses helper function to obtain total sum of fitness
2. Uses a lambda and a stl function called "min_element" to obtain the lowestest number found in "pop_->get_fitness()"
3. iterate all chromosomes in "pop_" 
4. Uses "endurance" which is the lowest number found and is used to subtract on the second for loop some fitness value.
5. Essentially. If the current fitness value is fairly high, than endurance will barely make a dent. Allowing the second loop to keep adding in "trial" the pointer of the current chromosome. Otherwise it essentially it will add less to "trial"
6. Then we use a stl random function to choose a random index in "trial"
7. Return the chromsome saved in trail

Valgrind: No memory leaks! Or atleast that what it claims

Command used: "./tsp challenge.tsv 10 0.0075" which gives an estimate between 17k (worst) to 13k (best)
