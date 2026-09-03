class Solution {
public:
    bool uniformArray(vector<int>& nums1) {

        int minOdd = INT_MAX;

        // Find the smallest odd number.
        for (int x : nums1) {

            if (x % 2 == 1) {
                minOdd = min(minOdd, x);
            }
        }

        // If there is no odd number,
        // all numbers are already even.
        if (minOdd == INT_MAX) {
            return true;
        }

        // If an even number is smaller than
        // the smallest odd number, it is impossible.
        for (int x : nums1) {

            if (x % 2 == 0 && x < minOdd) {
                return false;
            }
        }

        return true;
    }
};
