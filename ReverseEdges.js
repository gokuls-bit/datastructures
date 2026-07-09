function countReverseEdges(gNodes, gFrom, gTo) {
    const graph = Array.from({ length: gNodes + 1 }, () => []);

    for (let i = 0; i < gFrom.length; i++) {
        const u = gFrom[i];
        const v = gTo[i];

        // original direction u -> v
        graph[u].push([v, 0]);
        graph[v].push([u, 1]);
    }

    const ans = new Array(gNodes + 1).fill(0);

    function dfs1(node, parent) {
        let cnt = 0;

        for (const [next, cost] of graph[node]) {
            if (next === parent) continue;
            cnt += dfs1(next, node) + cost;
        }

        return cnt;
    }

    ans[1] = dfs1(1, 0);

    function dfs2(node, parent) {
        for (const [next, cost] of graph[node]) {
            if (next === parent) continue;

            if (cost === 0)
                ans[next] = ans[node] + 1;
            else
                ans[next] = ans[node] - 1;

            dfs2(next, node);
        }
    }

    dfs2(1, 0);

    return ans.slice(1);
}
