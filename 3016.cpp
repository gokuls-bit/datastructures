class Solution {
public:
    int minimumPushes(string word) {

        vector<int> frequency(26, 0);

        for (char ch : word) {
            frequency[ch - 'a']++;
        }

        sort(frequency.begin(), frequency.end(), greater<int>());

        int answer = 0;

        for (int i = 0; i < 26; i++) {

            if (frequency[i] == 0) {
                break;
            }

            int pushes = (i / 8) + 1;

            answer += frequency[i] * pushes;
        }

        return answer;
    }
};
