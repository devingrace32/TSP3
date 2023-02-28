#pragma once
#include "chromosome.hh"

class ClimbChromosome : public Chromosome
{
  public:
  ClimbChromosome(const Cities*);

  ClimbChromosome* clone() const override;

  std::pair<ClimbChromosome*, ClimbChromosome*>
		recombine(const ClimbChromosome* other);
  
  //local hill climbing: searches for the best solution in a 
  //neighborhood of the current chromosome
  void mutate() override;
  ClimbChromosome* create_crossover_child(const ClimbChromosome* mother,
		  const ClimbChromosome* father,
		  unsigned begin,
		  unsigned end) const;
};
