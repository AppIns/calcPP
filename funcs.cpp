#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <iostream>

#include "funcs.hpp"

bool isNumber(std::string s){
    // There should only be one decimal point
    bool seenDec = false;

    bool canBeMinus = true;
    bool incorrect = false;

    for (auto i : s){
        if( i == '-' && canBeMinus ){
            canBeMinus = false;
            incorrect = true;
            continue;
        }
        if( i == '.' && !seenDec ){
            seenDec = true;
            incorrect = true;
            continue;
        }
        if( !std::isdigit(i) ){
            return false;
        }
        incorrect = false;
        canBeMinus = false;
    }

    if(incorrect) return false;

    return true;
}

// Display the vector in a readable way. If not the main vector, we should use a different "theme?"
void dispVec (const std::vector<double> &input, bool mainVec){
    if(mainVec){
        std::cout << "[ ";
    }
    else {
        std::cout << "> ";
    }

    // No line should contain more than 10 numbers...
    int newler = 0;

    // Display every entry, one at a time
    for( auto i : input ){
        if((newler % 10 == 0) && (newler != 0)){
            std::cout << std::endl << "* "; 
        }
        std::cout << i << " ";
        newler++;
    }

    if(mainVec){
        std::cout << "]";
    }

    std::cout << std::endl;
}

// Handle all of the operations
std::vector<double> process ( const std::vector<double> &input, unsigned short command ){

    // A vector for our result(s)
    std::vector<double> res {};
    
    // NOTE: Don't include the nochange flag
    switch(command & ~comms::NOCHANGE){
        // Add function (get the sum of every number)
        case 1: {
            double temp = 0; 

            for( auto i : input ){
                temp += i; 
            }

            // Add it to the end and quit. This will be done alot
            res.push_back(temp);
            break; 
        }

        // Multiplication functions (product or * too)
        case 2: {
            double temp = 1;
        
            for( auto i: input ){
                temp *= i;
            }

            // Add it to the new away.
            res.push_back(temp);
            break;
        }

        // Average (or mean) function
        case 3: {

            // If input size is zero, exit before other code is done
            if( !input.size() ){
                break;
            }

            double temp = 0;

            for( auto i : input ){
                temp += i;
            }

            temp /= input.size();

            res.push_back(temp);

            break;
        }

        // Clear the array. We don't actually have to do anyting here, which is nice
        case 4: {
            break;
        }

        // Delete a single element from the end
        case 5: {
            res = input; 

            if(res.size() > 0){
                res.pop_back();
            }

            break;
        } 
        
        // Get maximum value in the vector
        case 6: {
            // If input size is zero, exit before other code is done
            if( !input.size() ){
                break;
            }

            // We shouldn't start with zero just incase the array is all negative
            auto temp = input[0];

            for( auto i : input ){
                if( i > temp ){
                    temp = i;
                }
            }

            res.push_back(temp);

            break;
        }

        // Get the minimum value
        case 7: {
            // If input size is zero, exit before other code is done
            if( !input.size() ){
                break;
            }

            // We shouldn't start with zero incase the numbers are all over zero
            auto temp = input[0];

            for( auto i : input ){
                if( i < temp ){
                    temp = i;
                }
            }

            res.push_back(temp);

            break;
        }

        // Move the oldest value to the newest value, do this by cycling
        case 8: {
            bool once = true;
            auto endof = input[0];

            for(auto i : input){
                if(once){
                    once = false;
                    continue;
                }
                res.push_back(i);
            }

            res.push_back(endof);

            break;
        }

        // Move the newest value to the oldest value
        case 9: {
            // Push back the oldest value first
            res.push_back(input[input.size() - 1]);

            for(int i = 0; i < input.size() - 1; i++){
                res.push_back(input[i]);
            }

            break;
        }
        
        // Insert a range of numbers
        case 10: {
            // We still want to keep the old array so we should start out with it
            res = input;
            
            // Ask the user about what they want from it
            std::cout << "Starting value: ";
            double startValue;
            std::cin >> startValue;

            // Check if the input was numberic, if not, try again until it is
            while(!std::cin){
                std::cout << "Not numeric input, please try again: ";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cin >> startValue; 
            }

            // Repreat this process three times
            std::cout << "Stop value: ";
            double stopValue;
            std::cin >> stopValue;

            while(!std::cin){
                std::cout << "Not numeric input, please try again: ";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cin >> stopValue; 
            }

            std::cout << "Increment value: ";
            double incValue;
            std::cin >> incValue;

            while(!std::cin){
                std::cout << "Not numeric input, please try again: ";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cin >> incValue; 
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // If there is some error where the loop will never finish, don't preform the loop
            if((startValue > stopValue && incValue > 0) || incValue == 0 ||
                    (startValue < stopValue && incValue < 0)){
                break;
            }
            
            bool incPositive = (incValue > 0);

            // Increment (or decrement) startValue by incValue until it is over or less than stopValue (Whichever is correct)
            for( ; (incPositive && startValue <= stopValue) || (!incPositive && startValue >= stopValue); startValue += incValue){
                res.push_back(startValue);
            }

            break;
        }

        // Divide the last two numbers, exactly like you would expect 
        case 11: {
            res = input;

            // We need at least two
            if(res.size() < 2){
                break;
            }

            // Denominator
            auto denom = res[res.size() - 1];

            // Divide by zero error
            if(denom == 0){
                std::cout << "Divide by zero error" << std::endl;
                break;
            }

            res.pop_back();
            res[res.size() - 1] /= denom;

            break;
        }
        
        // Subtract the second last number by the last number
        case 12: {
            res = input;

            // We need 2 elements
            if(res.size() < 2){
                break;
            }

            // Subractor
            auto subtr = res[res.size() - 1];
            res.pop_back();

            res[res.size() - 1] -= subtr;

            break;
        }

        case 13: {
            // Start with the old array
            res = input;

            std::cout << "Please enter a number to be inserted: ";
            double numericValue;
            std::cin >> numericValue;

            while(!std::cin){
                std::cout << "Not numeric input, please try again: ";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cin >> numericValue; 
            }

            std::cout << "How many times should we insert that number: ";
            double amount;
            std::cin >> amount;

            while(!std::cin){
                std::cout << "Not numeric input, please try again: ";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cin >> amount; 
            }

            // If under 1, don't do anything
            if(amount < 1){
                break;
            }

            for(; amount >= 1; amount--){
               res.push_back(numericValue);
            }

            break;
        }

        // This shouldn't be called unless there is some issue matching commands
        default: {
            res = input;
            std::cout << "Command not found" << std::endl;

            // If this was called with a nonzero command, there is most likley an issue
            if( command ){
                std::cout << "Please report that the command " << command << " might be broken." << std::endl;
            }
        }
    }

    return res;
}

// If the command ends with a '_' then we shouldn't change the vector.
bool isNoChange ( std::string &input ){
    if(input[input.length() - 1] == '_'){
        input = input.substr(0, input.length() - 1);
        return true; 
    }

    return false;

}

void toLowerCase(std::string &input){
    for( auto &i : input){
        i = tolower(i); 
    }
}
