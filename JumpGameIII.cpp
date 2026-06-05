class Solution {
public:
    bool canReach(vector<int>& arr, int start) {

        int n = arr.size();

        queue<int> q;

        vector<bool> visited(n, false);

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {

            int i = q.front();
            q.pop();

            if (arr[i] == 0)
                return true;

            int forward = i + arr[i];
            int backward = i - arr[i];

            if (forward < n && !visited[forward]) {
                visited[forward] = true;
                q.push(forward);
            }

            if (backward >= 0 && !visited[backward]) {
                visited[backward] = true;
                q.push(backward);
            }
        }

        return false;
    }
};
class Solution {
public:
    struct Node {
        long long ways;
        long long sum;
    };

    string s;
    Node dp[20][3][11][11];
    bool vis[20][3][11][11];

    Node dfs(int pos, int lenState, int p2, int p1, bool tight) {
        if (pos == (int)s.size()) {
            return {1, 0};
        }

        if (!tight && vis[pos][lenState][p2][p1]) {
            return dp[pos][lenState][p2][p1];
        }

        int limit = tight ? (s[pos] - '0') : 9;

        long long totalWays = 0;
        long long totalSum = 0;

        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);

            int nLen = lenState;
            int np2 = p2;
            int np1 = p1;

            long long contrib = 0;

            if (lenState == 0) {
                if (d == 0) {
                    nLen = 0;           // still leading zeros
                } else {
                    nLen = 1;
                    np1 = d;
                }
            }
            else if (lenState == 1) {
                nLen = 2;
                np2 = p1;
                np1 = d;
            }
            else {
                if ((p1 > p2 && p1 > d) ||
                    (p1 < p2 && p1 < d)) {
                    contrib = 1;
                }

                nLen = 2;
                np2 = p1;
                np1 = d;
            }

            Node nxt = dfs(pos + 1, nLen, np2, np1, ntight);

            totalWays += nxt.ways;
            totalSum += nxt.sum + contrib * nxt.ways;
        }

        Node ans = {totalWays, totalSum};

        if (!tight) {
            vis[pos][lenState][p2][p1] = true;
            dp[pos][lenState][p2][p1] = ans;
        }

        return ans;
    }

    long long solve(long long x) {
        if (x <= 0) return 0;

        s = to_string(x);
        memset(vis, 0, sizeof(vis));

        return dfs(0, 0, 10, 10, true).sum;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
