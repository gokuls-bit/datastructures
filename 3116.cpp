class Solution {
public:

    long long gcdLL(long long a, long long b) {
        while (b != 0) {
            long long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    long long lcmLL(long long a, long long b) {

        long long g = gcdLL(a, b);

        // Prevent unnecessary overflow.
        if (a > (long long)4e18 / (b / g))
            return (long long)4e18;

        return a / g * b;
    }

    long long countAmounts(
        long long x,
        vector<int>& coins
    ) {

        int n = coins.size();

        long long total = 0;

        int totalMasks = 1 << n;

        for (int mask = 1; mask < totalMasks; mask++) {

            long long lcm = 1;

            int bits = 0;

            bool overflow = false;

            for (int i = 0; i < n; i++) {

                if (mask & (1 << i)) {

                    bits++;

                    lcm = lcmLL(lcm, coins[i]);

                    if (lcm > x) {
                        overflow = true;
                        break;
                    }
                }
            }

            if (overflow)
                continue;

            long long contribution = x / lcm;

            if (bits % 2 == 1) {
                total += contribution;
            }
            else {
                total -= contribution;
            }
        }

        return total;
    }

    long long findKthSmallest(
        vector<int>& coins,
        int k
    ) {

        long long low = 1;

        long long high =
            1LL * (*min_element(
                coins.begin(),
                coins.end()
            )) * k;

        while (low < high) {

            long long mid =
                low + (high - low) / 2;

            long long count =
                countAmounts(mid, coins);

            if (count >= k) {

                high = mid;

            }
            else {

                low = mid + 1;
            }
        }

        return low;
    }
};
