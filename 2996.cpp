class Solution {
public:
    int missingInteger(vector<int>& nums) {

        unordered_set<int> seen;

        for (int x : nums) {
            seen.insert(x);
        }

        int sum = nums[0];

        for (int i = 1; i < nums.size(); i++) {

            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            }
            else {
                break;
            }
        }

        int answer = sum;

        while (seen.count(answer)) {
            answer++;
        }

        return answer;
    }
};
