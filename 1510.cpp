class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        // dp[i] = whether the current player can win
        // when there are i stones remaining.

        for (int i = 1; i <= n; i++) {

            for (int x = 1; x * x <= i; x++) {
                
                // If taking x*x leaves a losing position
                // for the opponent, current player wins.
                if (!dp[i - x * x]) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};
