#include "random.h"
#include <iostream>

using namespace std;
using namespace coen79_lab2;

// Main Functions

void printNumbers(rand_gen &r, int num) {

    for (int i = 0; i < num; i++) {
        r.print_info();
        cout << "Next: " << r.next() << endl;
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    // should output 1,2,3,4,5
    // testing for seed 0, increment 1, multiplier 1, standard modulo
    rand_gen myrg0(0, 1, 1, 729);
    printNumbers(myrg0, 5);  

    // should output 0,1,1,1,1 because multiplier is 0
    // testing for seed 0, multiplier 0, increment 1, standard modulo
    rand_gen myrg1(0, 0, 1, 729);
    printNumbers(myrg1, 5);

    // should output 1,15,25,25,25  : if given more iterations, 25 will always output
    // testing for seed 1, multipler 40, increment 725, 50 modulo (non-psuedoprime)
    rand_gen myrg2(1, 40, 725, 50);
    printNumbers(myrg2, 5);

/* given test functions
    rand_gen rg(1, 40, 725, 729);

    printNumbers(rg, 5);
    
    rg.set_seed(1);
    printNumbers(rg, 5);
    
    rg.set_seed(15);
    printNumbers(rg, 5);


    rand_gen rg2(14, 85, 637, 1947);
    
    printNumbers(rg2, 5);
    
    rg2.set_seed(14);
    printNumbers(rg2, 5);
*/

    return 0;
}
