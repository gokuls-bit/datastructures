class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {

        int count[3] = {0, 0, 0};

        for (int x : stones) {
            count[x % 3]++;
        }

        int zero = count[0];
        int one = count[1];
        int two = count[2];

        // Alice can win when the number of
        // remainder-0 stones is even and
        // both remainder-1 and remainder-2 stones exist.
        if (zero % 2 == 0) {

            if (one > 0 && two > 0) {
                return true;
            }

            return false;
        }

        // When the number of remainder-0 stones is odd,
        // one side needs to have enough advantage.
        if (abs(one - two) > 2) {
            return true;
        }

        return false;
    }
};
