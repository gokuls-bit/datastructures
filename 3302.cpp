class Solution {
public:
    vector<int> validSequence(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<int> last(m, -1);

        // last[i] = latest position in word1
        // from which word2[i..] can still be matched.
        int i = n - 1;
        int j = m - 1;

        while (i >= 0 && j >= 0) {

            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }

            i--;
        }

        vector<int> answer;

        bool usedMismatch = false;

        j = 0;

        for (i = 0; i < n && j < m; i++) {

            // Exact match
            if (word1[i] == word2[j]) {

                answer.push_back(i);
                j++;

                continue;
            }

            // Use our one allowed mismatch.
            //
            // We can use word1[i] here if:
            //
            // 1. This is the last character of word2.
            //
            // OR
            //
            // 2. word2[j+1...] can still be matched
            //    after position i.
            //
            if (!usedMismatch &&
                (j == m - 1 || last[j + 1] > i)) {

                answer.push_back(i);

                usedMismatch = true;

                j++;
            }
        }

        if (j != m) {
            return {};
        }

        return answer;
    }
};
