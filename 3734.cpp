Line 141: Char 31: error: no member named 'lexPalindromicPermutation' in 'Solution'
  141 |       string ret = Solution().lexPalindromicPermutation(param_1, param_2); return ret;
      |                    ~~~~~~~~~~ ^
1 error generated.

        class Solution {
public:

    string makePalindrome(string half, int n) {

        string ans = half;

        int i;

        if (n % 2 == 0)
            i = (int)half.size() - 1;
        else
            i = (int)half.size() - 2;

        while (i >= 0) {
            ans.push_back(half[i]);
            i--;
        }

        return ans;
    }

    string lexPalindromicPermutation(
        string s,
        string target
    ) {

        int n = s.size();
        int halfLen = n / 2;

        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // A palindrome is possible only when
        // at most one character has an odd frequency.
        int odd = 0;

        for (int i = 0; i < 26; i++) {

            if (freq[i] % 2)
                odd++;
        }

        if (odd > 1)
            return "";

        // Characters available in the first half.
        vector<int> halfFreq(26, 0);

        for (int i = 0; i < 26; i++) {
            halfFreq[i] = freq[i] / 2;
        }

        string targetHalf =
            target.substr(0, halfLen);

        /*
         * We need the smallest permutation of the
         * first half that is strictly greater than
         * target's first half.
         */

        vector<int> rem = halfFreq;

        /*
         * First try to match target's prefix.
         */
        for (int i = 0; i < halfLen; i++) {

            int x = targetHalf[i] - 'a';

            if (rem[x] == 0)
                break;

            rem[x]--;
        }

        /*
         * Backtrack from right to left.
         *
         * At each position, try the smallest character
         * greater than target[i].
         */
        for (int i = halfLen - 1; i >= 0; i--) {

            /*
             * Restore the character at position i
             * because we are moving the change point.
             */
            int current =
                targetHalf[i] - 'a';

            rem[current]++;

            /*
             * Try a character greater than target[i].
             */
            for (int c = current + 1; c < 26; c++) {

                if (rem[c] == 0)
                    continue;

                string half =
                    targetHalf.substr(0, i);

                half.push_back(char('a' + c));

                rem[c]--;

                /*
                 * Fill remaining positions with
                 * the smallest possible characters.
                 */
                for (int x = 0; x < 26; x++) {

                    while (rem[x] > 0) {

                        half.push_back(
                            char('a' + x)
                        );

                        rem[x]--;
                    }
                }

                string answer =
                    makePalindrome(half, n);

                if (answer > target)
                    return answer;

                /*
                 * Restore the selected character.
                 */
                for (int x = 0; x < 26; x++) {

                    rem[x] = halfFreq[x];
                }

                /*
                 * Rebuild the prefix for the next
                 * backtracking position.
                 */
                for (int j = 0; j < i; j++) {

                    int x =
                        targetHalf[j] - 'a';

                    if (rem[x] > 0)
                        rem[x]--;
                }
            }

            /*
             * Restore current character for the
             * next iteration.
             */
            rem[current]++;
        }

        return "";
    }
};
