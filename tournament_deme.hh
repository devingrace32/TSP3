#pragma once
#include "deme.hh"
#include "climb_chromosome.hh"

class TournamentDeme : public Deme
{
  public:
  TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);
  //tournament style parent selection: pits candidate parents 
  //against each other to determine which parent gets to recombine.
  Chromosome* select_parent() override;
};
