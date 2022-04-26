/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////////
// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
{
  // Defining
  mut_rate_ = mut_rate;
  pop_size_ = pop_size;

  // Constructing our population based on math
  for (unsigned int i = 0; i <= pop_size; ++i) { pop_.push_back(new Chromosome( cities_ptr )); }
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Deme::~Deme()
{
  for (auto chrome : pop_ ) { delete chrome; }
}

//////////////////////////////////////////////////////////////////////////////
// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  // Preparing
  std::vector<Chromosome*> swapPop;
  int max = floor((pop_size_)/2);
  for (int i = 0; i < max; ++i){
    Chromosome* const parent1 = select_parent();
    Chromosome* const parent2 = select_parent();

    // Might mutate parent
    if ( myrandom_double() < mut_rate_ ) { parent1->mutate(); }
    if ( myrandom_double() < mut_rate_ ) { parent2->mutate(); }

    // Generating our child pair
    auto childPair = parent1->recombine(parent2);
    swapPop.push_back(childPair.first);
    swapPop.push_back(childPair.second);
  }
  // Cleaning up memory
  for (auto chrome : pop_ ) { delete chrome; }    // Possible fix to memory error
  trial.clear();
  pop_ = swapPop; // Recreating population
}

//////////////////////////////////////////////////////////////////////////////
// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  // Finds best chromsome based on the lambda with stl.
  return *std::max_element(pop_.cbegin(), pop_.cend(), []( auto pointerOne, auto pointerTwo ){ return pointerOne->get_fitness() < pointerTwo->get_fitness(); });
}

//////////////////////////////////////////////////////////////////////////////
// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
//
// It now also uses something called "Fitness proportion selection"
// Where it tries to increase probability by knowing the sum total primarely and dividing it.
// Before applying the randomness found
Chromosome* Deme::select_parent()
{
  // Construct the vector that randomness will use
  if (trial.size() == 0){

    double lowest = (*std::min_element(pop_.cbegin(), pop_.cend(), []( auto pointerOne, auto pointerTwo ){ return pointerOne->get_fitness() < pointerTwo->get_fitness();}))->get_fitness();
    double total = get_fitness_proportion_total();
    for ( auto chromeptr : pop_ ){
      double endurance = lowest / total;
      for ( double currentFitness = (chromeptr->get_fitness() / total); currentFitness > 0; currentFitness -= endurance ){
        trial.push_back(chromeptr);    // Adding it to the main table it will use
      }
    }
  }
  // Randomness based on how big "trail" is
  std::uniform_int_distribution<int> distribution(0, (trial.size()-1));
  int result = (distribution(generator_));
  return trial[result];
}
