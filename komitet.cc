#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

#define MAX 1000000007

uint64_t modulo (uint64_t a){
    return (a + MAX) % MAX;
}

uint64_t caterpillar(uint64_t dp[],
                     uint64_t pc,
                     uint64_t kc)
{
    if (pc > kc)
    {
        return 0;
    }
    static uint64_t p = 0, k = 0, sum = 0;
    uint64_t idx = k;
    while (idx < kc)
    {
        sum += dp[idx];
        // sum = modulo(sum);
        idx++;
    }
    idx = p;
    while (idx < pc)
    {
        sum -= dp[idx];
        // sum = modulo(sum);
        idx++;
    }
    p = pc;
    k = kc;
    sum = modulo(sum);
    return sum;
}

uint64_t cutoff(std::vector<uint64_t> nums, uint64_t neew, uint64_t l)
{
    // potencjalny seq fault
    static uint64_t current = 0;
    if ((int)nums[neew] - (int)l < 0)
    {
        return current;
    }
    while (nums[current] <= nums[neew] - l)
    {
        current++;
    }
    return current;
}

uint64_t horizon(uint64_t vis[], uint64_t neew)
{
    // potencjalny seq fault
    static uint64_t current = 0;
    while (vis[current] < neew)
    {
        current++;
    }
    return current;
}

uint64_t horizon2(uint64_t vis[], uint64_t neew)
{
    // potencjalny seq fault
    static uint64_t current = 0;
    while (vis[current] < neew)
    {
        current++;
    }
    return current;
}

// void printvec(uint64_t r[], uint64_t n)
// {
//     for (uint64_t i = 0; i < n; i++)
//     {
//         std::cout << r[i] << " ";
//     }
//     std::cout << std::endl;
// }

// void printvec2(std::vector<uint64_t> r)
// {
//     for (uint64_t i = 0; i < r.size(); i++)
//     {
//         std::cout << r[i] << " ";
//     }
//     std::cout << std::endl;
// }

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    uint64_t n, k, l;
    std::cin >> n;
    std::cin >> k;
    std::cin >> l;
    std::vector<uint64_t> nums(n);
    uint64_t whatRep[n];
    for (uint64_t i = 0; i < n; i++)
    {
        std::cin >> nums[i];
    }
    std::sort(nums.begin(), nums.end());
    uint64_t a = 0, vis[n];
    for (uint64_t i = 0; i < n; i++)
    {
        while ((a <= n) && (nums[a] - nums[i] <= k))
        {
            a++;
        }
        vis[i] = a - 1;
    }
    bool temp = false;

    uint64_t index = 0;

    whatRep[index] = 0;
    index++;

    uint64_t c = 0;
    c = vis[c] + 1;

    whatRep[index] = c;
    index++;

    while (c < n)
    {
        c = vis[c - 1] + 1;
        if (c < n)
        {
            c = std::min(n, vis[c] + 1);
            whatRep[index] = c;
            index++;
        }
    }
    if (whatRep[index - 1] != n)
    {
        whatRep[index] = n;
        index++;
    }
    // printvec2(whatRep);
    // std::cout << nums[whatRep[whatRep.size() - 2] - 1] << std::endl;
    // std::cout << vis[whatRep[whatRep.size() - 2] - 1] << std::endl;
    if (index == 2)
    {
        std::cout << 1 << " " << n << std::endl;
        return 0;
    }
    // if (vis[whatRep[whatRep.size() - 2] - 1] == n - 1)
    // {
    //     whatRep.pop_back();
    // }
    // std::cout << "visibility\n";
    // printvec(vis, n);
    // std::cout<<"slices\n";
    // printvec2(whatRep);

    uint64_t dp[whatRep[index - 1]];

    // printvec(whatRep, n);

    for (uint64_t i = 0; i < whatRep[1]; i++)
    {
        dp[i] = 1;
    }
    for (uint64_t i = 1; i < index - 1; i++)
    {
        for (uint64_t j = whatRep[i]; j < whatRep[i + 1]; j++)
        {

            // std::cout << "current " << nums[j] << std::endl;
            // std::cout << "cutoff " << std::min(cutoff(nums, j, l), whatRep[i]) << std::endl;
            // std::cout << "hor1 " << horizon(vis, j) << std::endl;
            // std::cout << "hor2 " << horizon2(vis, horizon(vis, j) - 1) << std::endl;
            // std::cout << "max hor2 " << std::max(horizon2(vis, horizon(vis, j) - 1), whatRep[i - 1]) << std::endl;

            dp[j] = modulo(caterpillar(
                        dp,
                        std::max(horizon2(
                                     vis,
                                     horizon(vis, j) - 1),
                                 whatRep[i - 1]),
                        std::min(cutoff(
                                     nums,
                                     j,
                                     l),
                                 whatRep[i])));
            // std::cout << "---------" << std::endl;
        }
    }
    // printvec(dp, n);
    uint64_t finsum = 0;
    for (uint64_t j = whatRep[index - 2] - 1; j >= 0; j--)
    {
        if (vis[j] != n - 1)
        {
            break;
        }
        finsum += dp[j];
        finsum = modulo(finsum);
    }
    if (!finsum)
    {
        std::cout << index - 2 << " " << finsum << std::endl;
        return 0;
    }
    else
    {
        for (uint64_t j = whatRep[index - 1] - 1; j >= 0; j--)
        {
            if (vis[j] != n - 1)
            {
                break;
            }
            finsum += dp[j];
            finsum %= MAX;
        }
        std::cout << index - 1 << " " << finsum << std::endl;
        return 0;
    }
}