#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cin.sync_with_stdio(false);
    int n, m;
    std::cin >> n;
    unsigned long long sums[n + 1];
    int ev[n + 1], od[n + 1], mev[n + 1], mod[n + 1], vals[n],temp;
    sums[0] = 0;
    ev[0] = -1;
    od[0] = -1;
    bool all_evens = true, all_odd = true;
    for (int i = 1; i < n + 1; i++)
    {
        std::cin >> temp;
        vals[i - 1] = temp;
        sums[i] = temp + sums[i - 1];
        if (temp % 2 == 0)
        {
            if (all_odd)
            {
                all_odd = false;
            }
            ev[i] = temp;
            od[i] = od[i - 1];
            continue;
        }
        if (all_evens)
        {
            all_evens = false;
        }
        od[i] = temp;
        ev[i] = ev[i - 1];
    }
    mev[n] = -1;
    mod[n] = -1;
    for (int i = n - 1; i >= 0; i--)
    {
        if (vals[i] % 2 == 0)
        {
            mev[i] = vals[i];
            mod[i] = mod[i + 1];
            continue;
        }
        mev[i] = mev[i + 1];
        mod[i] = vals[i];
    }
    std::cin >> m;
    int num_of_things[m];
    for (int i = 0; i < m; i++)
    {
        std::cin >> num_of_things[i];
    }
    int min_even, min_odd, max_even = -1, max_odd = -1, diff1 = INT32_MIN, diff2 = INT32_MIN;
    long long sum = 0;
    for (int thing = 0; thing < m; thing++)
    {
        if (all_evens)
        {
            std::cout << -1 << "\n";
            continue;
        }
        if (all_odd && (num_of_things[thing] % 2 == 0))
        {
            std::cout << -1 << "\n";
            continue;
        }
        sum = sums[n] - sums[n - num_of_things[thing]];
        if (sum % 2 == 1)
        {
            std::cout << sum << "\n";
            continue;
        }
        min_even = mev[(n - num_of_things[thing])];
        min_odd = mod[(n - num_of_things[thing])];
        max_even = ev[(n - num_of_things[thing])];
        max_odd = od[(n - num_of_things[thing])];
        diff1 = INT32_MIN;
        diff2 = INT32_MIN;
        if ((max_even > -1) && (min_odd > -1))
        {
            diff1 = max_even - min_odd;
        }
        if ((max_odd > -1) && (min_even > -1))
        {
            diff2 = max_odd - min_even;
        }
        if ((diff1 == INT32_MIN) && (diff2 == INT32_MIN))
        {
            std::cout << -1 << "\n";
            continue;
        }
        std::cout << sum + std::max(diff1, diff2) << "\n";
    }
}