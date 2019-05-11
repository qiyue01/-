#include "pch.h"
#include<iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include<set>
#include<unordered_set>
using namespace std;
const int MN = 650005;

int N, M, cnt;
std::vector<int> G[MN], T[MN * 2];
bool vis[MN], flag[MN];
int dfn[MN], low[MN], dfc;
int stk[MN], tp;
unordered_set<int> anti[MN];
vector<int> ff[MN];
void Tarjan(int u)
{
	low[u] = dfn[u] = ++dfc;
	stk[++tp] = u;
	for (auto v : G[u]) {
		if (!dfn[v]) {
			Tarjan(v);
			low[u] = std::min(low[u], low[v]);
			if (low[v] == dfn[u]) {
				++cnt;
				anti[cnt].insert(u);
				for (int x = 0; x != v; --tp) {
					x = stk[tp];
					anti[cnt].insert(x);
					for (auto &s : ff[x])
						if (anti[cnt].find(s) != anti[cnt].end())
							flag[cnt] = 1;
					T[cnt].push_back(x);
					T[x].push_back(cnt);
				}
				T[cnt].push_back(u);
				T[u].push_back(cnt);
			}
		}
		else low[u] = std::min(low[u], dfn[v]);
	}
}
void init(int n, int m)
{
	N = n, M = m;
	cnt = N;
}
void add_edge(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}
void build()
{
	for (int u = 1; u <= N; ++u)
		if (!dfn[u]) Tarjan(u), --tp;
}
using namespace std;

bool dfs(int u, int t, bool a)
{
	vis[u] = true;
	if (flag[u] == 1)
		a = 1;
	if (u == t)
		return a;
	for (auto &s : T[u])
		if (vis[s] == false)
		{
			cout << u << " " << s << endl;
			if (dfs(s, t, a))
				return true;
		}
	return false;
}