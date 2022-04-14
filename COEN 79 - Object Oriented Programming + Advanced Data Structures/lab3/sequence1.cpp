#include <cassert>
#include <cmath>
#include "sequence1.h"

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3
{
	sequence::sequence()
	{
		length = 0;
		cur = 0;
	}

	void sequence::start()
	{
		cur = 0;
    }

	void sequence::end() 
	{
		cur = length - 1;
    }

	sequence::value_type sequence::current() const
	{
		assert(is_item());
		return data[cur];
	}

	void sequence::advance()
	{
		if(cur < CAPACITY)
			cur++;
	}

	bool sequence::is_item() const
	{
		if(cur < size())
			return true;
		return false;
   	}

	void sequence::insert(const value_type& entry)
	{
		assert(size() < CAPACITY);
		if(length == 0)
		{
			data[0] = entry;
			cur = 0;
		}	

		else
		{
			for(int i = length; i> cur; --i)
				data[i] = data[i-1];
			data[cur] = entry; 
		}

		length++;
	}

	void sequence::attach(const value_type& entry)
	{
		assert(size() < CAPACITY);
		
		if(!is_item())
			data[length] = entry;
		else
		{
			for(int i = length; i > cur + 1; --i)
				data[i] = data[i-1];
			data[cur+1] = entry;
			cur++;
		}

		length++;
	}    
	
	void sequence::remove_current()
	{
		assert(is_item());
		for(int i = cur + 1; i< length ; ++i)
			data[i-1] = data[i]; 
		length--;
	}

	void sequence::insert_front(const value_type& entry)
	{
		assert(size() < CAPACITY);
		cur = 0;
		insert(entry);
		length++;
	}

	void sequence::attach_back(const value_type& entry)
	{
		assert(size() < CAPACITY);
		data[length] = entry;
		length++;
	}
	
	void sequence::remove_front()
	{
		assert(is_item());
		for(int  i = 0; i< length - 1; ++i)
			data[i] = data[i+1];
		length--;
	}

	sequence::size_type sequence::size() const 
	{
		return length;
	}

	sequence::value_type sequence::operator[] (int index) const
	{
		assert(index < length);
		return data[index];
	}

	sequence operator+(sequence& lhs, sequence& rhs)
	{
		sequence temp;
		for(int i =0; i< lhs.size(); i++)
		{
			lhs.start();
			temp.attach(lhs.current());
			lhs.remove_front();
		}
		for(int j = 0; j<rhs.size(); j++)
		{
			rhs.start();
			temp.attach(rhs.current());
			rhs.remove_front();
		}
		return temp;
	}

	sequence operator+=(sequence& lhs, sequence& rhs)
	{
		lhs = lhs + rhs;
	}

	double sequence::mean() const
	{
		double sum = 0.0;
		for(int i = 0; i<length; i++)
			sum += data[i];
		return sum/length;
	}
	double sequence::standardDeviation() const
	{
		double stdev = 0.0;
		for(int i = 0; i<length; ++i)
			stdev += pow(data[i] - mean(), 2);
		return sqrt(stdev/length);
	}

	sequence::value_type summation(const sequence &s)
	{
		return s.mean()*s.size();
	}
}
