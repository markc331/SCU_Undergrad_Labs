// FILE: rand_gen.cpp
// CLASS IMPLEMENTED: rand_gen (see rand_gen.h for documentation)

#include "random.h"

namespace coen79_lab2 {
    
    //Constructor
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus) {
        assert(modulus != 0);
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }
    
    void rand_gen::set_seed(int new_seed) {
        seed = new_seed;
    }
    
    int rand_gen::next() {
        int num = (multiplier * seed + increment) % modulus;
        set_seed(num);
        return num;
    }
    
    void rand_gen::print_info() {
        cout << "seed: " << seed << "\n";
        cout << "multiplier: " << multiplier << "\n";
        cout << "increment: " << increment << "\n";
        cout << "modulus: " << modulus << "\n";
    }
}
