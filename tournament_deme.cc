#include "tournament_deme.hh"
#include <algorithm>
#include <random>
#include <cmath>

//tournament style parent selection: pits candidate parents 
//against each other to determine which parent gets to recombine.
TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
 :Deme(cities_ptr,pop_size,mut_rate){}

Chromosome* TournamentDeme::select_parent(){

// Find P where P is the greatest power of 2 less than than the population size
    int P=2;
    /*for(int i=1;pow(2,i)<=pop_.size();i++){                  
        P=pow(2,i);
    }*/

//Select P parents at random
    std::random_shuffle(pop_.begin(), pop_.end());
    std::vector<Chromosome*> candidateParents;
    for(int i=0; i<P; i++){
        candidateParents.push_back(pop_[i]);
    }

//Tournament style elimanates 1/2 of the parents each round until only 1 remains
    while(candidateParents.size()!=1){
    //Where winning parents are stored
        std::vector<Chromosome*> nextParents;
    //Removes parents two at a time saving the one with a higher fitness
        while(candidateParents.size()>0){
        
        //Chose 2 parents
            auto parent1=candidateParents.back();
	    candidateParents.pop_back();
            auto parent2=candidateParents.back();
	    candidateParents.pop_back();
        
        //Determins witch parent is more fit and saves it
            if(parent1-> get_fitness() > parent2 ->get_fitness()){
                nextParents.push_back(parent1);
            }
            else{nextParents.push_back(parent2);}
        }
    
    //Sets Next Generation of candidateParents
    candidateParents = nextParents;
    nextParents.clear();
    }
    return candidateParents[0];

}
