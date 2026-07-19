class Solution {
public:
    string smallestSubsequence(string s) {

        vector<int> lastIndex(26);

        for (int i = 0; i < s.size(); i++) {

            lastIndex[s[i] - 'a'] = i;
        }

        vector<bool> visited(26, false);

        string result;

        for (int i = 0; i < s.size(); i++) {

            char currentCharacter = s[i];

            if (visited[currentCharacter - 'a']) {
                continue;
            }

            while (!result.empty() &&
                   result.back() > currentCharacter &&
                   lastIndex[result.back() - 'a'] > i) {

                visited[result.back() - 'a'] = false;

                result.pop_back();
            }

            result.push_back(currentCharacter);

            visited[currentCharacter - 'a'] = true;
        }

        return result;
    }
};
