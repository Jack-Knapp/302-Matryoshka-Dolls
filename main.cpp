/*
Name: Jack Knapp, 302.2
Purpose: Recursion Review
Description: Program to validate Russian Nesting Dolls
Input: Nested dolls from text file
What to do?:  Verify whether the given dolls are a valid set or not
    using a recursive function
Output: The pass fail results, printed to terminal
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

/* 
 * function : A function to recursively check a list of dolls
        and whether is is valid or not
 * parameters: a vector which holds the list of dolls, 
        an int with a starting index, adn an int with the size of the vector
 * return value: A bool to represent validity of the doll
 */
bool function (vector<int> doll, int start, int size) {

    /*
    for (int i=start; i<size; i++) {
        cout << doll[i] << " ";
    }
    cout << endl;
    */
    
    //base case, inner dolls
    if (size-start==2) {
        if (doll[start] + doll[size-1] == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    
    //if bookends match, check smaller doll
    if (doll[start] + doll[size-1] == 0) {
        bool value = function(doll, start+1, size-1);

        //if the recursive functions fail at any point, fail this function
        if (value == false) {
            return false;
        }

    }
    //check for twins
    else {
        bool match = false;
        //loop through looking for a pair of adjacent values that sum up to zero 
        //when added to the first and last indexes; i.e. a pair of twins
        for (int i=size-3; i>start; i--) {
            if (doll[i]+doll[start] == 0 && doll[i+1] + doll[size-1] == 0) {
                match = true;
            
                //check inside each of the twins for validity
                bool lhs = function(doll, start, i+1);
                bool rhs = function(doll, i+1, size);

                //fail if either side fails
                if (lhs == false || rhs == false) {
                    return false;
                }

                break;
            }
        }
        //return false if no viable matches found after loop
        if (match == false) {
            return false;
        }
    }
    
    //an int which checks whether the inner values are less than the ones dircetly outside of them
    int validPair = -doll[start]+doll[start+1]-doll[size-2];

    //dolls match and are greater than outer set
    if (doll[start+1]+doll[size-2] == 0 && doll[size-1]-doll[size-2] > 0) {
        return true;
    }

    //pair is adjacent
    else if (size-start ==2) {
        return true;
    }

    //if validpair fails, see whether twins were involved
    else if (validPair <=0 && doll[start]+doll[size-1]==0) {
        return false;
    }

    //no fails triggered
    else {
        return true;
    }
}

int main() {

    //define some vars
    vector<int> doll;
    int cnt = 0;
    string num = "", digs = "";

    //input
    getline(cin, num);
    stringstream s(num);
    while (s >> digs) {
        doll.push_back(stoi(digs));
        cnt++;
    }

    //recursion
    bool goodDoll = function(doll, 0, doll.size());
    if (goodDoll) {
        cout << ":-) matryoshka!";
    }
    else {
        cout << ":-( Try again.";
    }
    
    return 0;
}