/**
 * @param {number} n
 * @param {number[]} nums
 * @param {number} maxDiff
 * @param {number[][]} queries
 * @return {boolean[]}
 */
var pathExistenceQueries = function(n, nums, maxDiff, queries) {

    const comp = new Array(n);
    let id = 0;

    comp[0] = 0;

    for (let i = 1; i < n; i++) {
        if (nums[i] - nums[i - 1] > maxDiff) {
            id++;
        }
        comp[i] = id;
    }

    const ans = [];

    for (const [u, v] of queries) {
        ans.push(comp[u] === comp[v]);
    }

    return ans;
};
