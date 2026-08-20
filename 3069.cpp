class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {

        vector<int> first;
        vector<int> second;

        first.push_back(nums[0]);
        second.push_back(nums[1]);

        for (int i = 2; i < nums.size(); i++) {

            if (i % 2 == 0) {
                first.push_back(nums[i]);
            }
            else {
                second.push_back(nums[i]);
            }
        }

        for (int x : second) {
            first.push_back(x);
        }

        return first;
    }
};
