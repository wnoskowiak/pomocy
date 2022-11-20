#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

#define MAX 1000000007

uint32_t caterpillar(uint32_t dp[],
                   uint32_t pc,
                   uint32_t kc)
{
    static uint32_t p = 0, k = 0, sum = 0;
    uint32_t idx = k;
    while (idx < kc)
    {
        sum += dp[idx];
        // sum %= MAX;
        idx++;
    }
    idx = p;
    while (idx < pc)
    {
        sum -= dp[idx];
        // sum %= MAX;
        idx++;
    }
    p = pc;
    k = kc;
    sum %= MAX;
    return sum;
}

uint32_t cutoff(std::vector<uint32_t> nums, uint32_t neew, uint32_t l)
{
    // potencjalny seq fault
    static uint32_t current = 0;
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

uint32_t horizon(uint32_t vis[], uint32_t neew)
{
    // potencjalny seq fault
    static uint32_t current = 0;
    while (vis[current] < neew)
    {
        current++;
    }
    return current;
}

uint32_t horizon2(uint32_t vis[], uint32_t neew)
{
    // potencjalny seq fault
    static uint32_t current = 0;
    while (vis[current] < neew)
    {
        current++;
    }
    return current;
}

void printvec(uint32_t r[], uint32_t n)
{
    for (uint32_t i = 0; i < n; i++)
    {
        std::cout << r[i] << " ";
    }
    std::cout << std::endl;
}

void printvec2(std::vector<uint32_t> r)
{
    for (uint32_t i = 0; i < r.size(); i++)
    {
        std::cout << r[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cin.sync_with_stdio(false);
    uint32_t n, k, l;
    std::cin >> n;
    std::cin >> k;
    std::cin >> l;
    std::vector<uint32_t> nums(n);
    for (uint32_t i = 0; i < n; i++)
    {
        std::cin >> nums[i];
    }
    std::sort(nums.begin(), nums.end());
    uint32_t a = 0, vis[n];
    for (uint32_t i = 0; i < n; i++)
    {
        while ((a <= n) && (nums[a] - nums[i] <= k))
        {
            a++;
        }
        vis[i] = a - 1;
    }
    bool temp = false;
    std::vector<uint32_t> whatRep;
    whatRep.push_back(0);
    uint32_t c = 0;
    c = vis[c] + 1;
    whatRep.push_back(c);
    while (c < n - 1)
    {
        c = vis[c - 1] + 1;
        c = vis[c] + 1;
        whatRep.push_back(c);
    }
    if(whatRep[whatRep.size() - 1] != n) {
        whatRep.push_back(n);
    }
    // printvec2(whatRep);
    // std::cout << nums[whatRep[whatRep.size() - 2] - 1] << std::endl;
    // std::cout << vis[whatRep[whatRep.size() - 2] - 1] << std::endl;
    if (whatRep.size() == 2) {
        std::cout << 1 << " " << n << std::endl;
        return 0;
    }
    if (vis[whatRep[whatRep.size() - 2] - 1] == n - 1)
    {
        whatRep.pop_back();
    }
    // printvec(vis, n);
    // printvec2(whatRep);

    uint32_t dp[whatRep[whatRep.size() - 1]];

    for (uint32_t i = 0; i < whatRep[1]; i++)
    {
        dp[i] = 1;
    }
    for (uint32_t i = 1; i < whatRep.size() - 1; i++)
    {
        for (uint32_t j = whatRep[i]; j < whatRep[i + 1]; j++)
        {

            // std::cout << "current " << nums[j] << std::endl;
            // std::cout << "cutoff " << std::min(cutoff(nums, j, l), whatRep[i]) << std::endl;
            // std::cout << "hor1 " << horizon(vis, j) << std::endl;
            // std::cout << "hor2 " << horizon2(vis, horizon(vis, j) - 1) << std::endl;
            // std::cout << "max hor2 " << std::max(horizon2(vis, horizon(vis, j) - 1), whatRep[i - 1]) << std::endl;

            dp[j] = caterpillar(
                dp,
                std::max(horizon2(
                             vis,
                             horizon(vis, j) - 1),
                         whatRep[i - 1]),
                std::min(cutoff(
                             nums,
                             j,
                             l),
                         whatRep[i]));
            //  std::cout << "---------" << std::endl;       
        }
    }
    // printvec(dp, n);
    uint32_t finsum = 0;
    for (uint32_t j = whatRep[whatRep.size() - 1] - 1; j >= 0; j--)
    {
        if (vis[j] != n - 1)
        {
            break;
        }
        finsum += dp[j];
        finsum %= MAX;
    }
    std::cout << whatRep.size() - 1 << " " << finsum << std::endl;
}