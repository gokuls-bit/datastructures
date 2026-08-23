class Solution {
public:
    bool sumGame(string num) {

        int n = num.size();

        int half = n / 2;

        int leftSum = 0;
        int rightSum = 0;

        int leftQuestion = 0;
        int rightQuestion = 0;

        for (int i = 0; i < half; i++) {

            if (num[i] == '?') {
                leftQuestion++;
            } else {
                leftSum += num[i] - '0';
            }
        }

        for (int i = half; i < n; i++) {

            if (num[i] == '?') {
                rightQuestion++;
            } else {
                rightSum += num[i] - '0';
            }
        }

        // If the number of '?' is odd,
        // Alice can always force a win.
        if ((leftQuestion + rightQuestion) % 2 == 1) {
            return true;
        }

        // Difference in the known sums.
        int difference = leftSum - rightSum;

        // Alice wins if the current difference
        // cannot be neutralized by the remaining '?'.
        int questionDifference =
            leftQuestion - rightQuestion;

        /*
            Each pair of '?' effectively allows Bob
            to adjust the difference by at most 9.

            Alice wins unless:
            
            |difference| == 9 * |questionDifference| / 2
        */
        return difference !=
               -9 * questionDifference / 2;
    }
};
