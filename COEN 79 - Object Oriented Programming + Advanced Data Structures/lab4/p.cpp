#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
    const unsigned int polynomial::MAXIMUM_DEGREE;


    polynomial::polynomial(double c, unsigned int exponent)
    {
        assert(exponent <= MAXIMUM_DEGREE);
        for(int i = 0; i< MAXIMUM_DEGREE; i++)
            data[i] = 0;
        data[exponent] = c;
    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
        assert(exponent<=MAXIMUM_DEGREE);
        data[exponent] = (double)coefficient;
        current_degree = (exponent > degree()) ? exponent : degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] += amount; 
        current_degree = (exponent > degree()) ? exponent : degree();

    }

    void polynomial::clear()
    {
        for(int i = 0; i < MAXIMUM_DEGREE; i++)
            data[i] = 0;
        current_degree = 0;
    }

    polynomial polynomial::antiderivative() const
    {
        assert(degree() < MAXIMUM_DEGREE);
        polynomial a;
        for(unsigned int i = MAXIMUM_DEGREE - 1; i >= 0; i--)
        {
            if(coefficient(i) != 0)
                a.assign_coef(coefficient(i)/(i+1), i + 1);
            if( i== 0)
                break;
        }
        return a;
    }

    double polynomial::coefficient(unsigned int exponent) const
    {
      if(exponent > MAXIMUM_DEGREE)
          return 0;
      else
        return data[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const
    {
        polynomial a = this ->antiderivative();
        double up, low = 0.0; 

        for(int i = 0; i <= MAXIMUM_DEGREE; i++)
        {
            up += (a.coefficient(i)*pow(x0,i));
            low +=(a.coefficient(i)*pow(x1,i));
        }
        return up - low;
    }

    unsigned int polynomial::degree() const
    {
       for(int i = MAXIMUM_DEGREE-1; i >= 0; i--) 
       { 
            if(data[i] != 0)
                return i;
       }
       return 0;
    }

    polynomial polynomial::derivative() const
    {
        polynomial a; 
        for(int i = 1; i<MAXIMUM_DEGREE; i++)
        {
            if(coefficient(i) != 0)
                a.assign_coef(coefficient(i) * i, i - 1);
        }
        a.current_degree = degree() -1;
        return a;
    }

    double polynomial::eval(double x) const
    {
            double sum = coefficient(0);
            for(int i = 1; i< MAXIMUM_DEGREE; i++)
                sum+= (coefficient(i)*pow(x, i));
            return sum;
    }

    bool polynomial::is_zero() const
    {
        for(int i = 0; i<MAXIMUM_DEGREE; i++)
        {
            if(data[i] != 0)
                return false;
        }
        return true;
    }

    unsigned int polynomial::next_term(unsigned int e) const
    {
        for(int i = e+1; e< MAXIMUM_DEGREE; i++)
        {
                if(data[i] != 0)
                    return i;
        }
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const
    {
        for(int i = e-1; i>=0; i--)
        {
            if(data[i] != 0)
                return i;
        }
    }

    double polynomial::operator()(double x) const
    {
        return eval(x);
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
        polynomial temp;
        for(int i = 0; i< polynomial::MAXIMUM_DEGREE; i++)
            temp.assign_coef(p1.coefficient(i)+p2.coefficient(i),i);
        return temp;
    }

    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
        polynomial temp; 
        for(int i = 0; i< polynomial::MAXIMUM_DEGREE; i++)
            temp.assign_coef(p1.coefficient(i)-p2.coefficient(i), i);
        return temp;
    }

    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {
        polynomial a;
        for(int i = 0; i<=p1.degree(); i++)
        {
            for(int j = 0; j<= p2.degree(); j++)
                a.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + 1);
        }
        return a;
    }

    std::ostream& operator<<(std::ostream& out, const polynomial& p)
    {
        unsigned int i = p.degree();
        streamsize s = out.precision();
        out << fixed;
        out << setprecision(1);
        for(int i = p.degree(); i >= 0; i--) {              
            if(p.degree() == 0) 
                out << p.coefficient(0);
            else if(p.coefficient(i) != 0) {        
                if(i == p.degree())                             
                    out << p.coefficient(i) << "x^" << i << ' ';   
                else if(i < p.degree() && i > 1) {          
                    if(p.coefficient(i) < 0)
                        out << "- ";                       
                    else    
                        out << "+ ";                           
                    out << fabs(p.coefficient(i)) << "x^" << i << ' ';  
                }
                else if(i == 1) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                         
                    else
                        out << "+ "; 
                    out << fabs(p.coefficient(i)) << "x ";   
                }
                else if(i == 0) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                    
                    else
                        out << "+ ";                           
                    out << fabs(p.coefficient(i));            
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(s);
        return out;
    }   
}