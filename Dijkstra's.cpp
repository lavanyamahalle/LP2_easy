// Online C++ compiler to run C++ program online
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
void printg(vector<vector<edge>> g) {
    for (int i = 0; i < g.size(); i++) {
        cout << "for vertex " << i << " :: ";
        for (auto it : g[i]) {
            cout << "(" << it.v << "," << it.wt << ") ";
        }
        cout << endl;
    }
}
void djkstras(vector<vector<edge>>& g, int src, int v) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min heap
    pq.push(make_pair(0, src));
    vector<int> dist(v, INT_MAX);
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        vector<edge> neighbours = g[u];
        for (auto it : neighbours) {
            if (dist[it.v] > dist[u] + it.wt) {
                dist[it.v] = dist[u] + it.wt; //edge relaxation
                pq.push(make_pair(dist[it.v], it.v));
            }
        }
    }

    int i = 0;
    for (auto it : dist) {
        cout << "Shortest path distance::: for " << i << " : " << it << endl;
        i = i + 1;
    }
}

int main() {
    int v = 6;
    vector<vector<edge>> g(v);

    /* 
    vector<edge> is a vector of edge objects (each element in this vector will be an edge object).
    vector<vector<edge>> is a vector of vector<edge>, which means it is a 2D structure 
    (essentially, a list of lists of edge objects).
    */

    g[0].push_back(edge(1, 2));
    g[0].push_back(edge(2, 4));
    g[1].push_back(edge(2, 1));
    g[1].push_back(edge(3, 7));
    g[2].push_back(edge(4, 3));
    g[3].push_back(edge(5, 1));
    g[4].push_back(edge(3, 2));
    g[4].push_back(edge(5, 5));

    /* 
    edge(2, 3) creates an object of type edge. 
    It calls the constructor edge(int v, int wt) and passes the values 2 and 3 to initialize the object's member variables v and wt.

    edge(2, 3): This is a temporary object created using the constructor. 
    It doesn't have a name because it's used immediately in the push_back function.

    g[0].push_back(...): The push_back function of the vector is adding the temporary edge object 
    to the vector g[0], which represents the adjacency list for vertex 0.
    */
    printg(g);
    djkstras(g, 0, v);
    return 0;
}
