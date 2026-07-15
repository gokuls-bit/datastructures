class Solution {
public:

    // Function to calculate the Greatest Common Divisor
    // of two positive integers using Euclidean Algorithm.
    int calculateGCD(int firstNumber, int secondNumber) {

        while (secondNumber != 0) {

            int remainder = firstNumber % secondNumber;

            firstNumber = secondNumber;

            secondNumber = remainder;
        }

        return firstNumber;
    }


    int gcdOfOddEvenSums(int n) {

        /*
            We need to calculate two different sums:

            1. Sum of first n odd positive integers.

               Odd numbers are:

               1, 3, 5, 7, 9, ...

            2. Sum of first n even positive integers.

               Even numbers are:

               2, 4, 6, 8, 10, ...

            After calculating both sums,
            we return their Greatest Common Divisor.
        */


        int oddSum = 0;

        int evenSum = 0;


        /*
            Generate the first n odd numbers.

            Formula for ith odd number:

                2 * i - 1

            Examples:

                i = 1  ->  1
                i = 2  ->  3
                i = 3  ->  5
                i = 4  ->  7
        */

        for (int i = 1; i <= n; i++) {

            int currentOddNumber = 2 * i - 1;

            oddSum = oddSum + currentOddNumber;
        }


        /*
            Generate the first n even numbers.

            Formula for ith even number:

                2 * i

            Examples:

                i = 1  ->  2
                i = 2  ->  4
                i = 3  ->  6
                i = 4  ->  8
        */

        for (int i = 1; i <= n; i++) {

            int currentEvenNumber = 2 * i;

            evenSum = evenSum + currentEvenNumber;
        }


        /*
            Now calculate:

                GCD(oddSum, evenSum)

            Using Euclidean Algorithm.
        */

        int finalAnswer = calculateGCD(
            oddSum,
            evenSum
        );


        return finalAnswer;
    }
};
