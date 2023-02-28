#include "climb_chromosome.hh"
#include <algorithm>
#include <random>
#include <cassert>

ClimbChromosome::ClimbChromosome(const Cities* cities_ptr)
	: Chromosome(cities_ptr){
    assert(is_valid());
}

std::pair<ClimbChromosome*, ClimbChromosome*>
ClimbChromosome::recombine(const ClimbChromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());

  // need to include size() because create_crossover_child takes [b, e):
  std::uniform_int_distribution<int> dist(0, order_.size());

  // Pick two random indices such that b <= e:
  auto r1 = dist(generator_);
  auto r2 = dist(generator_);
  auto [b, e] = std::minmax(r1, r2);

  // Make children:
  auto child1 = create_crossover_child(this, other, b, e);
  auto child2 = create_crossover_child(other, this, b, e);

  return std::make_pair(child1, child2);
}
//local hill climbing: searches for the best solution in a
//neighborhood of the current chromosome
void ClimbChromosome::mutate(){
   //evaluate the fitness of the current chromosome
   double fit = get_fitness();
  
   //pick a random point p in the chromosome
   std::uniform_int_distribution<int> dis(0,order_.size() -1);
   unsigned p = dis(generator_);
   //Swap the city at index p with the city at index p-1 
   //and evaluate the resulting chromosome's fitness.
   auto begin = order_[p];
   auto end = order_[p];
   if(p==0)	end = order_[order_.size() -1];
   else         end = order_[p-1];
   std::swap(begin, end);
   assert(is_valid());
   auto fit1 = get_fitness();

   //reverse swap
   std::swap(begin, end);

   //swap the city at index p from original chromosome with the city at index
   //p+1 and evaluate the resulting chromosome's fitness.
   //If p==N-1, swap with the city at index 0 instread of at index N using mod

   auto end1 = order_[p];
   if(p == order_[order_.size() - 1])	end1 = order_[0];
   else					end1 = order_[p+1];
   std::swap(begin, end1);
   auto fit2 = get_fitness();

   //reverse swap
   std::swap(begin, end1);

   //find the best fitness
   if(fit1 > fit){
	   if(fit1 > fit2){
		   std::swap(begin, end);
	   }
	   else{
		   std::swap(begin, end1);
	   }
   }

   else if(fit2 > fit){
	   if(fit2 > fit1){
		   std::swap(begin, end1);
	   }
	   else{
		   std::swap(begin, end);
	   }
   } 

}

ClimbChromosome* ClimbChromosome::clone() const
{
	return new ClimbChromosome(*this);
}
ClimbChromosome*
ClimbChromosome::create_crossover_child(const ClimbChromosome* p1, const ClimbChromosome* p2,
                                   unsigned b, unsigned e) const
{
  const unsigned len = p1->order_.size();
  assert(len == p2->order_.size());
  ClimbChromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < len && j < len; ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
      }
      assert(j < len);
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}
