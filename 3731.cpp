class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {

        int minimumValue = INT_MAX;
        int maximumValue = INT_MIN;

        unordered_set<int> seenNumbers;

        for (int number : nums) {

            minimumValue = min(minimumValue, number);

            maximumValue = max(maximumValue, number);

            seenNumbers.insert(number);
        }

        vector<int> missingElements;

        for (int current = minimumValue + 1;
             current < maximumValue;
             current++) {

            if (seenNumbers.find(current) == seenNumbers.end()) {

                missingElements.push_back(current);
            }
        }

        return missingElements;
    }
};
