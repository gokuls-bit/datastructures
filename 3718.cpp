class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {

        unordered_set<int> seen;

        for (int x : nums) {
            seen.insert(x);
        }

        int multiple = k;

        while (seen.count(multiple)) {
            multiple += k;
        }

        return multiple;
    }
};
