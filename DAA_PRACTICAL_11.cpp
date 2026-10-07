#include <iostream>
#include <iomanip>
using namespace std;

#define INF 99999

// Function to display the matrix
void displayMatrix(int dist[10][10], int n)
{
    cout << "\nShortest Distance Matrix:\n\n";

    cout << "     ";
    for (int i = 0; i < n; i++)
    {
        cout << setw(6) << i;
    }
    cout << endl;

    cout << "----------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        cout << i << " | ";

        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
            {
                cout << setw(6) << "INF";
            }
            else
            {
                cout << setw(6) << dist[i][j];
            }
        }

        cout << endl;
    }
}

// Floyd-Warshall Algorithm
void floydWarshall(int graph[10][10], int n)
{
    int dist[10][10];

    // Copy graph into distance matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = graph[i][j];
        }
    }

    // Consider every vertex as an intermediate vertex
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // Check if a shorter path exists through k
                if (dist[i][k] != INF &&
                    dist[k][j] != INF)
                {
                    if (dist[i][j] >
                        dist[i][k] + dist[k][j])
                    {
                        dist[i][j] =
                            dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    displayMatrix(dist, n);

    // Check for negative weight cycle
    for (int i = 0; i < n; i++)
    {
        if (dist[i][i] < 0)
        {
            cout << "\nNegative weight cycle detected.\n";
            return;
        }
    }

    cout << "\nNo negative weight cycle detected.\n";
}

int main()
{
    int n;
    int graph[10][10];

    cout << "========================================\n";
    cout << "       FLOYD-WARSHALL ALGORITHM\n";
    cout << "========================================\n";

    cout << "\nEnter number of vertices: ";
    cin >> n;

    cout << "\nEnter the adjacency matrix:\n";
    cout << "Enter " << INF
         << " if there is no direct edge.\n\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    cout << "\nOriginal Adjacency Matrix:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
            {
                cout << "INF\t";
            }
            else
            {
                cout << graph[i][j] << "\t";
            }
        }

        cout << endl;
    }

    floydWarshall(graph, n);

    return 0;
}
