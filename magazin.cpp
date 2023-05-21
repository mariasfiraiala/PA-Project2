#include <bits/stdc++.h>

using namespace std;

#define NMAX (int)1e5 + 5

ifstream fin("magazin.in");
ofstream fout("magazin.out");
vector<int> adj[NMAX];
vector<int> nodesSubTree;
vector<bool> visited;
vector<int> traversal;
map<int, int> pos;

void dfs(int node) {
    nodesSubTree[node] = 0;
    visited[node] = true;
    traversal.push_back(node);
    pos[node] = traversal.size() - 1;

    for (auto &neigh : adj[node]) {
        if (!visited[neigh]) {
            dfs(neigh);
            nodesSubTree[node] += 1 + nodesSubTree[neigh];
        }
    }
}

void task(vector<int> adj[], int q, int n) {
    nodesSubTree = vector<int>(NMAX);
    visited = vector<bool>(NMAX, false);
    traversal = vector<int>();

    dfs(1);

    int d, e;
    for (int i = 0; i < q; ++i) {
        fin >> d >> e;

        if (nodesSubTree[d] >= e)
            fout << traversal[pos[d] + e] << "\n";
        else
            fout << -1 << "\n";
    }
}

int main() {
    int n, q;
    fin >> n >> q;

    int x;
    for (int i = 2; i <= n; ++i) {
        fin >> x;
        adj[x].push_back(i);
    }

    task(adj, q, n);

    return 0;
}
