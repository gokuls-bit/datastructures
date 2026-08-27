class Solution {
public:
    string lexGreaterPermutation(string s, string target) {

        int n = s.size();

        // Frequency of every character in s.
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        string answer;

        // Try to keep the answer equal to target
        // for as long as possible.
        for (int i = 0; i < n; i++) {

            int current = target[i] - 'a';

            // First, try to put exactly target[i].
            if (freq[current] > 0) {

                freq[current]--;
                answer.push_back(target[i]);

                continue;
            }

            // We cannot match target[i].
            // Find the smallest character greater than it.
            int greater = -1;

            for (int c = current + 1; c < 26; c++) {

                if (freq[c] > 0) {
                    greater = c;
                    break;
                }
            }

            if (greater != -1) {

                answer.push_back(char('a' + greater));
                freq[greater]--;

                // Once we are greater than target,
                // append the remaining characters
                // in sorted order.
                for (int c = 0; c < 26; c++) {

                    while (freq[c] > 0) {

                        answer.push_back(
                            char('a' + c)
                        );

                        freq[c]--;
                    }
                }

                return answer;
            }

            /*
             * We matched target up to this point,
             * but cannot place a character greater
             * than target[i].

             * Therefore we must go backwards and
             * change an earlier character.
             */
            break;
        }

        /*
         * We reached here when the prefix matched
         * target but the complete permutation is not
         * greater than target.

         * Find the rightmost position where we can
         * replace target[i] with a larger character.
         */
        freq.assign(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        for (int i = n - 1; i >= 0; i--) {

            // Characters before i must match target.
            bool possible = true;

            vector<int> remaining = freq;

            for (int j = 0; j < i; j++) {

                int c = target[j] - 'a';

                if (remaining[c] == 0) {
                    possible = false;
                    break;
                }

                remaining[c]--;
            }

            if (!possible) {
                continue;
            }

            int current = target[i] - 'a';

            // Find the smallest character greater
            // than target[i].
            for (int c = current + 1; c < 26; c++) {

                if (remaining[c] > 0) {

                    string result =
                        target.substr(0, i);

                    result.push_back(
                        char('a' + c)
                    );

                    remaining[c]--;

                    // Append remaining characters
                    // in ascending order.
                    for (int x = 0; x < 26; x++) {

                        while (remaining[x] > 0) {

                            result.push_back(
                                char('a' + x)
                            );

                            remaining[x]--;
                        }
                    }

                    return result;
                }
            }
        }

        return "";
    }
};
