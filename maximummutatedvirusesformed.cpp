#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxMutatedViruses(int N, vector<int>& contamination_levels) {
    const int MAXV = 105;
    const int NEG = -1e9;

    vector<int> cnt(MAXV, 0);
    for (int x : contamination_levels) cnt[x]++;

    // dp[i][a][b]
    // i = current contamination level
    // a = how many of level i are already used by previous consecutive groups
    // b = how many of level i+1 are already used by previous consecutive groups
    int dp[MAXV][3][3];

    for (int i = 0; i < MAXV; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                dp[i][j][k] = NEG;

    dp[1][0][0] = 0;

    for (int i = 1; i <= 100; i++) {
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                if (dp[i][a][b] < 0) continue;

                if (cnt[i] < a || cnt[i + 1] < b) continue;

                // remaining count of current level after fulfilling old consecutive groups
                int remain = cnt[i] - a;

                // how many NEW consecutive groups (i, i+1, i+2) can we start?
                int limit = min({remain, cnt[i + 1] - b, cnt[i + 2], 2});

                for (int take = 0; take <= limit; take++) {
                    int left = remain - take;

                    // use remaining current level for identical triples
                    int same = left / 3;

                    // next state:
                    // level i+1 already has b viruses used from previous,
                    // plus 'take' more due to new groups started here
                    // level i+2 has 'take' used due to new groups started here
                    dp[i + 1][b][take] = max(
                        dp[i + 1][b][take],
                        dp[i][a][b] + take + same
                    );
                }
            }
        }
    }

    int ans = 0;
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            ans = max(ans, dp[101][a][b]);
        }
    }

    return ans;
}

int main() {
    int V;
    cin >> V;

    vector<int> contamination_levels(V);
    for (int i = 0; i < V; i++) {
        cin >> contamination_levels[i];
    }

    cout << maxMutatedViruses(V, contamination_levels) << endl;
    return 0;
}
