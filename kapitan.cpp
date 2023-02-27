#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <map>
#include <bits/stdc++.h>
#include <limits.h>
#include <tuple>
#include <queue>

typedef struct GraphNode{
    std::pair<int,int> coordinate;
    bool is_visited = false;
    int distance_from_start = INT_MIN;
    std::set<int> neighbours;
}graph_node;

typedef struct HeapNode{
    graph_node* graph_vertice;
    uint64_t weight;
}node_t;



bool sortbysec (const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b){
    return (std::get<1>(a) < std::get<1>(b));
}

int two_point_distance (std::pair<int,int> first, std::pair<int,int> second){
    int answer = std::min(std::abs(first.first - second.first), std::abs(first.second - second.second));
    /*std::cout << answer;*/
    return answer;
}

void dijkstra (std::priority_queue<std::pair<int , graph_node*>, std::deque<std::pair<int , graph_node*>>>& our_queue, std::vector<graph_node>& graph, int position_end){
    std::pair<int, graph_node* > take_top;
    std::pair<int, int> neighbour_coordinate;
    int my_neighbour_dist;

    while (!our_queue.empty()){
        take_top = our_queue.top();
        our_queue.pop();

        take_top.second->is_visited = true;

        if (take_top.second == &graph[position_end]) return;

        for (auto child : take_top.second->neighbours){
            neighbour_coordinate = graph[child].coordinate;
            my_neighbour_dist = -two_point_distance(take_top.second->coordinate, neighbour_coordinate) + take_top.first;

            if (my_neighbour_dist > graph[child].distance_from_start){
                graph[child].distance_from_start = my_neighbour_dist;
            }

            if (!graph[child].is_visited){
                our_queue.push(std::make_pair(my_neighbour_dist, &graph[child]));
            }
        }
    }
}

int final_function (std::vector<graph_node>& graph, int position_start, int position_end){
    int answer;

    std::priority_queue<std::pair<int , graph_node*>, std::deque<std::pair<int , graph_node*>>> our_queue;

    our_queue.push(std::make_pair(0, &graph[position_start]));

    dijkstra(our_queue, graph, position_end);

    answer = graph[position_end].distance_from_start;

    return -answer;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();

    int n;

    std::cin >> n;

    std::vector<std::pair<int,int>> input(n);
    std::vector<std::tuple<int,int,int>> islands(n);
    std::vector<std::tuple<int, int, int>> island_reverse(n);

    for (int i = 0; i < n; i++){
        std::cin >> input[i].first;
        std::cin >> input[i].second;
    }

    std::pair<int, int> start = std::make_pair(input[0].first, input[0].second);
    std::pair<int,int> end = std::make_pair(input[n - 1].first, input[n - 1].second);

    sort(input.begin(), input.end());

    //posortowany po y
    for (int i = 0; i < n; i++){
        island_reverse[i] = std::make_tuple(input[i].first, input[i].second, i);
    }

    sort(island_reverse.begin(), island_reverse.end(), sortbysec);

    //posortowany po x
    int position;
    for (int i = 0; i < n; i++){
        position = std::get<2>(island_reverse[i]);
        islands[position] = std::make_tuple(std::get<0>(island_reverse[i]), std::get<1>(island_reverse[i]), i);
    }

    std::vector<graph_node> graph(n);
    int helper, helper2;
    int position_of_start;
    int position_of_end;

    for (int i = 0; i < n; i++){
        graph[i].coordinate.first = std::get<0>(island_reverse[i]);
        graph[i].coordinate.second = std::get<1>(island_reverse[i]);

        //remember where is start
        if (std::get<0>(island_reverse[i]) == start.first && std::get<1>(island_reverse[i]) == start.second){
            position_of_start = i;
            graph[i].distance_from_start = 0;
        }
        //remember where is end
        if (std::get<0>(island_reverse[i]) == end.first && std::get<1>(island_reverse[i]) == end.second){
            position_of_end = i;
        }

        if (i == 0) {
            // work with y-neighbour
            graph[i].neighbours.insert(i + 1);
        }
        else if (i == n - 1) {
            graph[i].neighbours.insert(i - 1);
        }
        else {
            graph[i].neighbours.insert(i - 1);
            graph[i].neighbours.insert(i + 1);
        }

        // work with x-neighbour
        helper = std::get<2>(island_reverse[i]);

        if (helper == 0) {
            helper2 = std::get<2>(islands[1]);
            graph[i].neighbours.insert(helper2);
        }
        else if (helper == n - 1) {
            helper2 = std::get<2>(islands[n - 2]);
            graph[i].neighbours.insert(helper2);
        }
        else {
            //helper2 = std::get<2>(islands[helper]);
            graph[i].neighbours.insert(std::get<2>(islands[helper - 1]));
            graph[i].neighbours.insert(std::get<2>(islands[helper + 1]));
        }
    }

    std::cout << final_function (graph, position_of_start, position_of_end);

    return 0;
}
