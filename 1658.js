/**
 * @param {number[]} nums
 * @param {number} x
 * @return {number}
 */
var minOperations = function(nums, x) {
    const total = nums.reduce((sum, val) => sum + val, 0);
    const target = total - x;

    if (target < 0) return -1;

    // Find the longest subarray whose sum is target.
    let left = 0;
    let sum = 0;
    let maxLen = -1;

    for (let right = 0; right < nums.length; right++) {
        sum += nums[right];

        while (sum > target && left <= right) {
            sum -= nums[left];
            left++;
        }

        if (sum === target) {
            maxLen = Math.max(maxLen, right - left + 1);
        }
    }

    if (maxLen === -1) return -1;

    return nums.length - maxLen;
};
