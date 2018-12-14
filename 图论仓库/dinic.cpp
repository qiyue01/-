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
const int MAXN = 1010;
const int INF = 0x7fffffff;
#define For(i,j) for(int i=0;i<j;++i)
struct Edge
{
	int from, to, cap, flow;
};
const int maxn = 1000;
struct Dinic
{
	int s, t, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool vis[maxn];
	int d[maxn];
	int cur[maxn];
	void init(int n)
	{
		for (int i = 0; i <= n; i++) {
			G[i].clear();
		}
		edges.clear();
	}
	void addedge(int from, int to, int cap)
	{
		edges.push_back(Edge{ from, to, cap, 0 });
		edges.push_back(Edge{ to, from, 0, 0 });
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}
	bool bfs() {
		memset(vis, 0, sizeof vis);
		queue<int>Q;
		Q.push(s);
		d[s] = 0;
		vis[s] = 1;
		while (!Q.empty())
		{
			int u = Q.front(); Q.pop();
			for (int i = 0; i < G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				if (!vis[e.to] && e.cap > e.flow) {
					vis[e.to] = 1;
					d[e.to] = d[u] + 1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}
	int DFS(int x, int a)
	{
		if (x == t || a == 0) return a;
		int flow = 0, f;
		for (int& i = cur[x]; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
				e.flow += f;
				edges[G[x][i] ^ 1].flow -= f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		return flow;
	}
	int maxflow(int s, int t) {
		this->s = s; this->t = t;
		int flow = 0;
		while (bfs()) {
			memset(cur, 0, sizeof cur);
			flow += DFS(s, 10000000);
		}
		return flow;
	}
}dinic;
class Floyd
{
public:
	int matrix[200][200];
	int node_sum;
	Floyd(int p) :node_sum(p)
	{
		memset(matrix, 0, sizeof(matrix));
	};
	void init()
	{
		for (int k = 1; k <= node_sum; ++k)
			for (int i = 1; i <= node_sum; ++i)
			{
				if (k == i)
					matrix[k][i] = 0;
				else
					matrix[k][i] = 100000;
			}
	}
	void add_edge(int u, int v, int w)
	{
		matrix[u][v] = w;
	}
	void floyd()//ÆÕÍ¨floyd
	{
		for (int k = 1; k <= node_sum; ++k)
			for (int i = 1; i <= node_sum; ++i)
				for (int j = 1; j <= node_sum; ++j)
					matrix[i][j] = min(matrix[i][j], matrix[i][k]+ matrix[k][j]);
	}
	void floyd2() //floyd´«µÝ±Õ°ü
	{
		for (int k = 1; k <= node_sum; ++k)
			for (int i = 1; i <= node_sum; ++i)
				for (int j = 1; j <= node_sum; ++j)
					matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
	}
};
int ans = 0;
int judge1(int L, int R, vector<pair<int, int>> &par, int n)
{
	if (R >= L)
	{
	}
	else
		return L;
}
/*
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, k, f, p1, p2;
	int O = 0;
	while (cin >> n >> m >> k)
	{
	}
	return 0;
}
*/
