/* Program Name: Bitset Lab
 * Student Name: Harrison Clark
 * Program Description: So, this lab contains a bunch of integers, and we're creating a bunch of methods to test, set, clear the bits of those integers to return other integers or lists of bits. This is all done using a user interface that we designed for users to use. */

//! Remember: your comments
//! Remember: your formatting and indentation
//  - auto-format in vim: gg=G in normal mode, in vscode: alt+shift+f
//! Remember: check your solution with the gradescripts
//  - gradescript command: `python3.11 scripts/test.py bitset.cpp`

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class BITSET {
    vector<int> mSets;

  public:
    BITSET();
    bool Test(int index) const;
    void Set(int index);
    void Clear(int index);
    int GetNumSets() const;
    int GetSet(int index) const;
};
string ToBinary(int bit_set, int spacing = 4);
int main() {
    BITSET sets;
    string command;
    int which;
    do {
        cout << "> ";
        if (!(cin >> command) || "q" == command) {
            // If cin fails for any reason, it usually means
            // an EOF state, break and quit.
            break;
        }
        // Handle the commands here
        if ("t" == command) { // tests index
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                cout << sets.Test(which) << '\n';
            }
        } else if ("s" == command) { // sets index
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                sets.Set(which);
            }
        } else if ("g" == command) { // prints out binary
            int spacing;
            string line;
            getline(cin, line);
            istringstream sin{line};
            if (!(sin >> which)) {
                cout << "Invalid index\n";
            } else {
                if (!(sin >> spacing)) {
                    spacing = 4;
                }
                cout << ToBinary(sets.GetSet(which), spacing) << '\n';
            }
        } else if ("c" == command) { //clears at index
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            } else {
                sets.Clear(which);
            }
        } else if ("n" == command) {
			cout << sets.GetNumSets() << endl; // returns number of sets
		}
        else {
            cout << "Unknown command '" << command << "'\n";
        }
    } while (true);
    return 0;
}
// Write the function body for ToBinary:
string ToBinary(int bit_set, int spacing) {
    string ret = "";
    // The constructor will
    // clear it to the empty string "".
    for (int i = 31; i >= 0; i--) {
		
        if (bit_set & (1 << i)) { // << causes it to iterate through values like 0001, 0010, 0100, 1000 and compare that using and to bit_set
            ret += '1';
        } else {
            ret += '0';
        }
        if (((32 - i) % spacing == 0) && (i != 0)) { // checks to see if there's a space; 31 - i because we're iterating backwards
            ret += ' ';
        }
    }
    return ret;
}

// BITSET Class Members
BITSET::BITSET() : mSets(1, 0) {}

bool BITSET::Test(int index) const {
    // Recall that each set has 32 bits
    int which_set = index / 32; //FINDS WHICH INTEGER IT'S IN GIVEN 32 BIT LENGTH 
	
    int which_bit = index % 32; 
    if (which_set >= GetNumSets()) {
        // The BITSET is an "infinite" set, so if the requested set
        // is bigger than what we are storing, that means it's a 0.
        return false;
		//we don't need to create that many sets for all intents and purposes so we just return false. if ever they need that array it will be created then
    }
	
	//returns boolean of whether an array like 000100 and 101100 have matching bits at the spot that's 1 in the first
    return ((mSets.at(which_set) & (1 << which_bit)) != 0);
}

void BITSET::Set(int index) {
    int which_set = index / 32; //FINDS WHICH INTEGER IT'S IN GIVEN 32 BIT LENGTH 
	
    int which_bit = index % 32; 
    while ((which_set + 1) > GetNumSets()) {
		mSets.push_back(0); // creates new sets, referenced above in test
	}
    mSets.at(which_set) = mSets.at(which_set) | (1 << which_bit);// uses or turn on a bit if it's 0
}

void BITSET::Clear(int index) {
    int which_set = index / 32; // returns an integer and truncates so will always round down
    int which_bit = index % 32; // returns remainder inside of that index
    if (which_set < GetNumSets()) {
        mSets.at(which_set) = mSets.at(which_set) & ~(1 << which_bit);
		while ((mSets.at(GetNumSets() - 1) == 0) && (GetNumSets() != 1)) {
			mSets.pop_back(); // removes sets from the end of the vector until one is found that isnt empty
		} 
    }
}

int BITSET::GetNumSets() const { return static_cast<int>(mSets.size()); }

int BITSET::GetSet(int which_set) const {
	if ((GetNumSets()) <= (which_set)) {
		return 0; // if it doesnt exist it returns 0; there's no reason to create a bunch of new integers because if they are needed they'll be there through the set operation
	}
    return mSets.at(which_set);
}
