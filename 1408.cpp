class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {

        int n = stoneValue.size();

        vector<int> dp(n + 1, INT_MIN);

        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--) {

            int currentSum = 0;

            for (int take = 0; take < 3 && i + take < n; take++) {

                currentSum += stoneValue[i + take];

                dp[i] = max(
                    dp[i],
                    currentSum - dp[i + take + 1]
                );
            }
        }

        if (dp[0] > 0)
            return "Alice";

        if (dp[0] < 0)
            return "Bob";

        return "Tie";
    }
};
