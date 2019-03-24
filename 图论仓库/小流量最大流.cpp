#include "pch.h"
#include <iostream>
#include<string>
#include<vector>
#include<regex>
#include<algorithm>
#include<random>
#include<map>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory>
#include<functional>
using namespace std;
const int MAXN = 20010;
const int INF = 0x7fffffff;
#define For(i,j) for(int i=0;i<j;++i)
int pre[MAXN];
bool vis[MAXN];
int Max[MAXN];
struct Node {
	int v, f, index;
	Node(int v, int f, int index) : v(v), f(f), index(index) {}
};

std::vector<Node> edge[MAXN];

inline void addEdge(int u, int v, int f) {
	edge[u].push_back(Node(v, f, edge[v].size()));
	edge[v].push_back(Node(u, 0, edge[u].size() - 1));
}
bool bfs(int s, int t)
{
	queue<int> que;
	memset(vis, 0, sizeof(vis));
	Max[s] = 100000;
	que.push(s);
	vis[s] = true;
	int k;
	while (!que.empty())
	{
		k = que.front();
		que.pop();
		for (auto &p : edge[k])
		{
			if (vis[p.v] == false && p.f > 0)
			{

				vis[p.v] = true;
				pre[p.v] = k;
				Max[p.v] = min(p.f, Max[k]);
				que.push(p.v);
			}
		}
	}
	if (pre[t] != -1)
	{
		int cur = t, k = Max[t];
		while (cur != s)
		{
			for (auto &p : edge[cur])
				if (p.v == pre[cur])
				{
					p.f += k;
					edge[p.v][p.index].f -= k;
				}
			cur = pre[cur];
		}
		return true;
	}
	else
		return false;
}
int all_flow;
int max_flow(int s, int t)
{
	vis[t] = false;
	int flow = 0;
	memset(pre, -1, sizeof(pre));
	while (bfs(s, t))
	{
		memset(pre, -1, sizeof(pre));
		all_flow += Max[t];
	}
	return all_flow;
}
void init()
{
	for (int i = 0; i < MAXN; ++i)
		edge[i].clear();
}
const int inf = 0x6fffffff;