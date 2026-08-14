class Solution {
public:
    int maximumLengthSubstring(string s) {

        vector<int> freq(26, 0);

        int left = 0;
        int answer = 0;

        for (int right = 0; right < s.size(); right++) {

            freq[s[right] - 'a']++;

            while (freq[s[right] - 'a'] > 2) {

                freq[s[left] - 'a']--;

                left++;
            }

            answer = max(
                answer,
                right - left + 1
            );
        }

        return answer;
    }
};
