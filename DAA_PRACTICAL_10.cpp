#include <iostream>
#include <algorithm>
using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
};

int findParent(int parent[], int vertex)
{
    if (parent[vertex] == vertex)
        return vertex;

    return findParent(parent, parent[vertex]);
}

void unionSet(int parent[], int rank[], int u, int v)
{
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    if (rootU != rootV)
    {
        if (rank[rootU] < rank[rootV])
        {
            parent[rootU] = rootV;
        }
        else if (rank[rootU] > rank[rootV])
        {
            parent[rootV] = rootU;
        }
        else
        {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

bool compareEdges(Edge a, Edge b)
{
    return a.weight < b.weight;
}

int main()
{
    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    Edge edge[100];

    cout << "\nEnter source, destination and weight of each edge:\n";

    for (int i = 0; i < edges; i++)
    {
        cin >> edge[i].source
            >> edge[i].destination
            >> edge[i].weight;
    }

    // Sort edges according to weight
    sort(edge, edge + edges, compareEdges);

    int parent[100];
    int rank[100];

    // Initialize parent and rank
    for (int i = 0; i < vertices; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalCost = 0;
    int edgeCount = 0;

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\tWeight\n";

    // Select edges for MST
    for (int i = 0; i < edges && edgeCount < vertices - 1; i++)
    {
        int u = edge[i].source;
        int v = edge[i].destination;

        int rootU = findParent(parent, u);
        int rootV = findParent(parent, v);

        // Add edge only if it does not form a cycle
        if (rootU != rootV)
        {
            cout << u << " - " << v
                 << "\t" << edge[i].weight << endl;

            totalCost += edge[i].weight;
            edgeCount++;

            unionSet(parent, rank, u, v);
        }
    }

    cout << "\nMinimum Cost = " << totalCost << endl;

    return 0;
}
