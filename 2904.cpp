class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {

        int n = s.size();

        int left = 0;
        int ones = 0;

        string answer = "";

        for (int right = 0; right < n; right++) {

            if (s[right] == '1') {
                ones++;
            }

            while (ones > k) {

                if (s[left] == '1') {
                    ones--;
                }

                left++;
            }

            if (ones == k) {

                // Remove unnecessary leading zeros.
                while (left <= right && s[left] == '0') {
                    left++;
                }

                string current =
                    s.substr(left, right - left + 1);

                if (answer.empty() ||
                    current.size() < answer.size() ||
                    (current.size() == answer.size() &&
                     current < answer)) {

                    answer = current;
                }
            }
        }

        return answer;
    }
};
