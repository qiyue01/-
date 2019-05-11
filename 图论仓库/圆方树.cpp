#include "pch.h"
#include <iostream>
#include<vector>
#include<cstring>
#include<list>
#include<set>
#include<queue>
#include<map>
#include<stack>
#include<algorithm>
using namespace std;
#define int long long
#define double long double
const int N = 21000;
const double MAXN = 10e19;
int fa[N], de[N], tot, n;
struct Edge {
	int to[N << 2], nx[N << 2], w[N << 2], pr[N], tp;
	void add(int u, int v, int W)
	{
		to[++tp] = v;
		nx[tp] = pr[u];
		pr[u] = tp;
		w[tp] = W;
	}
	void adds(int u, int v, int w)
	{
		add(u, v, w);
		add(v, u, w);
	}
};
struct Round_Square_Tree {
	Edge T;
	int sz[N], fa[N], ds[N], de[N], d[N], di[N], c[N];
	void dfs1(int u, int ff) {
		fa[u] = ff; de[u] = de[ff] + 1; sz[u] = 1;
		for (int i = T.pr[u], v; i; i = T.nx[i])
			if ((v = T.to[i]) != ff)
			{
				di[v] = di[u] + T.w[i]; dfs1(v, u);
				sz[u] += sz[v]; sz[ds[u]] < sz[v] ? ds[u] = v : 0;
			}
	}
	void dfs2(int u, int c) {
		d[u] = c;
		if (!ds[u])
			return;
		dfs2(ds[u], c);
		for (int i = T.pr[u]; i; i = T.nx[i])
			if (T.to[i] != ds[u] && T.to[i] != fa[u])
				dfs2(T.to[i], T.to[i]);
	}
	int Lca(int u, int v) {
		while (d[u] != d[v])
		{
			de[d[u]] < de[d[v]] ? u ^= v ^= u ^= v : 0;
			u = fa[d[u]];
		}
		return de[u] < de[v] ? u : v;
	}
	int Jump(int u, int c) {
		int r;
		while (d[u] != d[c])
			r = d[u], u = fa[d[u]];
		return u == c ? r : ds[c];
	}
	int Query(int u, int v) {
		int x = Lca(u, v);
		if (x <= n) return di[u] + di[v] - (di[x] << 1);
		int cu = Jump(u, x), cv = Jump(v, x), cd = abs(c[cu] - c[cv]);
		cd = std::min(cd, c[x] - cd);
		return di[u] - di[cu] + di[v] - di[cv] + cd;
	}
}rst;
struct Tarjan {
	Edge G;
	int di[N], fa[N], dfn[N], low[N], tm;
	void Build(int u, int v, int d)
	{
		int tp = de[v] - de[u] + 1, s = d + di[v] - di[u], D = d; rst.c[++tot] = s;
		for (int i = v; i != u; i = fa[i])
			rst.T.adds(tot, i, std::min(D, s - D)), rst.c[i] = D, D += di[i] - di[fa[i]];
		rst.T.adds(tot, u, 0);
	}
	void dfs(int u, int ff)
	{
		fa[u] = ff;
		dfn[u] = low[u] = ++tm;
		de[u] = de[ff] + 1;
		for (int i = G.pr[u]; i; i = G.nx[i])
		{
			int v = G.to[i];
			if (v == ff) continue;
			if (!dfn[v])
				di[v] = di[u] + G.w[i], dfs(v, u), low[u] = std::min(low[u], low[v]);
			else
				low[u] = std::min(low[u], dfn[v]);
			if (dfn[u] < low[v])
				rst.T.adds(u, v, G.w[i]);
		}
		for (int i = G.pr[u]; i; i = G.nx[i])
		{
			int v = G.to[i];
			if (v == ff)
				continue;
			if (fa[v] != u && dfn[u] < dfn[v])
				Build(u, v, G.w[i]);
		}
	}
}tar;
void init(int N)
{
	tot = n = N;
	tar.dfs(1, 0); rst.dfs1(1, 0); rst.dfs2(1, 1);
}

