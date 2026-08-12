class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {

        unordered_map<int, int> frequency;

        int left = 0;
        int right = 0;

        int answer = 0;

        while (right < nums.size()) {

            // Add current element to the window
            frequency[nums[right]]++;

            // If its frequency exceeds k,
            // shrink the window from the left.
            while (frequency[nums[right]] > k) {

                frequency[nums[left]]--;

                left++;
            }

            // Current window is valid
            answer = max(answer, right - left + 1);

            right++;
        }

        return answer;
    }
};
