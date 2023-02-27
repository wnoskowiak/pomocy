#include <iostream>
#include <vector>
#define MAX 500000
std::vector<int> height;
std::vector<int> level;
using namespace std;
int n;
vector<vector<int>> g;
vector<bool> visited;
vector<vector<int>> nodeQueries;
vector<vector<int>> queries;
vector<int> results;
struct node {
		int depth;
		int val;
};
void unVisitAll() {
	fill_n(visited.begin(), visited.size(), false);
}
void addNode(int parentNode, int childNode) {
	g[parentNode].push_back(childNode);
	g[childNode].push_back(parentNode);
}
void ansQuery(vector<int>& p, int t) {
	if(visited[t]) return;
	visited[t]=true;
	vector<int> q=nodeQueries[t];
	p.push_back(t);
	for(int i=0; i<q.size(); i++)
		if(q[i]<p.size()) {
			unsigned last=p.size()-1-q[i];
			results[queries[t][i]]=p[last];
		}
	for(int x : g[t])
		ansQuery(p, x);
	p.pop_back();
}
void addQuery(int a, int k, int i) {
	nodeQueries[a].push_back(k);
	queries[a].push_back(i);
}
void initTree() {
	g.resize(n+1);
	visited.resize(n+1);
	unVisitAll();
}
void initQueries(int m) {
	nodeQueries.resize(n+1);
	queries.resize(n+1);
	results.resize(m);
	fill_n(results.begin(), m, -1);
}
node dfs(int t, int d) {
	if(visited[t]) return {-1, -1};
	visited[t]=true;
	node k{d, t};
	vector<int>& children=g[t];
	for(int x : children) {
		node tmp=dfs(x, d+1);
		if(tmp.depth>k.depth)
			k=tmp;
	}
	return k;
}
void process() {
	unVisitAll();
	const node leftDepth=dfs(1, 0);
	unVisitAll();
	const node rightDepth=dfs(leftDepth.val, 0);
	unVisitAll();
	vector<int> p;
	ansQuery(p, leftDepth.val);
	unVisitAll();
	ansQuery(p, rightDepth.val);
}
int saveHeight(int t) {
	if(visited[t]) return height[t];
	visited[t]=true;
	if(g[t].empty())
		height[t]=1;
	else {
		height[t]=0;
		for(auto x : g[t])
			height[t]=std::max(height[t], saveHeight(x));
		height[t]++;
	}
	return height[t];
}
void saveDistance(int t, int d) {
	if(visited[t]) return;
	visited[t]=true;
	level[t]=d;
	if(!g[t].empty())
		for(auto x : g[t]) saveDistance(x,d+1);
}
void saveHeightAndDistance() {
	unVisitAll();
	saveHeight(1);
	unVisitAll();
	saveDistance(1,0);
}
int main() {
	int m;
	scanf("%d", &n);
	initTree();
	initQueries(MAX);
	for(int i=1; i<=n; i++) {
		int left, right;
		scanf("%d %d", &left, &right);
		if(left!=-1) addNode(i, left);
		if(right!=-1) addNode(i, right);
	}
	height.resize(n+1);
	level.resize(n+1);
	saveHeightAndDistance();
	scanf("%d", &m);
	for(int i=0; i<m; i++) {
		int left, right;
		scanf("%d %d", &left, &right);
		addQuery(left, right, i);
	}
	process();
	for(int i=0; i<m; i++)
		printf("%d\n", results[i]);
	return 0;
}