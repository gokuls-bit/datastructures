from collections import deque

class Solution(object):
    def findMaxPathScore(self, edges, online, k):
        """
        :type edges: List[List[int]]
        :type online: List[bool]
        :type k: int
        :rtype: int
        """

        n = len(online)

        if n == 0:
            return -1

        vals = sorted(set(c for _, _, c in edges))

        if not vals:
            return -1

        def check(limit):
            g = [[] for _ in range(n)]
            indeg = [0] * n

            for u, v, c in edges:
                if c < limit:
                    continue

                if u != 0 and u != n - 1 and not online[u]:
                    continue

                if v != 0 and v != n - 1 and not online[v]:
                    continue

                g[u].append((v, c))
                indeg[v] += 1

            q = deque()

            for i in range(n):
                if indeg[i] == 0:
                    q.append(i)

            INF = 10 ** 30
            dist = [INF] * n
            dist[0] = 0

            while q:
                u = q.popleft()

                if dist[u] != INF:
                    for v, c in g[u]:
                        if dist[v] > dist[u] + c:
                            dist[v] = dist[u] + c

                for v, _ in g[u]:
                    indeg[v] -= 1
                    if indeg[v] == 0:
                        q.append(v)

            return dist[n - 1] <= k

        lo = 0
        hi = len(vals) - 1
        ans = -1

        while lo <= hi:
            mid = (lo + hi) // 2

            if check(vals[mid]):
                ans = vals[mid]
                lo = mid + 1
            else:
                hi = mid - 1

        return ans
