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
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
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


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string soundex(string initialInput) {
    string firstChar = repFirst(initialInput);
    string letters = lettersOnly(initialInput);
    string nums = encode(letters);
    string noDupes = removeDuplicates(nums);
    string noZeroes = removeZeroes(noDupes);
    string code = fixLength(noZeroes);
    return nums;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // This provided code opens the specified file
    // and reads the lines into a vector of strings
    ifstream in;
    Vector<string> allNames;

    if (openFile(in, filepath)) {
        allNames = readLines(in);
    }
    cout << "Read file " << filepath << ", "
         << allNames.size() << " names found." << endl;

    // The names read from file are now stored in Vector allNames

    /* TODO: Fill in the remainder of this function. */
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string repFirst(string intialInput) {
    return std::to_string(initialInput[0]);
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string lettersOnly(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string encode(string s) {
    string result = "";
    string input = toUpperCase(s);
    for (char ch : input) {
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'H' || ch == 'W' || ch == 'Y') {
            result += '0';
        }
        else if (ch == 'B' || ch == 'F' || ch == 'P' || ch == 'V') {
            result += '1';
        }
        else if (ch == 'C' || ch == 'G' || ch == 'J' || ch == 'K' || ch == 'Q' || ch == 'S' || ch == 'X' || ch == 'Z') {
            result += '2';
        }
        else if (ch == 'D' || ch == 'T') {
            result += '3';
        }
        else if (ch == 'L') {
            result += '4';
        }
        else if (ch == 'M' || ch == 'N') {
            result += '5';
        }
        else if (ch == 'R') {
            result += '6';
        }
    }
    return result;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string removeDuplicates(string s) {
    string result = "";
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] != s[i + 1]) {
            result += s[i];
        }
    }
    return result;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */

/*removeExtraZeroes (string)
 * if string is greater than 4
 * start at int 5 check if zeroes
 * then keep chekcing if 0s to end
 * cut 0
 * d4560004
 * d40560005
 *
 *
 */
string removeZeroes(string s) {
    string ret = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != 0) {
            ret += s[i];
        }
    }
    return ret;
}

string fixLength(string s) {
    if (s.length() < 3) {
        while (s.length() != 3) {
            s += "0";
        }
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
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here


