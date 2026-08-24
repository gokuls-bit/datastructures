class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {

        int n = stones.size();

        vector<long long> prefix(n);

        prefix[0] = stones[0];

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + stones[i];
        }

        long long best = prefix[n - 1];

        for (int i = n - 2; i >= 1; i--) {

            best = max(
                best,
                prefix[i] - best
            );
        }

        return (int)best;
    }
};
