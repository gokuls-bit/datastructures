/**
 * @param {number} n
 * @return {number[]}
 */
var lexicalOrder = function(n) {
    const result = [];
    let current = 1;

    for (let i = 0; i < n; i++) {
        result.push(current);

        // Go deeper: 1 -> 10 -> 100
        if (current * 10 <= n) {
            current *= 10;
        } 
        else {
            // Move to next valid number
            while (
                current % 10 === 9 || 
                current + 1 > n
            ) {
                current = Math.floor(current / 10);
            }

            current++;
        }
    }

    return result;
};
