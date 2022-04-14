// FILE: statistician.cpp

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
	//Constructor
	statistician::statistician( )
    {
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }

    void statistician::next(double r)
    {
        total += r;
        if(min > r || size == 0) min = r;
        if(max < r || size == 0) max = r;
        size++;
        avg = total/size;
    }
    
    void statistician::reset( )
    {
        total = 0;
        size = 0;
        min = 0;
        max = 0;
        avg = 0;
    }
    
    double statistician::mean( ) const
    {
        return avg;
    }
    
    double statistician::minimum( ) const
    {
        return min;
    }
    
    double statistician::maximum( ) const
    {
        return max;
    }
    
    //FRIEND function +
    statistician operator +(const statistician& s1, const statistician& s2)
    {
        statistician s3;
    	s3.size += s1.size;
        s3.size += s2.size;

        s3.total += s1.total;
        s3.total += s2.total;
        
        if (s1.min > s2.min) s3.min = s2.min;
        else s3.min = s1.min;
        if (s1.max < s2.max) s3.max = s2.max;
        else s3.max = s1.max;
        s3.avg = s1.total/s1.size;

        return s3;
    }

    
    //NON-MEMBER function ==
    bool operator ==(const statistician& s1, const statistician& s2)
    {
        bool flag1 = false;
        bool flag2 = false;
        bool flag3 = false;
        bool flag4 = false;
        bool flag5 = false;

        if (s1.mean() == s2.mean()) flag1 = true;
        if (s1.minimum() == s2.minimum()) flag2 = true;
        if (s1.maximum() == s2.maximum()) flag3 = true;
        if (s1.sum() == s2.sum()) flag4 = true;
        if (s1.length() == s2.length()) flag5 = true;

        

    }
    
    //FRIEND function *
    statistician operator *(double scale, const statistician& p)
    {
        statistician s1;

        s1.total = p.total*scale;
        s1.avg = p.avg*scale;

        if(scale >= 0) {
            s1.max = p.max*scale;
            s1.min = p.min*scale;
        } else {
            s1.max = p.min*scale;
            s1.min = p.max*scale;
        }
        return s1;
             
    }
        

}


