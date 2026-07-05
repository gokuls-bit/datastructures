class Solution(object):
    def pathsWithMaxScore(self, board):
    
        MOD = 10 ** 9 + 7
        n = len(board)

        score = [[-1] * n for _ in range(n)]
        ways = [[0] * n for _ in range(n)]

        score[n - 1][n - 1] = 0
        ways[n - 1][n - 1] = 1

        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):

                if board[i][j] == 'X':
                    continue

                if i == n - 1 and j == n - 1:
                    continue

                best = -1
                cnt = 0

                for x, y in ((i + 1, j), (i, j + 1), (i + 1, j + 1)):
                    if x < n and y < n and score[x][y] != -1:
                        if score[x][y] > best:
                            best = score[x][y]
                            cnt = ways[x][y]
                        elif score[x][y] == best:
                            cnt = (cnt + ways[x][y]) % MOD

                if best == -1:
                    continue

                val = 0
                if board[i][j].isdigit():
                    val = int(board[i][j])

                score[i][j] = best + val
                ways[i][j] = cnt

        if ways[0][0] == 0:
            return [0, 0]

        return [score[0][0], ways[0][0]]
