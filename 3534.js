/**
 * @param {number} n
 * @param {number[]} nums
 * @param {number} maxDiff
 * @param {number[][]} queries
 * @return {number[]}
 */
var pathExistenceQueries = function (n, nums, maxDiff, queries) {

    const arr = [];
    for (let i = 0; i < n; i++) {
        arr.push([nums[i], i]);
    }

    arr.sort((a, b) => a[0] - b[0]);

    const pos = new Array(n);
    const val = new Array(n);

    for (let i = 0; i < n; i++) {
        val[i] = arr[i][0];
        pos[arr[i][1]] = i;
    }

    // Connected components in sorted order
    const comp = new Array(n);
    comp[0] = 0;
    let cid = 0;
    for (let i = 1; i < n; i++) {
        if (val[i] - val[i - 1] > maxDiff) cid++;
        comp[i] = cid;
    }

    const LOG = 17;

    // farthest index reachable in one jump to the right
    const right = new Array(n);
    let j = 0;
    for (let i = 0; i < n; i++) {
        while (j + 1 < n && val[j + 1] - val[i] <= maxDiff) j++;
        right[i] = j;
    }

    const up = Array.from({ length: LOG }, () => new Array(n));
    for (let i = 0; i < n; i++) up[0][i] = right[i];
    for (let k = 1; k < LOG; k++) {
        for (let i = 0; i < n; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }

    // farthest index reachable in one jump to the left
    const left = new Array(n);
    let p = 0;
    for (let i = 0; i < n; i++) {
        while (val[i] - val[p] > maxDiff) p++;
        left[i] = p;
    }

    const down = Array.from({ length: LOG }, () => new Array(n));
    for (let i = 0; i < n; i++) down[0][i] = left[i];
    for (let k = 1; k < LOG; k++) {
        for (let i = 0; i < n; i++) {
            down[k][i] = down[k - 1][down[k - 1][i]];
        }
    }

    function goRight(a, b) {
        let cur = a;
        let ans = 0;

        for (let k = LOG - 1; k >= 0; k--) {
            if (up[k][cur] < b) {
                cur = up[k][cur];
                ans += 1 << k;
            }
        }

        return ans + 1;
    }

    function goLeft(a, b) {
        let cur = a;
        let ans = 0;

        for (let k = LOG - 1; k >= 0; k--) {
            if (down[k][cur] > b) {
                cur = down[k][cur];
                ans += 1 << k;
            }
        }

        return ans + 1;
    }

    const res = [];

    for (const [u, v] of queries) {

        const a = pos[u];
        const b = pos[v];

        if (a === b) {
            res.push(0);
            continue;
        }

        if (comp[a] !== comp[b]) {
            res.push(-1);
            continue;
        }

        if (a < b) {
            res.push(goRight(a, b));
        } else {
            res.push(goLeft(a, b));
        }
    }

    return res;
};
