/**
 * @param {number[]} arr
 * @return {number[]}
 */
var arrayRankTransform = function(arr) {

    // Create sorted array with unique elements
    const sorted = [...new Set(arr)].sort((a, b) => a - b);

    // Store rank of each number
    const rank = new Map();

    for (let i = 0; i < sorted.length; i++) {
        rank.set(sorted[i], i + 1);
    }

    // Replace every element with its rank
    return arr.map(num => rank.get(num));
};
