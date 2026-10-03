/* This file shows different ways to find perfect numbers.
 * It starts with a slow search that checks every single divisor a number should possibly have up to the number itself, then uses a smarter version that only checks up to the square root of the number,
 * and finally uses Euclid's method with Mersenne primes to find perfect numbers almost instantly.
 *
 * Something interesting I learned: after implementing the functions according to the instructions in the assignment,
 * I was scrolling through the table of perfect numbers when constructing some of my test cases and randomly noticed
 * that not a single one was odd. That meant my search was checking twice as many numbers as it needed to, using
 * twice the time and compute power. So I changed findPerfectsSmarter to skip odd numbers by counting up by 2 instead of 1.
 * After looking it up, I learned that nobody has proven odd perfect numbers can't exist, but none have ever been found, and if one exists it would probably be crazy large.
 * So for the sake of efficiency, I kept the change.
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


/* findPerfectsSmarter takes stop and performs a search for perfect numbers over the range 2 to stop
 * (only checks even numbers for perfectness since no odd perfects exist in the provided perfect numbers table).
 * It works the same as findPerfects but uses isPerfectSmarter, so the search runs faster.
 * Each perfect number found is printed to the console.
 */

void findPerfectsSmarter(long stop) {
    for (long num = 2; num < stop; num+=2) { //didn't see a single odd number in the perfect numbers table so skipping them to have use half the compute power and time
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* The findNthPerfectEuclid function takes n and returns the nth perfect number.
 * It loops through values of k, calculating the Mersenne number 2^k - 1 each time.
 * If that number is prime, it uses Euclid's formula 2^(k-1) * (2^k - 1)
 * to get a perfect number and adds one to the count to keep track of nth perfect number we're on right now.
 * Once the count reaches n (meaning it has found the nth perfect number),
 * the loop stops and returns the last perfect number found.
 */

long findNthPerfectEuclid(long n) {
    long counter = 0;
    long latestperfectnum = 0;
    for (long k = 1; counter < n; k++){
        long m = (long)pow(2,k) - 1;
        if (smarterSum(m) ==1) {
            counter++;
            latestperfectnum = (long)pow(2, k - 1) * m;
        }
    }

    return latestperfectnum;
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

STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes"){
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


STUDENT_TEST("Multiple time trials of findPerfectsSmarter on increasing input sizes"){
    int smallest = 2750000, largest = 22000000;

    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfectsSmarter(size));
    }
}

STUDENT_TEST("findNthPerfectEuclid for the first 3 known perfect numbers") {
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
}

STUDENT_TEST("findNthPerfectEuclid for larger known, 4th and 5th perfect numbers") {
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
}

STUDENT_TEST("whatever number findNthPerfectEuclid returns is checked by earlier isPerfectSmarter function") {
    for (long n = 1; n <= 5; n++) {
        EXPECT(isPerfectSmarter(findNthPerfectEuclid(n)));
    }
}

STUDENT_TEST("findNthPerfectEuclid returns with each subsequent n is truly increasing to find the next (larger) perfect number") {
    for (long n = 1; n < 5; n++) {
        EXPECT(findNthPerfectEuclid(n) < findNthPerfectEuclid(n + 1));
    }
}

