#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

class Graph {
private:
    vector<vector<pair<int, int> > > adjList;
    int numVertex;
    int numEdge;

public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int numVertices) : adjList(numVertices), numVertex(numVertices), numEdge(0) {}

    // Method to add an undirected edge between two vertices with a given weight
    void addEdge(int src, int dest, int weight) {
        adjList[src].emplace_back(dest, weight);
        adjList[dest].emplace_back(src, weight);  // Assuming an undirected graph
        numEdge++;
    }

    void deleteEdge(int src, int dest) {
        for (vector<pair<int, int> >::iterator iter = adjList[src].begin(); iter != adjList[src].end(); iter++) {
            if (iter->first == dest) {
                adjList[src].erase(iter);
                break;
            }
        }

        for (vector<pair<int, int> >::iterator iter = adjList[dest].begin(); iter != adjList[dest].end(); iter++) {
            if (iter->first == src) {
                adjList[dest].erase(iter);
                break;
            }
        }
    }

    vector<pair<int, int> > getEdge_inOrder() {
        struct edge {
            int start, end, weight;
            edge(int _start, int _end, int _weight) : start(_start), end(_end), weight(_weight){}
            bool operator<(edge& other) { return this->weight > other.weight; }
        };
        vector<edge> edges(numEdge);
        for (int i = 0; i < numVertex; i++) {
            for (int j = 0; j < adjList[i].size(); j++)
                edges.push_back(edge(i, adjList[i][j].first, adjList[i][j].second));
        }
        sort(edges.begin(), edges.end());
        vector<pair<int, int> > sorted_edges(numEdge);
        for (int i = 0; i < numEdge; i++)
            sorted_edges[i] = make_pair(edges[i].start, edges[i].end);
        return sorted_edges;
    }

    int getNumVertex() { return numVertex; }

    int getNumEdge() { return numEdge; }

    vector<vector<pair<int, int> > > getEdge() { return adjList; }

    Graph& operator=(Graph other) {
        if (this != &other) {
            // Clear the current adjacency list
            adjList.clear();
            // Resize to match the size of the other graph
            adjList.resize(other.adjList.size());

            // Copy each adjacency list
            for (size_t i = 0; i < other.adjList.size(); ++i) {
                adjList[i] = other.adjList[i];
            }
        }
        return *this;
    }

    // Method to get the first neighbor of a vertex
    pair<int, int> getFirstNeighbor(int vertex) {
        if (!adjList[vertex].empty()) {
            return adjList[vertex][0];
        } else {
            // Return a pair with -1 if there are no neighbors
            return make_pair(-1, -1);
        }
    }

    // Method to get the next neighbor edge based on a given vertex and edge
    pair<int, int> getNextNeighbor(int vertex, pair<int, int> currentNeighbor) {
        for (size_t i = 0; i < adjList[vertex].size() - 1; ++i) {
            if (adjList[vertex][i] == currentNeighbor) {
                return adjList[vertex][i + 1];
            }
        }

        // Return a pair with -1 if there are no more neighbors
        return make_pair(-1, -1);
    }

    int getWeight(int start, int end) {
        for (int i = 0; i < adjList[start].size(); i++) {
            if (adjList[start][i].first == end)
                return adjList[start][i].second;
        }
        return -1;
    }

     // Dijkstra's algorithm to find the shortest paths from a source vertex to all other vertices
    void dijkstra(int source, vector<int>& dist, vector<int>& path) {
        int numVertices = adjList.size();
        dist.assign(numVertices, INT_MAX);
        path.assign(numVertices, -1);

        // Priority queue to store vertices and their distances
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

        // Initialize distance from source to itself as 0
        dist[source] = 0;
        pq.push(make_pair(0, source));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    path[v] = u;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }

    void DFS(int start_vertex) {
        vector<bool> visited(adjList.size(), false);
        stack<int> S;
        S.push(start_vertex);
        while(!S.empty()) {
            int current = S.top();
            S.pop();
            if (visited[current] == false) {
                //do something
                cout << current;//for example
                visited[current] = true;
            }
            for (int i = 0; i < adjList[current].size(); i++) {
                int next_vertex = adjList[current][i].first;
                if (visited[next_vertex] == false) {
                    S.push(next_vertex);
                }
            }
        }
    }

    bool find_DFS(int u, int v, vector<bool>& visited, vector<int>& path) {
        visited[u] = true;
        path.push_back(u);
        if (u == v)
            return true;
        for (int i = 0; i < adjList[u].size(); i++) {
            if (visited[adjList[u][i].first] == false) {
                if (find_DFS(adjList[u][i].first, v, visited, path))
                    return true;
            }
        }
        path.pop_back();
        return false;
    }

    vector<int> find_DFS_launcher(int u, int v) {
        vector<bool> visited(adjList.size(), false);
        vector<int> path;
        find_DFS(u, v, visited, path);
        return path;
    }

    void print() {
         for (size_t i = 0; i < adjList.size(); ++i) {
            cout << "Adjacency list of vertex " << i << ": ";
            for (pair<int, int> neighbor : adjList[i]) {
                cout << neighbor.first << " ";
            }
            cout << endl;
        }
    }

    bool isConnected();

    void DFS_rec(int v, vector<int>& reversed, vector<bool>& visited) {
        visited[v] = true;
        for (int i = 0; i < adjList[v].size(); i++)
            if (!visited[adjList[v][i].first])
                DFS_rec(adjList[v][i].first, reversed, visited);
        reversed.push_back(v);
    }

    vector<int> DFS_TopologicalSort() {
        vector<int> reversed(numVertex);
        vector<bool> visited(numVertex, false);
        for (int i = 0; i < numVertex; i++) {
            if (!visited[i])
                DFS_rec(i, reversed, visited);
        }
        reverse(reversed.begin(), reversed.end());
        return reversed;
    }
};

bool Graph::isConnected() {
    vector<bool> visited(numVertex);
    DFS(0);//, visited);
    for (int i = 0; i < numVertex; i++)
        if (visited[i] == false)
            return false;
    return true;
}

Graph& create_break_circle(Graph G) {
    Graph min_tree = G;
    vector<pair<int, int> > sorted_edges = G.getEdge_inOrder();
    int current = 0;
    while(min_tree.getNumEdge() > min_tree.getNumVertex() - 1 || current == sorted_edges.size() - 1) {
        int start = sorted_edges[current].first;
        int end = sorted_edges[current].second;
        min_tree.deleteEdge(start, end);
        if (!min_tree.isConnected())
            min_tree.addEdge(start, end, G.getWeight(start, end));
        current++;
    }
    return min_tree;
}

int main() {
    // Example usage
    Graph myGraph(5);  // Create a graph with 5 vertices

    myGraph.addEdge(0, 1, 10);
    myGraph.addEdge(0, 2, 15);
    myGraph.addEdge(1, 2, 20);
    myGraph.addEdge(2, 3, 5);
    myGraph.addEdge(3, 4, 8);

    // Get the first neighbor of vertex 0
    pair<int, int> firstNeighbor = myGraph.getFirstNeighbor(0);
    //cout << "First Neighbor of Vertex 0: " << firstNeighbor.first << " (Weight: " << firstNeighbor.second << ")\n";

    // Get the next neighbor of vertex 0 based on the first neighbor
    pair<int, int> nextNeighbor = myGraph.getNextNeighbor(0, firstNeighbor);
    //cout << "Next Neighbor of Vertex 0: " << nextNeighbor.first << " (Weight: " << nextNeighbor.second << ")\n";

    vector<int> path = myGraph.find_DFS_launcher(0, 4);
    for (int i : path)
        cout << i << " ";

    return 0;
}