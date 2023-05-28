#include <bits/stdc++.h>

using namespace std;

#define NMAX (int)1e5 + 1

ifstream fin("ferate.in");
ofstream fout("ferate.out");
vector<int> adj[NMAX];
vector<int> parent;
vector<int> found;
vector<int> low_link;
stack<int> nodes_stack;
vector<bool> in_stack;
vector<int> which_scc;
vector<int> in_scc;

void dfs(int node, int& timestamp, vector<vector<int>>& all_sccs) {
    found[node] = ++timestamp;
    low_link[node] = found[node];
    nodes_stack.push(node);
    in_stack[node] = true;

    /* Visit each neighbour of the current node */
    for (auto neigh : adj[node]) {
        /* Check if neighbour already visited */
        if (parent[neigh] != -1) {
            /**
             * The neighbour is in the same SCC as node only if it's
             * present in the visiting stack
             */
            if (in_stack[neigh]) {
                /* Update node with info from neighbour */
                low_link[node] = min(low_link[node], found[neigh]);
            }
            continue;
        }

        /* Mark the parent */
        parent[neigh] = node;
        dfs(neigh, timestamp, all_sccs);
        /* Update node with info from neighbour */
        low_link[node] = min(low_link[node], low_link[neigh]);
    }

    /* Check whether the current node is root for its SCC */
    if (low_link[node] == found[node]) {
        /* Extract all the nodes in the SCC where the current node is root */
        vector<int> scc;
        do {
            auto x = nodes_stack.top();
            nodes_stack.pop();
            in_stack[x] = false;

            scc.push_back(x);
        } while (scc.back() != node);

        all_sccs.push_back(scc);
    }
}

vector<vector<int>> tarjan_scc(int n) {
    parent = vector<int>(n + 1, -1);
    found = vector<int>(n + 1, -1);
    low_link = vector<int>(n + 1, -1);
    in_stack = vector<bool>(n + 1, false);

    vector<vector<int>> all_sccs;
    int timestamp = 0;
    /* Visit all nodes */
    for (int node = 1; node <= n; ++node) {
        if (parent[node] == -1) {
            parent[node] = node;

            dfs(node, timestamp, all_sccs);
        }
    }

    return all_sccs;
}

int task(int n, int s) {
    vector<vector<int>> sccs = tarjan_scc(n);

    /* Set the SCC of each node */
    which_scc = vector<int>(n + 1);
    for (int i = 0; i < sccs.size(); ++i) {
        for (auto node : sccs[i]) {
            which_scc[node] = i;
        }
    }

    /* Determine the in-degree for each SCC */
    in_scc = vector<int>(sccs.size() + 1, 0);
    for (int src = 1; src <= n; ++src)
        for (auto dest : adj[src])
            if (which_scc[src] != which_scc[dest])
                ++in_scc[which_scc[dest]];

    /**
     * We aren't interested of the in-degree of the SCC
     * in which the source resides; we mark it as 1
     */
    in_scc[which_scc[s]] = 1;

    /* Get all SCCs that have the in-degree 0 */
    int ans = 0;
    for (int i = 0; i < sccs.size(); ++i)
        if (!in_scc[i])
            ++ans;

    return ans;
}

int main() {
    int n, m, s;
    fin >> n >> m >> s;

    int x, y;
    for (int i = 0; i < m; ++i) {
        fin >> x >> y;
        adj[x].push_back(y);
    }

    fout << task(n, s);

    return 0;
}
