#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void printOptimalParenthesis(vector<vector<int>>& split, int i, int j)
{
    if (i == j)
    {
        cout << "A" << i;
        return;
    }

    cout << "(";

    printOptimalParenthesis(split, i, split[i][j]);
    printOptimalParenthesis(split, split[i][j] + 1, j);

    cout << ")";
}

int matrixChainMultiplication(vector<int>& p, int n)
{
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> split(n + 1, vector<int>(n + 1, 0));

    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    cout << "\nMinimum number of scalar multiplications: "
         << m[1][n] << endl;

    cout << "Optimal Parenthesization: ";
    printOptimalParenthesis(split, 1, n);
    cout << endl;

    return m[1][n];
}

int main()
{
    int n;

    cout << "Enter number of matrices: ";
    cin >> n;

    vector<int> p(n + 1);

    cout << "Enter dimensions:\n";

    for (int i = 0; i <= n; i++)
    {
        cin >> p[i];
    }

    matrixChainMultiplication(p, n);

    return 0;
}
