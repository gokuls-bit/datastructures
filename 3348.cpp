class Solution {
    long long req2 = 0, req3 = 0, req5 = 0, req7 = 0;
    int v2[10] = {0,0,1,0,2,0,1,0,3,0};
    int v3[10] = {0,0,0,1,0,0,1,0,0,2};
    int v5[10] = {0,0,0,0,0,1,0,0,0,0};
    int v7[10] = {0,0,0,0,0,0,0,1,0,0};

    long long min_d(long long r2, long long r3) {
        long long r2_0 = max(0LL, r2);
        long long r3_0 = max(0LL, r3);
        long long d0 = (r2_0 + 2) / 3 + (r3_0 + 1) / 2;

        long long r2_1 = max(0LL, r2 - 1);
        long long r3_1 = max(0LL, r3 - 1);
        long long d1 = 1 + (r2_1 + 2) / 3 + (r3_1 + 1) / 2;

        return min(d0, d1);
    }

    long long get_req_digits(long long r2, long long r3, long long r5, long long r7) {
        return max(0LL, r5) + max(0LL, r7) + min_d(r2, r3);
    }

public:
    string smallestNumber(string num, long long t) {
        long long temp = t;
        while (temp % 2 == 0) { req2++; temp /= 2; }
        while (temp % 3 == 0) { req3++; temp /= 3; }
        while (temp % 5 == 0) { req5++; temp /= 5; }
        while (temp % 7 == 0) { req7++; temp /= 7; }
        if (temp > 1) return "-1";

        int n = num.length();
        for (int i = 0; i < n; i++) {
            if (num[i] == '0') {
                for (int j = i; j < n; j++) num[j] = '1';
                break;
            }
        }

        auto check = [&](const string& s) {
            long long c2 = 0, c3 = 0, c5 = 0, c7 = 0;
            for (char c : s) {
                int d = c - '0';
                c2 += v2[d]; c3 += v3[d]; c5 += v5[d]; c7 += v7[d];
            }
            return c2 >= req2 && c3 >= req3 && c5 >= req5 && c7 >= req7;
        };

        if (check(num)) return num;

        vector<long long> p2(n + 1, 0), p3(n + 1, 0), p5(n + 1, 0), p7(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int d = num[i] - '0';
            p2[i+1] = p2[i] + v2[d];
            p3[i+1] = p3[i] + v3[d];
            p5[i+1] = p5[i] + v5[d];
            p7[i+1] = p7[i] + v7[d];
        }

        for (int i = n - 1; i >= 0; i--) {
            int orig = num[i] - '0';
            for (int d = orig + 1; d <= 9; d++) {
                long long rem2 = req2 - p2[i] - v2[d];
                long long rem3 = req3 - p3[i] - v3[d];
                long long rem5 = req5 - p5[i] - v5[d];
                long long rem7 = req7 - p7[i] - v7[d];

                long long needed = get_req_digits(rem2, rem3, rem5, rem7);
                if (needed <= n - 1 - i) {
                    string res = num.substr(0, i);
                    res += to_string(d);
                    int rem_len = n - 1 - i;
                    for (int j = 0; j < rem_len; j++) {
                        for (int nd = 1; nd <= 9; nd++) {
                            long long nrem2 = rem2 - v2[nd];
                            long long nrem3 = rem3 - v3[nd];
                            long long nrem5 = rem5 - v5[nd];
                            long long nrem7 = rem7 - v7[nd];
                            if (get_req_digits(nrem2, nrem3, nrem5, nrem7) <= rem_len - 1 - j) {
                                res += to_string(nd);
                                rem2 = nrem2; rem3 = nrem3; rem5 = nrem5; rem7 = nrem7;
                                break;
                            }
                        }
                    }
                    return res;
                }
            }
        }

        long long L = max((long long)n + 1, get_req_digits(req2, req3, req5, req7));
        string res = "";
        long long rem2 = req2, rem3 = req3, rem5 = req5, rem7 = req7;
        for (int j = 0; j < L; j++) {
            for (int nd = 1; nd <= 9; nd++) {
                long long nrem2 = rem2 - v2[nd];
                long long nrem3 = rem3 - v3[nd];
                long long nrem5 = rem5 - v5[nd];
                long long nrem7 = rem7 - v7[nd];
                if (get_req_digits(nrem2, nrem3, nrem5, nrem7) <= L - 1 - j) {
                    res += to_string(nd);
                    rem2 = nrem2; rem3 = nrem3; rem5 = nrem5; rem7 = nrem7;
                    break;
                }
            }
        }
        return res;
    }
};
