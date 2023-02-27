#include <iostream>
#include <vector>
#include <queue>

typedef struct Node
{
    int myIndex;
    int workers;
    std::vector<int> WhoDependsOnMe;
    int howManyDoIDependOn;
} job;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, k;

    std::cin >> n;
    std::cin >> m;
    std::cin >> k;

    // std::cout << m << "\n";

    job jobs[n];

    typedef struct ffsfrsdrff
    {
        int y;
        int workers;
        bool operator<(const ffsfrsdrff &t) const
        {
            return (this->workers < t.workers);
        }

        ffsfrsdrff(int y, int workers)
        {
            this->y = y;
            this->workers = workers;
        }

    } jezu;

    class myComparator
    {
    public:
        int operator()(const jezu &p1, const jezu &p2)
        {
            return p1.workers >= p2.workers;
        }
    };

    for (int i = 0; i < n; i++)
    {
        std::cin >> jobs[i].workers;
        jobs[i].myIndex = i;
        jobs[i].howManyDoIDependOn = 0;
    }

    int temp1, temp2;

    for (int i = 0; i < m; i++)
    {
        std::cin >> temp1;
        std::cin >> temp2;
        jobs[temp1 - 1].howManyDoIDependOn++;
        jobs[temp2 - 1].WhoDependsOnMe.push_back(temp1 - 1);
    }

    std::priority_queue<jezu, std::vector<jezu>, myComparator> queue;

    for (int i = 0; i < n; i++)
    {
        if (jobs[i].howManyDoIDependOn == 0)
        {
            auto d = jezu(i, jobs[i].workers);
            queue.emplace(d);
        }
    }

    int result = 0;
    int howManyWePoppin = 0;

    while (true)
    {
        if (howManyWePoppin == k)
        {
            break;
        }
        if (queue.empty())
        {
            break;
        }
        auto embe = queue.top();
        auto &dupa = jobs[embe.y];
        result = std::max(result, dupa.workers);

        auto dupa2 = dupa.WhoDependsOnMe;
        for (auto i = 0; i < dupa2.size(); i++)
        {
            jobs[dupa2[i]].howManyDoIDependOn--;
            if (jobs[dupa2[i]].howManyDoIDependOn == 0)
            {
                auto d = jezu(dupa2[i], jobs[dupa2[i]].workers);
                queue.emplace(d);
            }
        }

        queue.pop();
        howManyWePoppin++;
    }

    std::cout << result << "\n";
}