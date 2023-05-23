#include <bits/stdc++.h>

using namespace std;

#define NMAX (int)1e5 + 1

ifstream fin("ferate.in");
ofstream fout("ferate.out");
vector<int> adj[NMAX];
bool visited[NMAX];
bool reachable[NMAX];

void dfs1(int node) {
    reachable[node] = true;
    for (auto neigh : adj[node])
        if (!reachable[neigh])
            dfs1(neigh);
}

void dfs2(int node, int *unreachable) {
    visited[node] = true;
    ++(*unreachable);
    for (auto neigh : adj[node])
        if (!visited[neigh] && !reachable[neigh])
            dfs2(neigh, unreachable);
}

int minEdges(int s, int n) {
    dfs1(s);
    vector<pair<int, int> > val;

    for (int node = 1; node <= n; ++node) {
        if (!reachable[node]) {
            int unreachable = 0;
            memset(visited, false, sizeof(visited));

            dfs2(node, &unreachable);
            val.push_back(make_pair(unreachable, node));
        }
    }

    sort(val.begin(), val.end(), greater<pair<int, int>>());

    int ans = 0;
    for (auto it : val) {
        if (!reachable[it.second]) {
            ++ans;
            dfs1(it.second);
        }
    }

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

    fout << minEdges(s, n);

    return 0;
}
