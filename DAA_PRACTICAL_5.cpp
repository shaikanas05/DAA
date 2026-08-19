#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int capacity, vector<int>& weight, vector<int>& value, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= capacity; w++)
        {
            if (weight[i - 1] <= w)
            {
                dp[i][w] = max(
                    value[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main()
{
    int n, capacity;

    cout << "=====================================\n";
    cout << "        0/1 KNAPSACK PROBLEM\n";
    cout << "=====================================\n";

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n);
    vector<int> value(n);

    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++)
    {
        cin >> weight[i];
    }

    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++)
    {
        cin >> value[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    int result = knapsack(capacity, weight, value, n);

    cout << "\nMaximum profit: " << result << endl;

    cout << "=====================================\n";

    return 0;
}
