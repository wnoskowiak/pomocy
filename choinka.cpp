#include <iostream>
#include <vector>
#include <map>

typedef struct Node
{
    int father;
    int position;
    int color;
    std::vector<int> children;
    bool almost_same = true;
    bool has_one_color = true;
} node_t;

typedef std::map<int, int> map_t;

int numOfNodes;
map_t m;

void printMap()
{
    std::cout << "\n";
    for (auto i = m.begin(); i != m.end(); i++)
    {
        std::cout << i->first << " " << i->second << "\n";
    }
    std::cout << "\n";
}

void plain_insert(int position, int color, int oldColor)
{
    m.insert_or_assign(position, color);
    if (m.find(position + 1) == m.end())
    {
        m.insert_or_assign(position + 1, oldColor);
    }
}

void insert_color(int position, int color)
{

    map_t::iterator upper = m.upper_bound(position);
    map_t::iterator me = upper;
    me--;
    map_t::iterator lower = me;
    lower--;



    int meBegin = me->first,
        meColor = me->second;

    // jeśli wstawiamy ten sam kolor to nic nie robimy
    if (meColor == color)
    {
        return;
    }
    // jeśli wstawiamy na koniec/początek to trzeba sprawdzić specjalny case
    bool checkForUppers = (upper != m.end());
    bool checkForDowners = true;


    int upperBegin = upper->first,
        upperColor = upper->second;
    
    int lowerColor = lower->second;


    if ((meBegin == position) && (upperBegin - 1 == position) && checkForUppers && checkForDowners)
    {
        if (lowerColor == color && color == upperColor)
        {
            m.erase(me);
            m.erase(upper);
            return;
        }
    }
    if ((meBegin == position) && (lowerColor == color) && checkForDowners)
    {
        m.erase(me);
        if(m.find(position + 1) == m.end()){
            m.insert_or_assign(position + 1, meColor);
        }
        return;
    }

    if ((upperBegin - 1 == position) && (color == upperColor) && checkForUppers)
    {
        m.erase(upperBegin);
        m.insert_or_assign(position, color);
        return;
    }

    plain_insert(position, color, meColor);
}

int iter = 0;

void rec_dfs(std::vector<node_t> &tree, int position, std::vector<int> &answer, std::vector<int> &exit)
{
    answer[position] = iter;
    iter++;

    for (auto child : tree[position].children)
    {
        rec_dfs(tree, child, answer, exit);
    }

    exit[position] = iter - 1;
}

std::pair<std::vector<int>, std::vector<int>> dfs(std::vector<node_t> &tree)
{
    std::vector<int> answer(tree.size());
    std::vector<int> exit(tree.size());
    rec_dfs(tree, 0, answer, exit);

    return std::make_pair(answer, exit);
}

void printing(std::vector<int> &vec)
{

    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
}

bool check_interval(int start, int stop)
{
    int main_color = -1;
    auto it = m.upper_bound(stop);
    it--;

    if (it->first <= start)
    {
        return true;
    }
    bool gottaCheckSth = (it->first == stop);

    main_color = it->second;
    int last_border = it->first;
    it--;

    if ((it->first <= start))
    {

        if(last_border-1 == start) {
            return true;
        }
        return gottaCheckSth;
    }

    if (it->first <= start && last_border - start == 1)
    {
        return true;
    }

    if (last_border - it->first > 1)
    {
        return false;
    }

    it--;
    if (it->first <= start && it->second == main_color)
    {
        return true;
    }

    return false;
}

bool check_almost_colored(std::vector<int> &res, std::vector<int> &new_index, std::vector<int> &exit, int position)
{
    int start = res[position - 1];
    int stop = exit[position - 1];
    if (stop - start <= 1)
        return true;

    return check_interval(start, stop);
}



int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();

    int n, q;
    int x;
    char c;

    std::cin >> n;
    std::cin >> q;

    numOfNodes = n;
    std::vector<node_t> tree(n);

    for (int i = 0; i < n - 1; i++)
    {
        std::cin >> x;
        tree[i + 1].father = x - 1;
        tree[x - 1].children.push_back(i + 1);
        tree[i + 1].position = tree[x - 1].children.size();
    }

    auto kropla = dfs(tree);
    std::vector<int> res = kropla.first;
    std::vector<int> exit = kropla.second;

    for (int i = 0; i < n; i++)
    {
        std::cin >> tree[i].color;
    }

    std::vector<int> new_index(n);

    for (int i = 0; i < n; i++)
    {
        new_index[res[i]] = i;
    }

    int current_color = tree[0].color;
    m[0] = current_color;

    for (int i = 0; i < n; i++)
    {
        if (tree[new_index[i]].color != current_color)
        {
            current_color = tree[new_index[i]].color;
            m[i] = current_color;
        }
    }

    int v;

    for (int i = 0; i < q; i++)
    {
        std::cin >> c;

        if (c == '?')
        {
            std::cin >> x;

            if (check_almost_colored(res, new_index, exit, x))
            {
                std::cout << "TAK" << '\n';
            }
            else
            {
                std::cout << "NIE" << '\n';
            }
        }
        else
        {
            std::cin >> v;
            std::cin >> x;
            insert_color(res[v - 1], x);
        }
    }

    return 0;
}