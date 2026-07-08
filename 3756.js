/**
 * @param {string} s
 * @param {number[][]} queries
 * @return {number[]}
 */
var sumAndMultiply = function(s, queries) {

    const MOD = 1000000007n;
    const n = s.length;

    const cnt = new Array(n + 1).fill(0);
    const digitSum = new Array(n + 1).fill(0);

    

    const digits = []; 

    for (let i = 0; i < n; i++) {
        cnt[i + 1] = cnt[i];
        digitSum[i + 1] = digitSum[i];

        const d = s.charCodeAt(i) - 48;

        if (d !== 0) {
            cnt[i + 1]++;
            digitSum[i + 1] += d;
            digits.push(d);
        }
    }

    const m = digits.length;

    const pow10 = new Array(m + 1).fill(0n);
    pow10[0] = 1n;

    for (let i = 1; i <= m; i++) {
        pow10[i] = (pow10[i - 1] * 10n) % MOD;
    }

    const prefVal = new Array(m + 1).fill(0n);

    for (let i = 0; i < m; i++) {
        prefVal[i + 1] = (prefVal[i] * 10n + BigInt(digits[i])) % MOD;
    }

    const ans = [];

    for (const [l, r] of queries) {

        const L = cnt[l];
        const R = cnt[r + 1];

        const len = R - L;

        let x =
            (prefVal[R] -
                (prefVal[L] * pow10[len]) % MOD +
                MOD) % MOD;

        const sum = BigInt(digitSum[r + 1] - digitSum[l]);

        ans.push(Number((x * sum) % MOD));
    }

    return ans;
};
