#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        
        // dp[i] will store the maximum score difference a player can achieve
        // over the other player for the subarray starting at index i
        vector<int> dp(n, 0);
        
        // Base case: If the subarray has length 1, the score difference is just the element itself
        for (int i = 0; i < n; i++) {
            dp[i] = nums[i];
        }
        
        // Build the DP table for subarrays of length 2 up to n
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1; // End index of the current subarray
                
                // If the player chooses nums[i], the other player plays optimally on nums[i+1...j]
                int pickLeft = nums[i] - dp[i + 1];
                
                // If the player chooses nums[j], the other player plays optimally on nums[i...j-1]
                int pickRight = nums[j] - dp[i];
                
                // The current player wants to maximize their net score difference
                dp[i] = max(pickLeft, pickRight);
            }
        }
        
        // Player 1 wins (or ties) if their score difference against Player 2 is >= 0
        return dp[0] >= 0;
    }
};
