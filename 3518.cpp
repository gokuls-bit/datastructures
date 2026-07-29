class Solution {
public:
    static const long long LIM = 1000001;

    long long combCap(int n, int r) {

        if (r < 0 || r > n) return 0;

        r = min(r, n - r);

        long long result = 1;

        for (int i = 1; i <= r; i++) {

            long long numerator = n - r + i;
            long long denominator = i;

            long long g = gcd(numerator, denominator);
            numerator /= g;
            denominator /= g;

            g = gcd(result, denominator);
            result /= g;
            denominator /= g;

            __int128 value = (__int128)result * numerator;
            value /= denominator;

            if (value >= LIM) return LIM;

            result = (long long)value;
        }

        return result;
    }

    long long countWays(vector<int>& halfCount) {

        int remaining = 0;

        for (int x : halfCount) remaining += x;

        long long ways = 1;

        for (int x : halfCount) {

            if (x == 0) continue;

            long long choose = combCap(remaining, x);

            __int128 value = (__int128)ways * choose;

            if (value >= LIM) ways = LIM;
            else ways = (long long)value;

            remaining -= x;
        }

        return ways;
    }

    string smallestPalindrome(string s, int k) {

        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26);

        char middle = '\0';

        int halfLength = 0;

        for (int i = 0; i < 26; i++) {

            half[i] = freq[i] / 2;

            halfLength += half[i];

            if (freq[i] & 1)
                middle = char('a' + i);
        }

        if (countWays(half) < k)
            return "";

        string left;

        for (int pos = 0; pos < halfLength; pos++) {

            for (int c = 0; c < 26; c++) {

                if (half[c] == 0)
                    continue;

                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {

                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (middle != '\0')
            return left + middle + right;

        return left + right;
    }
};
