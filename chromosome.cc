/*
 * Implementation for Chromosome class
 */


#include <algorithm>
#include <cassert>
#include <random>
#include "chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(rand())
{
  size_ = order_.size();      // Keeping track of the size it began with
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{
  std::vector<unsigned int> newPermutation; //Giving a vector so it can be randommized
  for (unsigned int i = 0; i < size_; ++i) { newPermutation.push_back( i ); } //a new permutation of all the numbers from 0 to len-1

  std::random_device randomDevice; //random_device is a integer random number generator
  std::mt19937 generator(randomDevice()); //Pseudo-random generator of 32-bit numbers with a size of 19937 bits
  std::shuffle(begin(newPermutation), end(newPermutation), generator); //using std::shuffle to "shuffle"

  // Obtianing our two new randomly choosen positions to check in "order".
  unsigned int randPos1 = newPermutation.pop_back();
  unsigned int randPos2 = newPermutation.pop_back();

  // Obtaining position of the cities
  auto randCity1 order.at(randPos1);
  auto randCity2 order.at(randPos2);

  // Saving their new position by our modification
  order[randPos1] = randCity2;
  order[randPos2] = randCity1;

  // Debugging
  //for (auto iterate : order) { std::cout << iterate << " "; }
  //std::cout << "\n" << randCity1 << ":" << randCity2 << std::endl;

  //Might need to clear memory

  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());

  // Add your implementation here
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
        assert(j < p2->order_.size());
      }
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  auto fitness=calculate_total_distance();// fitness would be the total path distance of a permutation
  return fitness;
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
bool
Chromosome::is_valid() const
{

  if(<order_.size())// If the size of the chromosome is bigger or smaller than
    return false;    // the sizes of parents chromosomes, it returns false.
  else if(>order_.size())
    return false;
  if (std::is_permutation(order_.begin(), order_.end())) { return true; } // make sure there's no repeated value in the permutation.
  return false;

  // Debugging
  //for (auto iterate : order) { std::cout << iterate << " "; }
  //std::cout << "\n" << std::endl;

}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  for ( unsigned int i = begin-1 /*Assuming it will always begin >= 1*/; i < end; ++i ){
    if ( value == order_[i]) { return true; }
    // Debugging
    // std::cout << i << "-";
  }
  // std::cout << std::endl;
  return false;
}
