#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

    // Modulo required by the problem
    static const int MOD = 1000000007;

    /*
        Helper function to safely add two values under modulo.

        Example:
            a = 1000000000
            b = 1000000000

        Their normal sum exceeds MOD, so we take modulo.
    */
    long long addModulo(long long a, long long b) {
        return (a + b) % MOD;
    }

public:

    int subsequencePairCount(vector<int>& nums) {

        /*
            --------------------------------------------------
            STEP 1: FIND MAXIMUM VALUE
            --------------------------------------------------

            We need to track possible GCD values.

            Since the GCD of a subsequence can never be greater
            than the maximum element in nums, we only need DP
            states from 0 to maxValue.

            GCD = 0 is used to represent an empty subsequence.
        */

        int maxValue = 0;

        for (int number : nums) {
            maxValue = max(maxValue, number);
        }


        /*
            --------------------------------------------------
            STEP 2: DEFINE DP TABLE
            --------------------------------------------------

            dp[gcd1][gcd2]

            represents:

            Number of ways to process some prefix of nums such
            that:

                GCD of subsequence 1 = gcd1
                GCD of subsequence 2 = gcd2

            Special meaning:

                gcd1 = 0  -> subsequence 1 is empty
                gcd2 = 0  -> subsequence 2 is empty

            Initially, before processing any elements:

                subsequence 1 = []
                subsequence 2 = []

            Therefore:

                dp[0][0] = 1
        */

        vector<vector<long long>> dp(
            maxValue + 1,
            vector<long long>(maxValue + 1, 0)
        );

        dp[0][0] = 1;


        /*
            --------------------------------------------------
            STEP 3: PROCESS EVERY NUMBER
            --------------------------------------------------

            For every number nums[i], we have exactly 3 choices:

            Choice 1:
                Do not use nums[i].

            Choice 2:
                Add nums[i] to subsequence 1.

            Choice 3:
                Add nums[i] to subsequence 2.

            We cannot add the same element to both subsequences
            because the two subsequences must be disjoint.
        */

        for (int number : nums) {

            /*
                Start nextDP as a copy of dp.

                This automatically handles Choice 1:

                    Do not use the current number.

                Every existing state remains unchanged.
            */

            vector<vector<long long>> nextDP = dp;


            /*
                Visit every possible pair:

                    (gcd1, gcd2)
            */

            for (int gcd1 = 0; gcd1 <= maxValue; gcd1++) {

                for (int gcd2 = 0; gcd2 <= maxValue; gcd2++) {

                    /*
                        If there are no ways to reach this state,
                        skip it.
                    */

                    if (dp[gcd1][gcd2] == 0) {
                        continue;
                    }


                    /*
                        Number of ways to reach the current state.
                    */

                    long long currentWays = dp[gcd1][gcd2];


                    /*
                        ------------------------------------------
                        CHOICE 2:
                        ADD CURRENT NUMBER TO SUBSEQUENCE 1
                        ------------------------------------------

                        Previous GCD:

                            gcd1

                        New number:

                            number

                        New GCD:

                            gcd(gcd1, number)

                        Important:

                            gcd(0, number) = number

                        Therefore, this also correctly handles
                        starting subsequence 1 for the first time.
                    */

                    int newGcd1 = std::gcd(gcd1, number);

                    nextDP[newGcd1][gcd2] =
                        addModulo(
                            nextDP[newGcd1][gcd2],
                            currentWays
                        );


                    /*
                        ------------------------------------------
                        CHOICE 3:
                        ADD CURRENT NUMBER TO SUBSEQUENCE 2
                        ------------------------------------------

                        Same logic as subsequence 1.

                        New GCD:

                            gcd(gcd2, number)
                    */

                    int newGcd2 = std::gcd(gcd2, number);

                    nextDP[gcd1][newGcd2] =
                        addModulo(
                            nextDP[gcd1][newGcd2],
                            currentWays
                        );
                }
            }


            /*
                The current number has now been completely
                processed.

                Move nextDP into dp for the next iteration.
            */

            dp = move(nextDP);
        }


        /*
            --------------------------------------------------
            STEP 4: CALCULATE FINAL ANSWER
            --------------------------------------------------

            We need pairs of non-empty subsequences where:

                gcd(subsequence1) == gcd(subsequence2)

            Therefore, valid states are:

                dp[1][1]
                dp[2][2]
                dp[3][3]
                ...
                dp[maxValue][maxValue]

            We intentionally start from 1 instead of 0 because:

                GCD = 0 represents an empty subsequence.

            Both subsequences must be non-empty.
        */

        long long answer = 0;

        for (int gcdValue = 1;
             gcdValue <= maxValue;
             gcdValue++) {

            answer = addModulo(
                answer,
                dp[gcdValue][gcdValue]
            );
        }


        /*
            Return final answer modulo 1e9 + 7.
        */

        return static_cast<int>(answer);
    }
};
