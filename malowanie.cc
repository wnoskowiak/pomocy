#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <set>
#include <algorithm>

struct fragType
{
    int begin, end;
    bool color;
    bool operator<(const fragType &a) const
    {
        return this->begin < a.begin;
    }
};

auto &road()
{
    static std::set<fragType> global_map;
    return global_map;
}

auto &how_many_white()
{
    static int km = 0;
    return km;
}

void corr(int del)
{
    how_many_white() += del;
}

void addFragment(int begin, int end, bool color)
{
    auto &street = road();
    if (street.size() == 0)
    {
        street.insert({begin, end, color});
        return;
    }
    auto lower = street.upper_bound({begin, 0, false});
    auto higher = street.upper_bound({end, 0, false});
    lower--;
    higher--;
    int whites = 0;
    fragType left = *lower, right = *higher;
    if (lower != higher)
    {
        for (auto i = lower; i != higher; i++)
        {
            if ((*i).color)
            {
                whites += (*i).end - (*i).begin;
            }
        }
        street.erase(lower,higher);
        if ((*higher).color)
        {
            whites += (*higher).end - (*higher).begin;
        }
        street.erase(higher);
    }
    else
    {
        if ((*higher).color)
        {
            whites += (*higher).end - (*higher).begin;
        }
        street.erase(higher);
    }

    std::vector<fragType> a;
    if (left.begin != begin)
    {
        a.push_back({left.begin, begin, left.color});
        if (left.color == color)
        {
            a[0].end = end;
        }
        else
        {
            a.push_back({begin, end, color});
        }
    }
    else
    {
        a.push_back({begin, end, color});
    }
    if (right.color == color)
    {
        a[a.size() - 1].end = right.end;
    }
    else
    {
        a.push_back({end, right.end, right.color});
    }
    whites *= -1;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].color)
        {
            whites += a[i].end - a[i].begin;
        }
        street.insert(a[i]);
    }
    corr(whites);
}

int main()
{
    std::cin.sync_with_stdio(false);
    int n, m, a, b;
    char eeee;
    std::cin >> n;
    std::cin >> m;
    addFragment(0, n, false);
    for (int i = 0; i < m; i++)
    {
        std::cin >> a;
        std::cin >> b;
        std::cin >> eeee;
        addFragment(a-1, b, (eeee == 'B'));
        std::cout << how_many_white() << std::endl;
    }
}