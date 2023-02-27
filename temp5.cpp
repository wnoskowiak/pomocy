#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
struct Island
{
    size_t x;
    size_t y;
    int id;
};
struct Vertex
{
    Island island;
    std::vector<Island> neighbours;
};
size_t cityMetric(struct Island &uno, struct Island &dos)
{
    return std::min(std::max(dos.x, uno.x) - std::min(dos.x, uno.x),
                    std::max(dos.y, uno.y) - std::min(dos.y, uno.y));
}


struct C
{
    bool operator()(const std::pair<Island, size_t> &island1, const std::pair<Island, size_t> &island2) const
    {
        return island1.second > island2.second;
    }
};
bool cX(const Island &i1, const Island &i2)
{
    return i1.x < i2.x || (i1.x == i2.x && i1.y < i2.y);
}
bool cY(const Island &lhs, const Island &rhs)
{
    return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}
int main()
{

    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    size_t ans = -1;
    int n;
    size_t x, y;
    std::vector<Island> islands;
    std::vector<Vertex> graph;
    std::cin >> n;
    struct Island start
    {
    };
    for (int i = 0; i < n; i++)
    {
        std::cin >> x;
        std::cin >> y;
        const struct Island island = {x, y, i};
        if (i == 0)
            start = island;
        islands.push_back(island);
        const struct Vertex vertex = {island, std::vector<Island>()};
        graph.push_back(vertex);
    }
    std::sort(islands.begin(), islands.end(), cX);
    for (int i = 0; i < n - 1; i++)
    {
        graph[islands[i].id].neighbours.push_back(islands[i + 1]);
        graph[islands[i + 1].id].neighbours.push_back(islands[i]);
    }
    std::sort(islands.begin(), islands.end(), cY);
    for (int i = 0; i < n - 1; i++)
    {
        graph[islands[i].id].neighbours.push_back(islands[i + 1]);
        graph[islands[i + 1].id].neighbours.push_back(islands[i]);
    }
    std::priority_queue<std::pair<Island, size_t>, std::vector<std::pair<Island, size_t>>, C> q;
    std::vector<size_t> distance(n, ULONG_MAX);
    std::vector<bool> visited(n, false);
    distance[0] = 0;
    q.push(std::pair(start, distance[0]));
    while (!q.empty())
    {
        Island min_island = q.top().first;
        size_t island_dist = q.top().second;
        q.pop();
        if (!visited[min_island.id])
        {
            if (min_island.id == n - 1)
            {
                ans = island_dist;
                break;
            }
            for (auto &v : graph[min_island.id].neighbours)
                if (!visited[v.id])
                    q.push(std::pair(v, distance[v.id] = std::min(distance[v.id], island_dist + cityMetric(min_island, v))));
        }
        visited[min_island.id] = true;
    }
    printf("%lu\n", ans);
    return 0;
}