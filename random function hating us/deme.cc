/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
{
  // Defining
  mut_rate_ = mut_rate;
  pop_size_ = pop_size;
  size_ = cities_ptr->size()-1;

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
// A simple helper function to help us get a random value
// The random value is fixed between [0-1)
double myrandom () { return (double)rand()/(RAND_MAX + 1.0)+12+(rand()%5); }

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
    if ( myrandom() < mut_rate_ ) { parent1->mutate(); }
    if ( myrandom() < mut_rate_ ) { parent2->mutate(); }

    // Generating our child pair
    auto childPair = parent1->recombine(parent2);
    swapPop.push_back(childPair.first);
    swapPop.push_back(childPair.second);
  }
  // Cleaning up memory
  for (auto chrome : pop_ ) { delete chrome; }    // Possible fix to memory error
  total = 0;
  pop_ = swapPop; // Recreating population
}

//////////////////////////////////////////////////////////////////////////////
// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  // Defining
  Chromosome* bestChrome;
  double absoluteLowest = -1.0;    // It's impossible for negative number, so its a good first case

  // Iterate all of the population
  for ( auto chrome : pop_) {
    //std::cout << chrome->get_fitness() << std::endl;
    if ( absoluteLowest > chrome->get_fitness() || absoluteLowest < 0 ) {
      bestChrome = chrome;
      absoluteLowest = bestChrome->get_fitness();
    }
  }
  return bestChrome;
}

//////////////////////////////////////////////////////////////////////////////
// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
//
// It now also uses something called "Fitness proportion selection"
// However it's made inversely from the actual implementation
Chromosome* Deme::select_parent()
{
  //
  get_fitness_proportion_total();

//
  double randNum = myrandom();
  double probability = 0;
  std::cout << randNum << std::endl;

  //
  for ( auto chromeptr : pop_ ){   // save the fractions of probability for each chromosome to be choosen
    probability += ((chromeptr->get_fitness())/total);
    if ( probability > randNum ) { return chromeptr; }
  }
  assert(nullptr);
  return nullptr;
}
