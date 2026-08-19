class Solution {
public:
    int maxNumberOfFamilies(
        int n,
        vector<vector<int>>& reservedSeats
    ) {

        unordered_map<int, int> reserved;

        // Store reserved seats as a bitmask for each affected row.
        for (auto &seat : reservedSeats) {

            int row = seat[0];
            int col = seat[1];

            // We only care about seats 2 through 9.
            if (col >= 2 && col <= 9) {

                reserved[row] |= (1 << col);
            }
        }

        // Every completely empty row can fit 2 families.
        long long answer =
            2LL * (n - reserved.size());

        // Check rows containing reserved seats.
        for (auto &[row, mask] : reserved) {

            bool left =
                (mask & (1 << 2)) == 0 &&
                (mask & (1 << 3)) == 0 &&
                (mask & (1 << 4)) == 0 &&
                (mask & (1 << 5)) == 0;

            bool middle =
                (mask & (1 << 4)) == 0 &&
                (mask & (1 << 5)) == 0 &&
                (mask & (1 << 6)) == 0 &&
                (mask & (1 << 7)) == 0;

            bool right =
                (mask & (1 << 6)) == 0 &&
                (mask & (1 << 7)) == 0 &&
                (mask & (1 << 8)) == 0 &&
                (mask & (1 << 9)) == 0;

            if (left && right) {

                // Two families can sit on the left and right.
                answer += 2;

            }
            else if (left || middle || right) {

                // At least one valid group exists.
                answer += 1;
            }
        }

        return (int)answer;
    }
};
