class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {

        int n = nums.size();

        vector<int> freq(51, 0);

        for (int x : nums) {
            freq[x]++;
        }

        // Every element belongs to exactly one
        // subarray when k == 1.
        if (k == 1) {

            int answer = -1;

            for (int x : nums) {

                if (freq[x] == 1) {
                    answer = max(answer, x);
                }
            }

            return answer;
        }

        // When k == n, there is only one
        // subarray: the entire array.
        if (k == n) {

            return *max_element(
                nums.begin(),
                nums.end()
            );
        }

        // For 1 < k < n, only the first and
        // last elements can occur in exactly
        // one size-k subarray.
        int answer = -1;

        if (freq[nums[0]] == 1) {
            answer = max(answer, nums[0]);
        }

        if (freq[nums[n - 1]] == 1) {
            answer = max(answer, nums[n - 1]);
        }

        return answer;
    }
};
