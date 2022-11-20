#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>

int main()
{
    std::cin.sync_with_stdio(false);
    int n, m, temp;
    std::cin >> n;
    std::cin >> m;
    unsigned long long player_codes[n];
    for(int i = 0; i<n; i++) {
        player_codes[i] = 0;
    }
    for(int i = 0; i<m; i++) {
        for(int j = 0; j < (n/2); j++) {
            std::cin >> temp;
            player_codes[temp-1] += std::pow(2,i);
        }
        for(int j = 0; j < (n/2); j++) {
            std::cin >> temp;
        }
    }
    std::unordered_set <unsigned long long> ust;
    for(int i = 0; i<n; i++) {
        ust.insert(player_codes[i]);
    }
    if (ust.size() == n) {
        std::cout << "TAK\n";
    }
    else {
        std::cout << "NIE\n";
    }
}