/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;

/* The divisorSum function takes one argument `n` and calculates the
 * sum of proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division using the modulus operator %
 *
 * Note: the C++ long type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* The isPerfect function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* The findPerfects function takes one argument `stop` and performs
 * an exhaustive search for perfect numbers over the range 1 to `stop`.
 * Each perfect number found is printed to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/*
 * The smarterSum function takes n and calculates the sum of divisors
 * of n excluding itself. Instead of looping all the way to n-1, it only
 * loops up to the square root of n. Each time it finds a divisor,
 * it also adds the matching pair (n / divisor), as long as the pair
 * isn't the same number.
 */
long smarterSum(long n) {
    if (n <=1){
        return 0;
    }
    long total = 1;
    for (long divisor = 2; divisor <= sqrt(n); divisor++){
        if (n % divisor ==0){
            total += divisor;
            long pair = n / divisor;
            if (pair != divisor){
                total += pair;
            }
        }
    }
    return total;
}

/* isPerfectSmarter takes n and returns a
 * boolean value telling whether or not n is perfect.
 * It works the same as isPerfect but uses smarterSum instead of divisorSum
 * to calculate the sum of divisors faster.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}


/* findPerfectsSmarter takes stop and performs a search for perfect numbers over the range 1 to stop.
 * It works the same as findPerfects but uses isPerfectSmarter, so the search runs faster.
 * Each perfect number found is printed to the console.
 */

void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    return 0;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(1000, findPerfects(1000));
}


// TODO: add your student test cases here

/*
 * Below is a suggestion of how to use a loop to set the input sizes
 * for a sequence of time trials.
 *
 *
STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes") {

    int smallest = 1000, largest = 8000;

    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfects(size));
    }
}

*/

/*thisismine STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes"){
    int smallest = 56250, largest = 450000;

    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfects(size));
    }
}

STUDENT_TEST("isPerfect on negative numbers"){
    int smallest = -10000, largest = -1;

    for (int number = smallest; number <= largest; number++){
        EXPECT(!isPerfect(number));
    }
}

STUDENT_TEST("smarterSum matches divisorSum on perfect squares") {
    EXPECT_EQUAL(smarterSum(25), divisorSum(25));
    EXPECT_EQUAL(smarterSum(36), divisorSum(36));
}

STUDENT_TEST("smarterSum matches divisorSum on small and edge inputs") {
    EXPECT_EQUAL(smarterSum(1), divisorSum(1));
    EXPECT_EQUAL(smarterSum(0), divisorSum(0)); EXPECT_EQUAL(smarterSum(-5), divisorSum(-5));
}

STUDENT_TEST("smarterSum matches divisorSum on primes and perfect numbers") {
    EXPECT_EQUAL(smarterSum(13), divisorSum(13));
    EXPECT_EQUAL(smarterSum(28), divisorSum(28));
    EXPECT_EQUAL(smarterSum(496), divisorSum(496));
}

*/

STUDENT_TEST("Multiple time trials of findPerfectsSmarter on increasing input sizes"){
    int smallest = 1750000, largest = 14000000;

    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfectsSmarter(size));
    }
}

