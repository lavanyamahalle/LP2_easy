// Online C++ compiler to run C++ program online
#include <iostream>
#include<list>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
class graph{
    int v;
    list<int>*l;//This is a pointer to an array of linked lists.
                //Each list<int> represents the adjacency list for a vertex — i.e., a list of neighbors.
    public:
    graph(int v){
        this->v=v;
        l=new list<int>[v];
        //Dynamically allocates an array of list<int> of size v.
        //Each element in this array is an empty linked list to start with.
        // After this line, l[0] to l[v-1] are ready to store connections (edges) for each corresponding node.
    }
 void addintolist(int u,int v){
     l[u].push_back(v);
     l[v].push_back(u);
 }
 void printlist(int v){
     cout<<"-------------------------------"<<endl;
     cout<<"Adj list:"<<endl;
     for(int u=0;u<v;u++){
         list<int>neighbours=l[u];
         cout<<u<<":";
        for(auto it:neighbours){
         cout<<it<<",";
        }
     cout<<endl;
     }
     cout<<"-------------------------------"<<endl;
 }
 void bfs(int u,int v){
     vector<bool>vis(v,false);
     for(int i=0;i<v;i++){
         if(!vis[i]){
              bfshelp(i,v,vis);
         }
    }
    cout<<"-----------------BFS"<<endl;
 }
 void bfshelp(int u,int v,vector<bool>&vis){
     queue<int>q;
     q.push(u);vis[u]=true;
     while(!q.empty()){
         int curr=q.front();
         q.pop();
         cout<<curr;
         list<int>neigh=l[curr];
         for(auto it:neigh){
             if(!vis[it]){
                 q.push(it);
                 vis[it]=true;
             }
         }
     }
    
 }
 void dfs(int u,int v){
     vector<bool>vis(v,false);
     
     for(int i=0;i<v;i++){
         if(!vis[i]){
             dfshelper(i,v,vis);
         }
    }
       cout<<"-----------------DFS"<<endl;
 }
 
 void dfshelper(int u,int v,vector<bool>&vis){
     vis[u]=true;
     cout<<u;
     list<int>neigh=l[u];
     for(auto it:neigh){
         if(!vis[it]){
              dfshelper(it,v,vis);
         }
       
     }
 }
};


int main() {
    graph g(5);
    g.addintolist(1,2);
    g.addintolist(2,3);
    g.addintolist(3,4);
    g.addintolist(4,1);
    g.printlist(5); 
    
    g.bfs(0,5); 
    g.dfs(0,5);
    return 0;
}


/*

THEORY:

### ✅ **Adjacency Matrix**
- **Definition**: A 2D array where `matrix[i][j] = 1` if there's an edge from node `i` to `j`.
- **Space**: O(V²)
- **Best for**: Dense graphs

```cpp
// Example: Undirected graph with 4 nodes
int V = 4;
int adjMatrix[4][4] = {0};

void addEdge(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;  // for undirected graph
}
```
Adjacency Matrix:
0 1 1 0
1 0 1 0
1 1 0 1
0 0 1 0


---

### ✅ **Adjacency List**
- **Definition**: An array of vectors where `list[i]` stores all neighbors of node `i`.
- **Space**: O(V + E)
- **Best for**: Sparse graphs

```cpp
// Example: Undirected graph with 4 nodes
int V = 4;
vector<int> adjList[4];

void addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);  // for undirected graph
}
```
Adjacency List:
0: 1 2 
1: 0 2 
2: 0 1 3 
3: 2 

---

### 📊 **Comparison Table**

| Feature             | Adjacency List       | Adjacency Matrix     |
|---------------------|----------------------|-----------------------|
| Space Complexity     | O(V + E)             | O(V²)                 |
| Check if edge exists | O(degree)            | O(1)                  |
| Add edge             | O(1)                 | O(1)                  |
| Remove edge          | O(degree)            | O(1)                  |
| Iterate neighbors    | Efficient            | Inefficient (O(V))    |
| Best for             | Sparse graphs        | Dense graphs          |



Adjacency Matrix is faster for edge existence checking.
Adjacency List is more space-efficient and faster for neighbor iteration in sparse graphs.



### ✅ **BFS (Breadth-First Search)**

- **How it works**: Visits all neighbors **level by level** using a **queue**.
- **Data Structure**: Queue
- **Time Complexity**: O(V + E)
- **Best for**: Finding the shortest path in an unweighted graph.

**Real-life example**:
> Finding the **shortest path in a maze** or in **Google Maps** from your home to a store — you check all nearby roads first before going further.

---

### ✅ **DFS (Depth-First Search)**

- **How it works**: Goes **deep** into one path before backtracking using a **stack** (or recursion).
- **Data Structure**: Stack (or function call stack)
- **Time Complexity**: O(V + E)
- **Best for**: Exploring all paths, topological sorting, or cycle detection.

**Real-life example**:
> Solving a **maze by hand** — you keep going down one path until you hit a dead end, then backtrack and try another path.

---

### 🔄 Comparison Summary

| Feature        | BFS                        | DFS                         |
|----------------|-----------------------------|------------------------------|
| Strategy       | Level by level              | Depth-first                 |
| Uses           | Shortest path               | Full exploration, cycles    |
| Structure      | Queue                       | Stack / Recursion           |
| Real-world use | Navigation, social networks | Puzzle solving, AI search   |

