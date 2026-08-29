
class Solution {
public:
    vector<int> lexicographicallySmallestArray(
        vector<int>& nums,
        int limit
    ) {

        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by value
        sort(arr.begin(), arr.end());

        vector<int> answer(n);

        int start = 0;

        while (start < n) {

            int end = start;

            // Find a connected group.
            while (end + 1 < n &&
                   arr[end + 1].first - arr[end].first <= limit) {

                end++;
            }

            // Collect original indices of this group.
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(arr[i].second);
            }

            // Original positions must be sorted so that
            // smallest values go to the earliest positions.
            sort(indices.begin(), indices.end());

            // Values are already sorted because arr is sorted.
            for (int i = 0; i < (int)indices.size(); i++) {

                answer[indices[i]] =
                    arr[start + i].first;
            }

            start = end + 1;
        }

        return answer;
    }
};
