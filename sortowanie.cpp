#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>

int main()
{
    std::cin.sync_with_stdio(false);
    long long n;
    std::cin >> n;
    long long vals[n];
    for (long long i = 0; i < n; i++)
    {
        std::cin >> vals[i];
    }
    long long front[n][n], back[n][n];
    for (long long i = 0; i < n; i++)
    {
        back[0][i] = 0;
        front[0][i] = 1;
    }
    for (long long i = 1; i < n; i++)
    {
        for (long long j = 0; j < n - i; j++)
        {
            front[i][j] = 0;
            if (vals[j + i] >= vals[j])
            {
                front[i][j] = (front[i][j] + back[i - 1][j + i]) % 1000000000;
            }
            if (vals[j] <= vals[j + 1])
            {
                front[i][j] = (front[i][j] + front[i - 1][j + 1]) % 1000000000;
            }
        }
        for (long long j = i; j < n; j++)
        {
            back[i][j] = 0;
            if (vals[j] >= vals[j - i])
            {
                back[i][j] = (back[i][j] + front[i - 1][j - i])% 1000000000;
            }
            if (vals[j] >= vals[j - 1])
            {
                back[i][j] = (back[i][j] + back[i - 1][j - 1])% 1000000000;
            }
        }
    }
    std::cout << (front[n - 1][0] + back[n - 1][n - 1]) % 1000000000 << "\n";
}