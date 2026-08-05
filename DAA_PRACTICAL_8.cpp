#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        if (u >= V || v >= V || u < 0 || v < 0)
        {
            cout << "Invalid Edge (" << u << "," << v << ")\n";
            return;
        }

        adj[u].push_back(v);
        adj[v].push_back(u);      // Remove for Directed Graph
    }

    void displayGraph()
    {
        cout << "\nAdjacency List\n";
        cout << "-------------------------\n";

        for (int i = 0; i < V; i++)
        {
            cout << i << " -> ";

            for (int neighbor : adj[i])
                cout << neighbor << " ";

            cout << endl;
        }
    }

    void DFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adj[v])
        {
            if (!visited[neighbor])
                DFSUtil(neighbor, visited);
        }
    }

    void DFS(int start)
    {
        vector<bool> visited(V, false);
        DFSUtil(start, visited);
    }

    void BFS(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for (int neighbor : adj[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

int main()
{
    int V, E;

    cout << "=====================================\n";
    cout << "      GRAPH DFS & BFS ANALYSIS\n";
    cout << "=====================================\n";

    cout << "Enter Number of Vertices : ";
    cin >> V;

    Graph g(V);

    cout << "Enter Number of Edges : ";
    cin >> E;

    cout << "\nEnter Edges (u v)\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.displayGraph();

    int start;

    cout << "\nEnter Starting Vertex : ";
    cin >> start;

    if (start < 0 || start >= V)
    {
        cout << "Invalid Starting Vertex!\n";
        return 0;
    }

    //---------------- DFS ----------------//

    auto startDFS = high_resolution_clock::now();

    cout << "\nDFS Traversal : ";
    g.DFS(start);

    auto endDFS = high_resolution_clock::now();

    //---------------- BFS ----------------//

    auto startBFS = high_resolution_clock::now();

    cout << "\nBFS Traversal : ";
    g.BFS(start);

    auto endBFS = high_resolution_clock::now();

    //---------------- Time ----------------//

    auto dfsNano = duration_cast<nanoseconds>(endDFS - startDFS);
    auto dfsMicro = duration_cast<microseconds>(endDFS - startDFS);
    auto dfsMilli = duration_cast<milliseconds>(endDFS - startDFS);

    auto bfsNano = duration_cast<nanoseconds>(endBFS - startBFS);
    auto bfsMicro = duration_cast<microseconds>(endBFS - startBFS);
    auto bfsMilli = duration_cast<milliseconds>(endBFS - startBFS);

    cout << "\n\n=====================================";
    cout << "\n         EXECUTION TIME";
    cout << "\n=====================================\n";

    cout << "\nDFS";
    cout << "\nNanoseconds  : " << dfsNano.count() << " ns";
    cout << "\nMicroseconds : " << dfsMicro.count() << " us";
    cout << "\nMilliseconds : " << dfsMilli.count() << " ms";

    cout << "\n\nBFS";
    cout << "\nNanoseconds  : " << bfsNano.count() << " ns";
    cout << "\nMicroseconds : " << bfsMicro.count() << " us";
    cout << "\nMilliseconds : " << bfsMilli.count() << " ms";

    cout << "\n\n=====================================\n";

    return 0;
}
