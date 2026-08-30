class Solution {
public:
    int minimumDeletions(vector<int>& nums) {

        int n = nums.size();

        // Find the index of the minimum element.
        int minIndex = 0;

        for (int i = 1; i < n; i++) {

            if (nums[i] < nums[minIndex]) {
                minIndex = i;
            }
        }

        // Find the index of the maximum element.
        int maxIndex = 0;

        for (int i = 1; i < n; i++) {

            if (nums[i] > nums[maxIndex]) {
                maxIndex = i;
            }
        }

        // Put min and max in sorted index order.
        int left = min(minIndex, maxIndex);
        int right = max(minIndex, maxIndex);

        /*
         * Three possibilities:
         *
         * 1. Delete both from the beginning.
         * 2. Delete both from the end.
         * 3. Delete minimum from beginning and
         *    maximum from the end.
         */

        int option1 = right + 1;

        int option2 = n - left;

        int option3 = (left + 1) + (n - right);

        return min({
            option1,
            option2,
            option3
        });
    }
};
