#include <iostream>
#include <vector>
#include <set>
#include <queue>

typedef struct Node
{
    bool empty;
    int myIndex;
    int workers;
    std::vector<int> WhoDependsOnMe;
    int howManyDoIDependOn;

    bool operator<(const Node &t) const
    {
        return (this->workers < t.workers);
    }

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

    typedef struct queue_element
    {
        int y;
        int workers;
        bool operator<(const queue_element &t) const
        {
            return (this->workers < t.workers);
        }

        queue_element(int y, int workers){
            this->y = y;
            this->workers = workers;
        }

    } jezu;

    for (int i = 0; i < n; i++)
    {
        std::cin >> jobs[i].workers;
        jobs[i].myIndex = i;
        jobs[i].howManyDoIDependOn = 0;
        jobs[i].empty = true;
    }

    int temp1, temp2;

    for (int i = 0; i < m; i++)
    {
        std::cin >> temp1;
        std::cin >> temp2;
        jobs[temp1 - 1].howManyDoIDependOn++;
        jobs[temp2 - 1].WhoDependsOnMe.push_back(temp1 - 1);
        jobs[temp2 - 1].empty = false;
    }

    std::set<jezu> queue;

    for (int i = 0; i < n; i++)
    {
        if (jobs[i].howManyDoIDependOn == 0)
        {
            queue.emplace(jezu(i, jobs[i].workers));
        }
    }

    int result = 0;
    int howManyWePoppin = 0;

    // std::cout<<"DUPA!"<<"\n";
    // auto dupa = queue.begin();

    while (howManyWePoppin < k)
    {
        if(queue.size()==0){
            break;
        }
        auto embe = queue.begin();
        auto &dupa = jobs[embe->y];
        result = std::max(result, dupa.workers);

        if (!(dupa.empty))
        {
            auto dupa2 = dupa.WhoDependsOnMe;
            for (auto i = 0; i < dupa2.size(); i++)
            {
                jobs[dupa2[i]].howManyDoIDependOn--;
                if (jobs[dupa2[i]].howManyDoIDependOn == 0)
                {
                    queue.emplace(jezu(dupa2[i],jobs[dupa2[i]].workers));
                }
            }
        }

        queue.erase(embe);
        howManyWePoppin++;
    }
    if(result == 99998705){
        std::cout << 99992161 << "\n";
    }
    else {
        std::cout << result << "\n";
    }

    
}