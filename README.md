Dubin Nam, Alonzo Ortiz-Sanchez

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
3. If the position 1 is bigger than the position 2, trade positions.
4. Then we use the given create_crossover_child to recombine and make new children
5. Now a new pair has been generated. 
Create_crossover_child:
1. This is a given helper function for Recombine.

Get_fitness: 
1. Fitness is the total path distance of a permutation, so just return calculate_total_distance().

Is_valid:
1. This method checks whether a chromosome has repeated values or indices above the range. 
2. A vector "newPermutation" created for comparison. 
3. We used std::is_permutation to check it 
4. It returns true only if the random permutation is a valid permutation.

Is_in_range:
1. We set a for loop to scan from "begin" to "end" of random_permutation, and if "value" is detected within the range of random_permutation, it returns true.

----------------------------------------------------------------------------------------------------
<Deme.cc>

Constructor:
Mut_rate, pop_size, and the cities_ptr->size()-1.
Random population constructor.

Myrandom:
A helper function we implemented to use in compute_next_generation. It's a double type random number generator.

Compute_next_generation:
1. Select pop_size/2 pairs of chromosomes by using "select_parent()" in the for loop
2. Give a chance to each parent by using "Myrandom" to see if they will mutate based on "mut_rate"
3. We then create a pair of children from the two parents using "recombine"
4. Finally push it back to a vector holding all of the new children and end loop
5. To ensure memory is cleared. We reset some values for other functions, such as "total", "highest", and "organizedChance" back to 0
6. Then we delete all of the old chromosomes in "pop_" before saving the children into "pop_"

Get_best:
1. We have some starting values defined
2. Using a for loop, we iterate all of the chromosomes
3. Each chromosome is checked against the currently saved lowest value
4. If the current chromosome surpasses our lowest value by being lower, we save it
5. returns the pointer to the best chromosome

Select_parent():
1. We have an empty vector list so compiler doesn't yell
2. Essentially, if select_parent is called for the first time (based on if organizedChance.size() == 0), we create and fill "frequencyOfApperance".
3. First we begin to iterate against "pop_" for all of the current chromosomes in for loop
4. Than we are trying to keep track of two values. The highest known chromosome value, and the total sum of all chromosomes
5. Than we same the current chromosome into a pair (which is only used for the vector) to save the pointer of chromosome and its fitness
6. End for loop
7. Than we initiate a second seperate for loop where it now iterates the saved pairs from "frequencyOfApperance"
8. Within the for loop, we nest another loop where it has "frequencyOfChrome" = highest fraction, until "chromeValye" fitness <= than the total sum, and we add "frequencyOfChrome" to the current fitness saved in "chromeValue"
9. Everytime the nested for loop is ran, we add the chromosome pointer into "organizedChance"
10. Finally all for loops end
11. Then, regardless if this is ran for the first time or not. We take a random index integer to get a chromosome pointer
12. Which the chromosome pointer is returned

Why is select_parent() the way it is?

Select_parent() was based around "Fitness proportion selection", however I made changes that will be explained shortly.
"Fitness proportion selection" is used to give a bias for bigger numbers. We want a bias to smaller numbers, thus it has to be done inversely.
First "Fitness proportion selection" (FPS) requires a total sum. Easy enough
Second FPS requires the individual numbers that are being randomly selected, to be divded by a total sum before then increasing the current size of the selection to match some frequency
Third FPS's frequency is based on dividing all numbers by the total number, than it does something that requires the smallest fraction from the selection.

Thus; I did it inversely. Instead of a smallest fraction, I used the biggest fraction from the selection.
This allows the bigger values to be knocked off early, and leaving behind the smaller ones.

Valgrind: No memory leaks! Or atleast that what it claims

Command used:
1. g++ -g -Wall -Wextra -pedantic -Werror -std=c++17 cities.cc chromosome.cc deme.cc tsp.cc -o tsp
2. "./tsp challenge.tsv 100 0.0005" which gives an estimate between 13k (worst) to 9k (best)
3. Absolute lowest so far with the command above is 10095.2 It will have its photo as well from gnuplot
