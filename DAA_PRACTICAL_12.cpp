#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 99999

int n;
int cost[10][10];
int dp[1024][10];

// Function to find minimum cost
int tsp(int mask, int pos)
{
    // If all cities are visited
    if (mask == (1 << n) - 1)
    {
        return cost[pos][0];
    }

    // If already calculated
    if (dp[mask][pos] != -1)
    {
        return dp[mask][pos];
    }

    int answer = INF;

    // Try visiting every unvisited city
    for (int city = 0; city < n; city++)
    {
        if ((mask & (1 << city)) == 0)
        {
            if (cost[pos][city] != INF)
            {
                int newCost = cost[pos][city]
                            + tsp(mask | (1 << city), city);

                answer = min(answer, newCost);
            }
        }
    }

    dp[mask][pos] = answer;

    return answer;
}

// Function to display the cost matrix
void displayMatrix()
{
    cout << "\nCost Matrix:\n\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (cost[i][j] == INF)
                cout << "INF\t";
            else
                cout << cost[i][j] << "\t";
        }

        cout << endl;
    }
}

int main()
{
    cout << "========================================\n";
    cout << "      TRAVELLING SALESMAN PROBLEM\n";
    cout << "========================================\n";

    cout << "\nEnter number of cities: ";
    cin >> n;

    cout << "\nEnter the cost matrix:\n";
    cout << "Enter 99999 if there is no direct path.\n\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    displayMatrix();

    // Initialize DP table
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int city = 0; city < n; city++)
        {
            dp[mask][city] = -1;
        }
    }

    // Start from city 0
    int minimumCost = tsp(1, 0);

    cout << "\nMinimum Tour Cost = "
         << minimumCost << endl;

    return 0;
}
