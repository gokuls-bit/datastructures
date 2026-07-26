class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {

        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));

        dp[0][0] = true;

        for (int value : nums) {

            for (int taken = 2; taken >= 0; taken--) {

                for (int x = 0; x < MAXX; x++) {

                    if (dp[taken][x]) {

                        dp[taken + 1][x ^ value] = true;
                    }
                }
            }
        }

        int answer = 0;

        for (int x = 0; x < MAXX; x++) {

            if (dp[1][x] || dp[3][x]) {

                answer++;
            }
        }

        return answer;
    }
};
Complexity
Time: O(n × 2048 × 3) ≈ 9 million operations
Space: O(4 × 2048)

This easily fits the constraints (n ≤ 1500).

Today 11:43 PM
Line 45: Char 28: error: no member named 'maximumProduct' in 'Solution'
   45 |       int ret = Solution().maximumProduct(param_1); return ret;
      |                 ~~~~~~~~~~ ^
1 error generated.

This is the same type of issue as before.

The compiler says:

error: no member named 'maximumProduct' in 'Solution'

That means the judge is trying to call:

Solution().maximumProduct(...)

but your class contains something else, such as:

int uniqueXorTriplets(...)

or another function.

You're submitting to the wrong LeetCode problem.

If you're solving 3514. Number of Unique XOR Triplets II, your class must be:

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        // solution
    }
};

If the judge expects:

int maximumProduct(vector<int>& nums)

then you're actually on a completely different problem (such as LeetCode 628 or another "Maximum Product" problem).

What to do
Check the title of the problem.
Look at the starter code that LeetCode provides.
Use exactly the function name and parameters from the starter code.

If you paste the first 15–20 lines of the starter code (or the LeetCode problem number/title), I'll give you the correct solution.

628. Maximum Product of Three Numbers
Attempted
Easy
Topics
premium lock icon
Companies
Given an integer array nums, find three numbers whose product is maximum and return the maximum product.

 

Example 1:

Input: nums = [1,2,3]
Output: 6
Example 2:

Input: nums = [1,2,3,4]
Output: 24
Example 3:

Input: nums = [-1,-2,-3]
Output: -6
 

Constraints:

3 <= nums.length <= 104
-1000 <= nums[i] <= 1000

For LeetCode 628, there are only two possible candidates for the maximum product:

The three largest numbers.
The two smallest (most negative) numbers and the largest positive number.

So, sort the array and return the maximum of these two products.

C++ Solution
class Solution {
public:
    int maximumProduct(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        int n = nums.size();

        int product1 =
            nums[n - 1] *
            nums[n - 2] *
            nums[n - 3];

        int product2 =
            nums[0] *
            nums[1] *
            nums[n - 1];

        return max(product1, product2);
    }
};
