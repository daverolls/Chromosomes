/*
 * Declarations for Chromosome class to be used in a genetic algorithm (GA) to
 * approximate the traveling-salesperson problem (TSP).
 * A chromosome represents a permutation on the orders of the cities to visit.
 * Includes common GA operators: mutate and recombine.
 * This class doesn't allow default construction and copying, to preserve
 * polymorphism. The only way to create a Chromosome class is via the create()
 * method, and the only way to copy one is via the clone() method.
 */

#pragma once

#include "cities.hh"
#include <random>
#include <iostream>
#include <map>

class Chromosome {
   // Disable public copying of objects for polymorphism:
    Chromosome(const Chromosome&) = default;
    Chromosome(Chromosome&&) = default;
    Chromosome& operator=(const Chromosome&) = default;
    Chromosome& operator=(Chromosome&&) = default;
 public:
  // Creation method for new Chromsomoe. Saves a copy of the cities and
  // generates a completely random permutation from a list of cities.
  Chromosome(const Cities*);

  // Polymorphic creation method from an existing Chromosome.
  // This method allocates memory for the newly created chromosome.
  // It is the caller's responsibility to free this memory.
  virtual Chromosome* clone() const
  {
    return new Chromosome(*this);
  }

  // Clean up as necessary
  virtual ~Chromosome();

  // Perform a single mutation on this chromosome: swap two random cities.
  virtual void mutate();

  // Return a pair of offsprings by recombining with another chromosome
  // Note: this method allocates memory for the new offsprings
  // It is the caller's responsibility to free this memory.
  virtual std::pair<Chromosome*, Chromosome*>
  recombine(const Chromosome* other);

  // Compute total distance to traverse cities in ordering:
  double calculate_total_distance() const
  {
    return cities_ptr_->total_path_distance(order_);
  }

  // Return a positive fitness value, with higher numbers representing
  // fitter solutions (shorter total-city traversal path).
  virtual double get_fitness() const;

  // Return an immutable reference to the city ordering.
  const Cities::permutation_t& get_ordering() const
  {
    return order_;
  }

 protected:
  // For an ordered set of parents, return a child using the ordered crossover.
  // The child will have the same values as p1 in the range [begin,end),
  // and all the other values in the same order as in p2.
  virtual Chromosome*
  create_crossover_child(const Chromosome* parent1,
                         const Chromosome* parent2,
                         unsigned begin,
                         unsigned end) const;

  // A chromsome is valid if it has no repeated values in its permutation,
  // as well as no indices above the range (length) of the chromosome.
  bool is_valid() const;

  // Find whether a certain value appears in a given range of the chromosome.
  // Returns true if value is in order_ within the specified the range specified
  // [begin, end) and false otherwise.
  bool is_in_range(unsigned value, unsigned begin, unsigned end) const;

  unsigned int size_;  // How it initially began
  const Cities* cities_ptr_; // Keep ptr to cities, no need for full copy
  Cities::permutation_t order_;  // The actual permutation of this chromosome

  std::default_random_engine generator_; // A random number generator for the various methods


private:
  // For other stuff here
};
