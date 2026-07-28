class Solution {
public:
    string smallestPalindrome(string s) {

        vector<int> count(26, 0);

        for (char character : s) {
            count[character - 'a']++;
        }

        string leftHalf = "";
        char middleCharacter = '\0';

        for (int i = 0; i < 26; i++) {

            leftHalf.append(count[i] / 2, char('a' + i));

            if (count[i] % 2 == 1) {
                middleCharacter = char('a' + i);
            }
        }

        string rightHalf = leftHalf;

        reverse(rightHalf.begin(), rightHalf.end());

        if (middleCharacter != '\0') {
            return leftHalf + middleCharacter + rightHalf;
        }

        return leftHalf + rightHalf;
    }
};
