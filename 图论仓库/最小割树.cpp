// 草稿11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"pch.h"
#include<memory>
#include<memory.h>
#include<array>
#include <iostream>
#include<vector>
#include<string>
#include<list>
#include<set>
#include<queue>
#include<map>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;
const int MAXN = 1500 + 1;
const int MAXG = MAXN * 2 + 1;
const int MAX_LOG = 21;
const int inf = 0x3f3f3f3f;
int n, q;

struct Edge
{
	int v, w;
	Edge(int v, int w) : v(v), w(w) {}
};

std::vector<Edge> g[MAXG];
int a[MAXN];
int tot;

inline void addEdge(int u, int v, int w) {
	//cout << u <<" "<< v << endl;
	g[u].emplace_back(v, w);
	g[v].emplace_back(u, w);
}
int deep[MAXG];
bool vis[MAXG], vis2[MAXG];
long long sz[MAXG], idx[MAXG], dep[MAXG], fa[MAXG], weight[MAXG];
long long dis[MAXG][MAX_LOG];
int lca[MAXG][MAX_LOG], Min[MAXG][MAX_LOG];
void dfsSize(int u, int pre) {
	sz[u] = 1;
	for (auto &p : g[u]) {
		if (!vis[p.v] && p.v != pre) {
			dfsSize(p.v, u);
			sz[u] += sz[p.v];
		}
	}
}
int get(int u, int pre, int n) {
	for (auto &p : g[u])
		if (!vis[p.v] && p.v != pre && sz[p.v] > n) return get(p.v, u, n);
	return u;
}
void dfs1(int u, int p)
{
	for (auto &s : g[u])
		if (s.v != p)
			deep[s.v] = deep[u] + 1, dfs1(s.v, u);
}
void dfs(int u, int pre, int d, int kk) {
	for (auto &p : g[u]) {
		if (!vis[p.v] && p.v != pre) {
			idx[p.v] = idx[u];
			Min[p.v][kk] = min(Min[u][kk], p.w);
			dis[p.v][kk] = dis[u][kk] + p.w;
			if (deep[p.v] > deep[u])
				lca[p.v][kk] = lca[u][kk];
			else
				lca[p.v][kk] = p.v;
			dfs(p.v, u, d, kk);
		}
	}
}

void build(int u, int d, int f)
{
	dfsSize(u, 0);
	vis[u = get(u, 0, sz[u] / 2)] = true;
	fa[u] = f;
	dep[u] = d;
	int c = 0;
	lca[u][dep[u]] = u;
	for (auto &p : g[u]) {
		if (!vis[p.v]) {
			dis[p.v][d] = p.w;
			Min[p.v][d] = p.w;
			idx[p.v] = c++;
			{
				if (deep[p.v] > deep[u])
					lca[p.v][dep[u]] = u;
				else
					lca[p.v][dep[u]] = p.v;
			}
			dfs(p.v, u, u, d);
			build(p.v, d + 1, u);
		}
	}
}
int getfa(int a, int b)
{
	int u, v;
	u = a, v = b;
	while (u != v)
	{
		if (dep[u] < dep[v])
			swap(u, v);
		else
			u = fa[u];
	}
	return u;
}
int query_min(int a, int b)
{
	int u = getfa(a, b);
	//cout << a << ": " << b << " " << u << endl;
	if (a == u)
		return Min[b][dep[u]];
	if (b == u)
		return Min[a][dep[u]];
	return min(Min[a][dep[u]], Min[b][dep[u]]);
}
int query_dis(int a, int b)
{
	int u = getfa(a, b);
	return dis[a][dep[u]] + dis[b][dep[u]];
}
int query_lca(int a, int b)
{
	int u = getfa(a, b);
	if (deep[lca[a][dep[u]]] < deep[lca[b][dep[u]]])
		return lca[a][dep[u]];
	else
		return lca[b][dep[u]];
}
const int INF = 0x3f3f3f3f;

struct Maxflow {
	struct Node {
		int v, f, c, i;

		Node(int v, int f, int i) : v(v), f(f), c(f), i(i) {}
	};

	std::vector<Node> g[MAXN];

	inline void addEdge(int u, int v, int f) {
		g[u].push_back(Node(v, f, g[v].size()));
		g[v].push_back(Node(u, f, g[u].size() - 1));
	}

	typedef std::vector<Node>::iterator Iterator;

	int n, s, t, iter[MAXN], h[MAXN], gap[MAXN];

	int dfs(int u, int flow) {
		if (u == t) return flow;
		int ret = 0;
		for (int &i = iter[u]; i < (int)g[u].size(); i++) {
			Node &p = g[u][i];
			if (p.f > 0 && h[u] == h[p.v] + 1) {
				int df = dfs(p.v, std::min(flow - ret, p.f));
				p.f -= df;
				g[p.v][p.i].f += df;
				if ((ret += df) == flow || h[s] >= n) return ret;
			}
		}
		if (--gap[h[u]] == 0) h[s] = n;
		gap[++h[u]]++;
		iter[u] = 0;
		return ret;
	}

	inline int maxflow(int s, int t) {
		this->s = s;
		this->t = t;
		memset(gap, 0, sizeof(int) * (n + 1));
		memset(h, 0, sizeof(int) * (n + 1));
		int ret = 0;
		for (gap[0] = n; h[s] < n;) {
			memset(iter, 0, sizeof(int) * (n + 1));
			ret += dfs(s, INF);
		}
		return ret;
	}

	inline void reset() {
		for (int i = 0; i <= n; i++)
			for (Iterator p = g[i].begin(); p != g[i].end(); ++p) p->f = p->c;
	}

	inline std::vector<Node> &operator[](int i) { return g[i]; }

	inline const std::vector<Node> &operator[](int i) const { return g[i]; }
} pp;

struct GomoryHuTree {
	int fa[MAXN], flow[MAXN];
	bool vis[MAXN];

	inline void bfs(Maxflow &g) {
		memset(vis, 0, sizeof(bool) * (g.n + 1));
		std::queue<int> q;
		q.push(g.s);
		vis[g.s] = true;
		for (int u; !q.empty();) {
			u = q.front();
			q.pop();
			for (Maxflow::Iterator p = g[u].begin(); p != g[u].end(); ++p) {
				if (p->f && !vis[p->v]) {
					vis[p->v] = true;
					q.push(p->v);
				}
			}
		}
	}

	inline void build(Maxflow &gg) {
		for (int i = 2; i <= gg.n; i++) fa[i] = 1;
		for (int u = 2, v; u <= gg.n; u++) {
			v = fa[u];
			flow[u - 1] = gg.maxflow(u, v);
			//cout <<"ans:"<< u<<" " << v <<" "<<flow[u - 1] << endl;
			g[u].push_back({ v,flow[u - 1] });
			g[v].push_back({ u,flow[u - 1] });
			bfs(gg);
			for (int i = u + 1; i <= gg.n; i++)
				if (fa[i] == v && vis[i]) fa[i] = u;
			gg.reset();
		}
	}
} d;
using namespace std;
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, s, u, v;
	cin >> n >> m;
	pp.n = n + 1;
	for (int i = 0, u, v, f; i < m; i++) {
		cin >> u >> v >> f;
		pp.addEdge(u + 1, v + 1, f);
	}
	d.build(pp);
	int Q;
	cin >> Q;
	build(1, 1, 0);
	while (Q--)
	{
		cin >> u >> v;
		cout << query_min(u + 1, v + 1) << '\n';
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
