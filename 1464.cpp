class Solution {
public:
    int maxProduct(vector<int>& nums) {

        int largest = 0;
        int secondLargest = 0;

        for (int number : nums) {

            if (number >= largest) {

                secondLargest = largest;

                largest = number;
            }
            else if (number > secondLargest) {

                secondLargest = number;
            }
        }

        return (largest - 1) * (secondLargest - 1);
    }
};
