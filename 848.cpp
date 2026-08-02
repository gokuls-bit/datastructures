#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        
        // dp[i] stores the max score difference a player can get on the current subarray starting at i
        vector<int> dp(n, 0);
        
        // Base case: subarrays of length 1
        for (int i = 0; i < n; i++) {
            dp[i] = piles[i];
        }
        
        // Build the DP table for lengths from 2 to n
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                
                // Maximize the net score by picking left or picking right
                dp[i] = max(piles[i] - dp[i + 1], piles[j] - dp[i]);
            }
        }
        
        // Alice wins if her score difference is > 0 (ties are impossible due to odd sum constraint)
        return dp[0] > 0;
    }
};
