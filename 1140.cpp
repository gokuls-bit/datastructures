class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // suffix[i] = total stones from i to n-1
        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        // dp[i][M] = maximum stones current player can obtain
        // starting at i with current M
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int M = 1; M <= n; M++) {

                // Can take all remaining piles
                if (i + 2 * M >= n) {
                    dp[i][M] = suffix[i];
                    continue;
                }

                // Try taking X piles
                for (int X = 1; X <= 2 * M && i + X <= n; X++) {

                    // We take X piles.
                    // Opponent then gets dp[i+X][max(M,X)].
                    //
                    // Whatever opponent gets, the rest is ours.
                    dp[i][M] = max(
                        dp[i][M],
                        suffix[i] - dp[i + X][max(M, X)]
                    );
                }
            }
        }

        return dp[0][1];
    }
};
