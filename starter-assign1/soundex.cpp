/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
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

// Initialize variables
string initialInput;
string c;

// Intialize functions
string repFirst(string initialInput);
string lettersOnly(string s);
string encode(string s);
string removeDuplicates(string s);
string removeZeroes(string s);
string fixLength(string s);
string soundex(string s);
void soundexSearch();


// Function that runs the entire encoding process, calling on helpers and returning the final code
string soundex(string initialInput) {
    string letters = lettersOnly(initialInput); // get just the letters from a name
    string firstChar = repFirst(initialInput); // extract the first character
    string nums = encode(letters); // encode the entire name into numbers
    string noDupes = removeDuplicates(nums); // get rid of adjacent duplicate numbers
    string noFirst = noDupes.substr(1); // get rid of the first number (do this to handle edge cases)
    string noZeroes = removeZeroes(noFirst); // get rid of all zeroes
    string code = fixLength(noZeroes); // append zeroes or remove numbers as needed to get to 3 digits
    return firstChar + code; // put together first letter and final 3-digit code
}

// This provided code opens the specified file and reads the lines into a vector of strings
void soundexSearch(string filepath) {
    ifstream in;
    Vector<string> allNames;
    Vector<string> matchingNames;

    if (openFile(in, filepath)) {
        allNames = readLines(in);
    }
    cout << "Read file " << filepath << ", "
         << allNames.size() << " names found." << endl; // // The names read from file are now stored in Vector allNames

    // Get user input
    string name_input = getLine("Input name: ");
    string user_code = soundex(name_input);
    for (int i = 0; i < allNames.size(); i++) {
        if (soundex(allNames[i]) == user_code) {
            matchingNames.add(allNames[i]);
        }
    }
    cout << matchingNames << endl;
}


// Extracts the first letter from the name, saving it in uppercase to be used in the code later on.
string repFirst(string initialInput) {
    return toUpperCase(string(1, initialInput[0]));
}

// Gets rid of symbols and extracts all letters in the names
string lettersOnly(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

// Uses the "rules" provided in assignment to encode letters into numerical code
string encode(string s) {
    string result = "";
    string input = toUpperCase(s);
    for (char ch : input) {
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'H' || ch == 'W' || ch == 'Y') {
            result += "0";
        }
        else if (ch == 'B' || ch == 'F' || ch == 'P' || ch == 'V') {
            result += "1";
        }
        else if (ch == 'C' || ch == 'G' || ch == 'J' || ch == 'K' || ch == 'Q' || ch == 'S' || ch == 'X' || ch == 'Z') {
            result += "2";
        }
        else if (ch == 'D' || ch == 'T') {
            result += "3";
        }
        else if (ch == 'L') {
            result += "4";
        }
        else if (ch == 'M' || ch == 'N') {
            result += "5";
        }
        else if (ch == 'R') {
            result += "6";
        }
    }
    return result;
}

// Removes adjacent duplicate numbers as shown in assignment
string removeDuplicates(string s) {
    string result = "";
    for (char c : s) {
        if (result.length() != 0 && c == result.back()) { // checks that string length isn't 0, and last char is same as current
            // do nothing, just don't add duplicate to the string
        }
        else {
            result.push_back(c); // if not a duplicate, add to the back of the string
        }
    }
    return result;
}

// Removes all zeroes from the string which already has duplicates removed
string removeZeroes(string s) {
    string ret = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '0') {
            ret += s[i];
        }
    }
    return ret;
}

// Cuts off codes that are too long and attaches zeroes to codes that are too short
string fixLength(string s) {
    if (s.length() > 3) {
        return s.substr(0, 3); // cut off codes that are too long
    }
    while (s.length() < 3) {
        s += "0"; // keep adding zeroes if too short
    }
    return s;
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

STUDENT_TEST("replaceFirst swaps the first digit for the uppercase first letter") {
    EXPECT_EQUAL(repFirst("Boral"), "B");
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


