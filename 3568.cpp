class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        int startR = 0;
        int startC = 0;

        // Give every litter cell an ID.
        vector<vector<int>> id(
            m,
            vector<int>(n, -1)
        );

        int litterCount = 0;

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                if (classroom[i][j] == 'S') {
                    startR = i;
                    startC = j;
                }

                else if (classroom[i][j] == 'L') {

                    id[i][j] = litterCount;
                    litterCount++;
                }
            }
        }

        // Nothing to clean.
        if (litterCount == 0) {
            return 0;
        }

        int totalMasks = 1 << litterCount;

        /*
         * mask:
         *
         * bit = 0 -> litter not collected
         * bit = 1 -> litter collected
         *
         * Example with 3 litter:
         *
         * 000 -> nothing
         * 001 -> first litter
         * 010 -> second litter
         * 011 -> first + second
         * 111 -> all litter
         */

        int allCollected = totalMasks - 1;

        /*
         * visited[r][c][energy][mask]
         *
         * We flatten the 4D array into one vector
         * to avoid huge nested-vector overhead.
         */
        long long totalStates =
            1LL * m *
            n *
            (energy + 1) *
            totalMasks;

        vector<char> visited(totalStates, 0);

        auto encode = [&](int r,
                          int c,
                          int e,
                          int mask) -> long long {

            return ((((long long)r * n + c)
                     * (energy + 1) + e)
                    * totalMasks + mask);
        };

        /*
         * BFS state:
         *
         * row
         * column
         * remaining energy
         * collected litter mask
         */
        struct State {
            int r;
            int c;
            int e;
            int mask;
        };

        queue<State> q;

        int startMask = 0;

        /*
         * Starting position is S, so there is
         * normally no litter to collect here.
         */
        long long startCode =
            encode(
                startR,
                startC,
                energy,
                startMask
            );

        visited[startCode] = 1;

        q.push({
            startR,
            startC,
            energy,
            startMask
        });

        int moves = 0;

        int dr[4] = {
            -1,
             1,
             0,
             0
        };

        int dc[4] = {
             0,
             0,
            -1,
             1
        };

        while (!q.empty()) {

            int size = q.size();

            /*
             * Process one BFS level at a time.
             */
            while (size--) {

                State cur = q.front();
                q.pop();

                int r = cur.r;
                int c = cur.c;
                int e = cur.e;
                int mask = cur.mask;

                /*
                 * All litter has been collected.
                 */
                if (mask == allCollected) {
                    return moves;
                }

                /*
                 * Cannot make another move with zero
                 * energy.
                 *
                 * If we are standing on R, energy would
                 * already have been reset when we entered it.
                 */
                if (e == 0) {
                    continue;
                }

                for (int d = 0; d < 4; d++) {

                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    /*
                     * Check boundaries.
                     */
                    if (nr < 0 ||
                        nr >= m ||
                        nc < 0 ||
                        nc >= n) {

                        continue;
                    }

                    /*
                     * X is an obstacle.
                     */
                    if (classroom[nr][nc] == 'X') {
                        continue;
                    }

                    /*
                     * Normally one movement consumes
                     * one energy.
                     */
                    int nextEnergy = e - 1;

                    /*
                     * R ALWAYS restores energy to maximum.
                     *
                     * It does not matter whether we had
                     * 1, 2, 10, etc. energy before reaching R.
                     */
                    if (classroom[nr][nc] == 'R') {
                        nextEnergy = energy;
                    }

                    /*
                     * Copy current collected-litter mask.
                     */
                    int nextMask = mask;

                    /*
                     * If we step onto litter, collect it.
                     */
                    if (classroom[nr][nc] == 'L') {

                        int litterID =
                            id[nr][nc];

                        nextMask |=
                            (1 << litterID);
                    }

                    /*
                     * Encode new state.
                     */
                    long long code =
                        encode(
                            nr,
                            nc,
                            nextEnergy,
                            nextMask
                        );

                    /*
                     * Don't visit the same state twice.
                     */
                    if (!visited[code]) {

                        visited[code] = 1;

                        q.push({
                            nr,
                            nc,
                            nextEnergy,
                            nextMask
                        });
                    }
                }
            }

            moves++;
        }

        /*
         * BFS finished without collecting
         * every piece of litter.
         */
        return -1;
    }
};
