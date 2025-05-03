#include <bits/stdc++.h>
using namespace std;
class edge {
public:
    int v;
    int wt;

    edge(int v, int wt) {
        this->v = v;
        this->wt = wt;
    }
};
void addnode(int u, int v, int wt, bool undir, vector<vector<edge>>& g) {
    g[u].push_back(edge(v, wt)); // storing destination and weight as an object
    if (undir) {
        g[v].push_back(edge(u, wt));
    }
}
void printg(vector<vector<edge>> g) {
    for (int i = 0; i < g.size(); i++) {
        cout << "Vertex " << i << " :: ";
        for (auto it : g[i]) {
            cout << "(" << it.v << "," << it.wt << ") ";
        }
        cout << endl;
    }
}
void djkstras(vector<vector<edge>>& g, int src, int v) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min heap
    pq.push({0, src});

    vector<int> dist(v, INT_MAX);
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        vector<edge> neighbours = g[u];
        for (auto it : neighbours) {
            if (dist[it.v] > dist[u] + it.wt) {
                dist[it.v] = dist[u] + it.wt; // edge relaxation
                pq.push({dist[it.v], it.v});
            }
        }
    }

    for (int i = 0; i < v; i++) {
        cout << "Shortest path distance for vertex " << i << " : " << dist[i] << endl;
    }
}
void prims(vector<vector<edge>>& g, int src, int v) {
    vector<bool> vis(v, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min heap

    pq.push({0, src});
    int ans = 0;

    while (!pq.empty()) {
        int curr = pq.top().second;
        int wt = pq.top().first;
        pq.pop();

        if (!vis[curr]) {
            vis[curr] = true;
            ans += wt;

            vector<edge> neigh = g[curr];
            for (auto it : neigh) {
                if (!vis[it.v]) {
                    pq.push({it.wt, it.v});
                }
            }
        }
    }

    cout << "MST Total Weight (Prim's): " << ans << endl;
}
int main() {
    cout << "----------------------> Prim's Algorithm <--------------------------" << endl;

    vector<vector<edge>> g(4);
    addnode(0, 1, 10, true, g);
    addnode(0, 2, 15, true, g);
    addnode(0, 3, 30, true, g);
    addnode(1, 3, 40, true, g);
    addnode(2, 3, 50, true, g);

    printg(g);
    prims(g, 0, 4);

    cout << "\n----------------------> Dijkstra's Algorithm <--------------------------" << endl;
    vector<vector<edge>> g2(4);
    addnode(0, 1, 10, false, g2);
    addnode(0, 2, 15, false, g2);
    addnode(0, 3, 30, false, g2);
    addnode(1, 3, 40, false, g2);
    addnode(2, 3, 50, false, g2);

    printg(g2);
    djkstras(g2, 0, 4);

    return 0;
}
