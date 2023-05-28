#include <bits/stdc++.h>

using namespace std;

#define NMAX (int)1e4 + 1
#define INF (1 << 30)

ifstream fin("teleportare.in");
ofstream fout("teleportare.out");

vector<pair<int, int>> adj[NMAX];
map<pair<int, int>, int> tunnels;

vector<int> dijkstra(int nodes) {
    vector<int> d(nodes + 1, INF);
    vector<int> p(nodes + 1, 0);

    set<pair<int, int>> pq;

    d[1] = 0;
    pq.insert({d[1], 1});

    while (!pq.empty()) {
        auto top = pq.begin();
        const auto [_, node] = *top;
        pq.erase(top);

        for (const auto& [neigh, w] : adj[node]) {
            /**
             * If the path can get improved and the tunnel either
             * doesn't exist or it's open, take that route
             */
            if (d[node] + w < d[neigh] &&
                (tunnels.find({node, neigh}) == tunnels.end() ||
                d[node] % tunnels[{node, neigh}] == 0)) {
                pq.erase({d[neigh], neigh});

                d[neigh] = d[node] + w;
                p[neigh] = node;

                pq.insert({d[neigh], neigh});
            }
        }
    }

    return d;
}

int main() {
    int n, m, k;

    fin >> n >> m >> k;
    for (int i = 1, x, y, w; i <= m; i++) {
        fin >> x >> y >> w;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }

    /* Mark all the tunnels as usual edges, but with cost 1 */
    for (int i = 1, x, y, p; i <= k; i++) {
        fin >> x >> y >> p;
        adj[x].push_back({y, 1});
        adj[y].push_back({x, 1});
        /* Save the tunnels for further inqueries */
        tunnels[{x, y}] = p;
        tunnels[{y, x}] = p;
    }

    fout << (dijkstra(n))[n];

    return 0;
}
