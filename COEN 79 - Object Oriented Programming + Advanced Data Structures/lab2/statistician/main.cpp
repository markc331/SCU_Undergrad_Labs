#include "statistician.h"
#include <iostream>

using namespace std;

using namespace coen79_lab2;


// Helper function to print statistician info
void printStatisticianInfo(statistician & s) {
    cout << "Sum: " << s.sum() << endl;
    cout << "Mean: " << s.mean() << endl;
    cout << "Smallest: " << s.minimum() << endl;
    cout << "Largest: " << s.maximum() << endl;
    cout << endl;
}

// main function
int main(int argc, const char * argv[])
{
    statistician s1, s2, s3;

    cout << "--- s1 prints --- | 0, -1, 1" << endl;

    s1.next(0);
    printStatisticianInfo(s1);
    s1.next(-1);
    printStatisticianInfo(s1);
    s1.next(1);
    printStatisticianInfo(s1);

    cout << "--- s2 prints --- | Large doubles" << endl;

    s2.next(1000.1234);
    printStatisticianInfo(s2);
    s2.next(2000.5678);
    printStatisticianInfo(s2);
    s2.next(3000.3456);
    printStatisticianInfo(s2);

    s3 = s1 + s2;

    cout << "--- s3 print --- | test + operator" << endl;

    printStatisticianInfo(s3);

    
    s1.reset();
    s1.next(5);
    printStatisticianInfo(s1);

    cout << "--- assignment prints --- | test assignment operator" << endl;

    s2 = s1;
    printStatisticianInfo(s1);
    
    cout << "--- erase prints --- | ";

    s1.reset();
    s2.reset();

    cout << "...erased sucessfully\n" << endl;

    cout << "--- equals prints --- | test compareTo operator" << endl;

    s1.next(4);
    s2.next(4);
    if (s1 == s2)
        cout << "s1 is equal to s2" << endl;

    cout << endl << "--- scaling test --- | test multiply operator" << endl;

    s1.reset();
    s1.next(5);
    s1.next(-3);
    printStatisticianInfo(s1);
    s1 = -1 * s1;
    printStatisticianInfo(s1);

    
        

    return 0;
}
