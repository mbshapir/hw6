#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				//NOTE: General idea for both for loops is to work from back of string we're adding
				//to front and multiply by right exponent before adding to the index

				unsigned long long w[5] = {0,0,0,0,0};
				int stringLengthLeft = k.size();
				int wPos = 4;

				while(stringLengthLeft > 0){ //input string not empty
					
					if(stringLengthLeft > 6  && wPos >= 0){ //6 or more chars left
						
						int count = 0;
						for(int i = stringLengthLeft-1; i >= stringLengthLeft - 6; i--){ //work from last char in string to 5 chars before
							w[wPos] += letterDigitToNumber(k[i]) * pow(36, count);
							count++;
						}
						stringLengthLeft -= 6;
						wPos--;

					}else if(stringLengthLeft != 0 && wPos >= 0){ // string left not empty aka og string not divisible by 6
						int count2 = 0;
						for(int i = stringLengthLeft-1; i>=0; i--){
							w[wPos] += letterDigitToNumber(k[i]) * pow(36, count2);
							count2++;
						}
						stringLengthLeft = 0; //exit while loop after iteration
					}

				}

				HASH_INDEX_T hashed = 0;
				for(int i = 0; i < 5; i++){
					hashed += w[i] * rValues[i]; //do hashing calculation and store in hashed index hashed
				}
				return hashed;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if(letter >= 65 && letter <= 90){ //check if uppercase letter
					//letter = letter + 32; //convert to lowercase
					return letter - 65;
				}else if(letter >= 97 && letter <= 122){ //check of lowercase letter
					return letter - 97;
				}else if(letter >= 48 && letter <= 57){ //check if 0-9 but we want these set to 26-35, not 0-26 like the letters
					return letter - 22;
				}else{ //otherwise not valid input
					return -1;
				}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif