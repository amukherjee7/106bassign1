/*
 * soundex.cpp
 * Names: Anika Mukherjee, Srishti Boral
 * Course: CS 106B
 * Description: This file contains three main parts: the Soundex function, its helper functions, and the Soundex search function.
 * Soundex is an algorithm that encodes the phonetic pronunciation of surnames. We recreated the encoding algorithm
 * using a variety of helper functions which are defined below. Additionally, we created a console program that takes in
 * a user input of a surname and returns matching surnames (same encoding) in Stanford's database. Finally, we created
 * student test cases to demonstrate the efficacy of the program as a whole, as well as the intermediate helper functions.
 */
#include <cctype>
#include <fstream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include "SimpleTest.h"
using namespace std;

// Constants
const int CODE_LENGTH = 3;

// Initialize functions
string getFirstLetter(string initialInput);
string lettersOnly(string name);
string encode(string name);
string removeDuplicates(string name);
string removeZeroes(string name);
string fixLength(string name);
string soundex(string name);
void soundexSearch(string filepath);


/*
 * Returns Soundex code which consists of first letter of surname plus three encoded digits for the surname inputted
 * into the function. Utilizes helper functions to execute the algorithm and handle edge cases.
 * Parameter: initialInput (the surname to encode)
 * Returns: Soundex code
*/
string soundex(string initialInput) {
    string letters = lettersOnly(initialInput); // get just the letters from a name
    string firstChar = getFirstLetter(letters); // extract the first character
    string nums = encode(letters); // encode the entire name into numbers
    string noDupes = removeDuplicates(nums); // get rid of adjacent duplicate numbers
    string noFirst = noDupes.substr(1); // get rid of the first number (do this to handle edge cases)
    string noZeroes = removeZeroes(noFirst); // get rid of all zeroes
    string code = fixLength(noZeroes); // append zeroes or remove numbers as needed to get to 3 digits
    return firstChar + code; // put together first letter and final 3-digit code
}

/*
 * Reads a file which contains all the possible last names in the Stanford Soundex database.
 * Compares soundex code of the inputted last name to soundex codes of all the Stanford database names in the file and
 * if a match is found adds to a new Vector, which is fully printed out to the console to end the function. Stops loop
 * when user types "RETURN".
 * Parameter: filePath (database of all Stanford last names)
 * Returns: N/A (Prints in console all last names with matching soundex codes)
*/
void soundexSearch(string filepath) {
    ifstream in;
    Vector<string> allNames;
    string nameInput;

    if (openFile(in, filepath)) {
        allNames = readLines(in);
    }
    cout << "Read file " << filepath << ", " << allNames.size() << " names found." << endl; // // The names read from file are now stored in Vector allNames

    // Get user input
    nameInput = getLine("Enter a surname (RETURN to quit): ");

    while (!nameInput.empty()) {
        string userCode;
        Vector<string> matchingNames;
        userCode = soundex(nameInput);

        for (int i = 0; i < allNames.size(); i++) {
            if (soundex(allNames[i]) == userCode) {
                matchingNames.add(allNames[i]);
            }
        }
        matchingNames.sort();
        cout << "Soundex code: " << userCode << endl;
        cout << matchingNames << endl;
        nameInput = getLine("Enter a surname (RETURN to quit): ");
    }

}


/*
 * Returns the first letter of the surname inputted, converting to uppercase to maintain consistency with other helper functions.
 * Parameter: initialInput (the surname we were given)
 * Returns: capitalized first letter of surname in a String
 * Assumes the string isn't empty and contains letters.
 */
string getFirstLetter(string initialInput) {
    return toUpperCase(string(1, initialInput[0]));
}

/*
 * Returns a copy of the surname with no symbols, accent marks, etc.
 * Parameter: name (the surname, which could possibly include the special cases above)
 * Returns: surname with only letters.
*/
string lettersOnly(string name) {
    string result = "";
    for (int i = 0; i < name.length(); i++) {
        if (isalpha(name[i])) {
            result += name[i];
        }
    }
    return result;
}

/*
 * Utilizes "rules" in assignment description to encode the surname into Soundex digits.
 * Parameter: name (the given surname, now with only letters)
 * Returns: a string of digits which corresponds to every letter in the surname
 */
string encode(string name) {
    string result = "";
    string input = toUpperCase(name);
    for (char ch : input) {
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'H' || ch == 'W' || ch == 'Y') {
            result += "0";
        } else if (ch == 'B' || ch == 'F' || ch == 'P' || ch == 'V') {
            result += "1";
        } else if (ch == 'C' || ch == 'G' || ch == 'J' || ch == 'K' || ch == 'Q' || ch == 'S' || ch == 'X' || ch == 'Z') {
            result += "2";
        } else if (ch == 'D' || ch == 'T') {
            result += "3";
        } else if (ch == 'L') {
            result += "4";
        } else if (ch == 'M' || ch == 'N') {
            result += "5";
        } else if (ch == 'R') {
            result += "6";
        }
    }
    return result;
}

/*
 * Removes adjacent duplicate Soundex digits in the surname so there are no repeats in a row.
 * Parameters: name (encoded surname with all digits from encode function)
 * Returns: updated string containing no adjacent duplicate digits.
 */
string removeDuplicates(string name) {
    string result = "";
    for (char c : name) {
        if (result.empty() || c != result.back()) { // checks that string length is 0, and last char is different than current
            result.push_back(c);
        }
    }
    return result;
}

/*
 * Removes ALL zeroes from encoded digits, as long as the string inputted has no adjacent duplicates.
 * Parameter: name (encoded surname without adjacent duplicates)
 * Returns: updated string containing only nonzero digits.
 */
string removeZeroes(string name) {
    string result = "";
    for (int i = 0; i < name.length(); i++) {
        if (name[i] != '0') {
            result += name[i];
        }
    }
    return result;
}

/*
 * Utilizes Soundex algorithm rules to confine the code to being exactly 3 digits long (code minus first letter), cutting off excess digits
 * if too long, and padding zeroes to the end of the code if too short.
 * Parameter: name (string of digits with zeroes)
 * Returns: 3-character string with Soundex digits.
 */
string fixLength(string name) {
    while (name.length() < CODE_LENGTH) {
        name += "0";
    }
    return name.substr(0, CODE_LENGTH);
}

/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test exclude of punctuation, digits, and spaces") {
    string s = "O'Hara";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// Student test cases
STUDENT_TEST("lettersOnly removes a non-letter at the start") {
    EXPECT_EQUAL(lettersOnly("9Tom"), "Tom");
    EXPECT_EQUAL(lettersOnly("'Pen"), "Pen");
}

STUDENT_TEST("lettersOnly on strings with no letters or empty string") {
    EXPECT_EQUAL(lettersOnly(""), "");
    EXPECT_EQUAL(lettersOnly("6767-!"), "");
}

STUDENT_TEST("encode turns each letter into the right digit") {
    EXPECT_EQUAL(encode("Curie"), "20600");
    EXPECT_EQUAL(encode("Jackson"), "2022205");
}

STUDENT_TEST("encode handles lowercase and rare letters") {
    EXPECT_EQUAL(encode("abc"), "012");
    EXPECT_EQUAL(encode("Q"), "2");
    EXPECT_EQUAL(encode("W"), "0");
}

STUDENT_TEST("removeDuplicates puts together repeats next to each other") {
    EXPECT_EQUAL(removeDuplicates("222025"), "2025");
    EXPECT_EQUAL(removeDuplicates("2022205"), "20205");
}

STUDENT_TEST("removeDuplicates keeps all other repeats and single digits") {
    EXPECT_EQUAL(removeDuplicates("2020"), "2020");
    EXPECT_EQUAL(removeDuplicates("1"), "1");
}

STUDENT_TEST("getFirstLetter swaps the first digit for the uppercase first letter") {
    EXPECT_EQUAL(getFirstLetter("Boral"), "B");
}

STUDENT_TEST("removeZeroes removes all zeros and keeps everything else") {
    EXPECT_EQUAL(removeZeroes("A000"), "A");
}

STUDENT_TEST("soundex on Angelou and my surname Boral") {
    EXPECT_EQUAL(soundex("Angelou"), "A524");
    EXPECT_EQUAL(soundex("Boral"), "B640");
}

STUDENT_TEST("soundex on a single letter and a mixed case name") {
    EXPECT_EQUAL(soundex("A"), "A000");
    EXPECT_EQUAL(soundex("McDonald"), "M235");
}

STUDENT_TEST("fixLength cuts off too long codes and adds zeroes if too short"){
    EXPECT_EQUAL(fixLength("24315"), "243");
    EXPECT_EQUAL(fixLength("24"), "240");
}


