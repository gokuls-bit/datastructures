#include <stdio.h>
#include <string.h>

#define MAXL 105
#define NEG -1000000000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxMutatedViruses(int N, int contamination_levels[]) {
    int freq[MAXL] = {0};

    for (int i = 0; i < N; i++) {
        freq[contamination_levels[i]]++;
    }

    // dp[level][used_from_level][used_from_next]
    int dp[MAXL][3][3];

    for (int i = 0; i < MAXL; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                dp[i][j][k] = NEG;
            }
        }
    }

    dp[1][0][0] = 0;

    for (int level = 1; level <= 100; level++) {
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                if (dp[level][a][b] == NEG) continue;

                // a = already used from current level
                // b = already used from next level
                if (freq[level] < a || freq[level + 1] < b) continue;

                int remainingCurrent = freq[level] - a;

                /*
                   Make t consecutive groups:
                   (level, level+1, level+2)

                   We already know b viruses of (level+1) are reserved
                   from previous transition, so now if we create t new
                   consecutive groups, then for next state:
                   - level+1 will have b+t used
                   - level+2 will have t used

                   t can't exceed remainingCurrent,
                   can't exceed available of level+1 after already reserved b,
                   and can't exceed available of level+2
                */
                int maxT = remainingCurrent;
                if (freq[level + 1] - b < maxT) maxT = freq[level + 1] - b;
                if (freq[level + 2] < maxT) maxT = freq[level + 2];

                for (int t = 0; t <= maxT && t < 3; t++) {
                    int rem = remainingCurrent - t;

                    // after using t consecutive groups, remaining current
                    // can form triples of same level
                    int sameGroups = rem / 3;

                    dp[level + 1][b + t][t] =
                        max(dp[level + 1][b + t][t],
                            dp[level][a][b] + t + sameGroups);
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
    scanf("%d", &V);

    int contamination_levels[V];
    for (int i = 0; i < V; i++) {
        scanf("%d", &contamination_levels[i]);
    }

    int result = maxMutatedViruses(V, contamination_levels);
    printf("%d\n", result);

    return 0;
}
