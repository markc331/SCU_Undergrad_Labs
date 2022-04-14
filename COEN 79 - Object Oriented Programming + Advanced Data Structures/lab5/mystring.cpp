#include <cctype>
#include <cassert>
#include <string.h>
#include <iostream>
#include "mystring.h"

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5
{
    string::string(const char str[])
    {
        current_length = strlen(str); // makes length = length of the string
        allocated = current_length + 1; // have \0
        characters = new char[allocated]; 
        characters[current_length] = '\0';
        strncpy(characters, str, allocated); //copies string into characters until allocated size
    }   

    string::string(char c)
    {
        current_length = 1; // inputing c makes the length = 1
        allocated = current_length +1; // have \0
        characters = new char[allocated]; //creates new array
        characters[0] = c; //inputs c as first item
        characters[1] = '\0'; // end of array
    }

    string::string(const string& source)
    {
        characters = new char[source.current_length]; // makes new array the size of source
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        allocated = source.allocated;
    }

    string::~string()
    {
        delete[] characters;
        current_length = 0;
        allocated = 0;
    }

    void string::operator+=(const string& addend)
    {
        current_length = current_length + addend.current_length;
        allocated = current_length +1;
        reserve(allocated);
        strncpy(characters, addend.characters, addend.current_length);
    }

    void string::operator +=(const char addend[])
    {
        current_length = current_length + strlen(addend);
        allocated = current_length +1;
        reserve(allocated);
        strncat(characters, addend, strlen(addend));
    }

    void string::operator +=(char addend)
    { 
        size_t finalLength = current_length + 1;
        allocated = finalLength + 1;
        reserve(allocated);
        characters[current_length] = addend;
        current_length = finalLength;
        return;
    }

    void string::reserve(size_t n)
    {
        char* new_characters = new char[n];
        if(characters != NULL)
        {
            strncpy(new_characters, characters, current_length);
            delete[] characters;
        }
        characters = new_characters;
    }

    string& string::operator = (const string& source)
    {
        this->dlt(0, current_length);
        if(current_length != source.current_length)
        {
            allocated = source.allocated;
            reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        return *this;
    }

    void string::insert(const string& source, unsigned int position)
    {
        assert(position <= length());
        char* temp = new char[current_length + source.current_length];
        if(position > 0)
            strncpy(temp, characters, position);

        char* tmp = new char[allocated - position]; 
        for(int i = position, j = 0; i<current_length; i++, j++)
        {
            tmp[j] = characters[i];
        }
        delete[] characters;
        strncpy(temp, source.characters, source.current_length);
        strncpy(temp, tmp, strlen(tmp));
        characters = temp;
        current_length += source.current_length;
        allocated = current_length +1;
        return;
    }

    void string::dlt(unsigned int position, unsigned int num)
    {
        assert((position + num) <= length());
        for(int i = position; i<length(); i++)
            characters[i] = characters [i + num];
        current_length == num;
        return;
    }

    void string::replace(char c, unsigned int position)
    {
        assert(position < length());
        characters[position] = c;
        return;
    }

    void string::replace(const string& source, unsigned int position)
    {
        assert((position + source.length()) <= length());
        int j = 0;
        for(int i = position; i< (position + source.length()); i++)
            *(source.characters + i) = source[j++];
        return;
    }

    char string::operator[](size_t position) const
    {
        assert(position < length());
        return characters[position];
    }

    int string::search(char c) const
    {
        int index = -1;
        for(int i = 0; i < length(); i++)
        {
            if(characters[i] == c)
            {   index = i;
                break;
            }
        }
        return index;

    }

    int string::search(const string& substring) const
    {
        int index = -1;
        char* temp = strstr(characters, substring.characters);
        if(temp != NULL)
            index = *temp - *characters;
        return index;
    }

    unsigned int string::count(char c) const
    {
        unsigned int count= 0;
        for(int i = 0; i< length(); i++)
        {
            if(c == characters[i])
                count++;
        }
        return count;
    }

    std::ostream& operator <<(std::ostream& outs, const string& source)
    {
        outs << source.characters;
        return outs;
    }

    bool operator ==(const string& s1, const string& s2)
    {
        return(strcmp(s1.characters, s2.characters) == 0);
    }

    bool operator !=(const string& s1, const string& s2)
    {
        return(strcmp(s1.characters, s2.characters) != 0);
    }

    bool operator > (const string& s1, const string& s2)
    {
        return(strcmp(s1.characters, s2.characters) > 0);
    }

    bool operator < (const string& s1, const string& s2)
    {
        return(strcmp(s1.characters, s2.characters) < 0);
    }

    bool operator >=(const string& s1, const string& s2)
    {
        return((s1 > s2) || (s1 == s2));
    }

    bool operator <=(const string& s1, const string& s2)
    {
        return((s1 < s2) || (s1 == s2));
    }

    
    string operator +(const string& s1, const string& s2)
    {
        string temp;
        temp.reserve(s1.length() + s2.length() + 1);
        temp += s1;
        temp += s2;
        return temp;
    }

    string operator +(const string& s1, const char addend[])
    {
        string temp;
        temp.reserve(s1.length() + strlen(addend) + 1);
        temp += s1;
        temp += addend;
        return temp;
    }

    std::istream& operator >>(std::istream& ins, string& target)
    {
        while(ins && isspace(ins.peek()))
        {
            ins.ignore();
        }
        char* input = new char[500];
        ins >> input;
        target = string(input);
        return ins;
    }
}
