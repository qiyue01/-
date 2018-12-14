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
const int MAXN = 10010;
const int MAXM = 501000;

class Tarjan //求图的强连通分量，常用于压点
{
public:
	class Edge
	{
	public:
		int to, next;
	};
	Edge egde[MAXM];
	int head[MAXN], tot;
	int Low[MAXN], DFN[MAXN], Stack[MAXN], Belong[MAXN];
	int Index, top;
	int scc;
	bool Instack[MAXN];
	int num[MAXN];
	void addedge(int u, int v)
	{
		egde[tot].to = v;
		egde[tot].next = head[u];
		head[u] = tot++;
	}
	void tarjan(int u)
	{
		int v;
		Low[u] = DFN[u] = ++Index;
		Stack[top++] = u;
		Instack[u] = true;
		for (int i = head[u]; i != -1; i = egde[i].next)
		{
			v = egde[i].to;
			if (DFN[v] == 0)
			{
				tarjan(v);
				if (Low[u] > Low[v])
					Low[u] = Low[v];
			}
			else if (Instack[v] && Low[u] > DFN[v])
				Low[u] = DFN[v];
		}
		if (Low[u] == DFN[u])
		{
			scc++;
			do {
				v = Stack[--top];
				Instack[v] = false;
				Belong[v] = scc;
				num[scc]++;
			} while (v != u);
		}
	}
	void solve(int N)
	{
		memset(DFN, 0,sizeof(DFN));
		memset(Instack, false,sizeof(Instack));
		memset(num, 0,sizeof(num));
		Index = scc = top = 0;
		for (int i = 1; i <= N; ++i)
			if (DFN[i] == 0)
				tarjan(i);
	}
	void init()
	{
		tot = 0;
		memset(head, -1, sizeof(head));
	}
};
class bridge1 //求图的桥
{
	class Edge
	{
	public:
		int to, next;
		bool cut;
		Edge() = default;
	};
public:
	Edge edge[MAXM];
	int head[MAXN], low[MAXN], DFN[MAXN], Stack[MAXN], add_block[MAXN], tot, Index, top, bridge;
	bool cut[MAXN], Instack[MAXN];
	map<int,int> part;
	bool isRepeat(int u, int v)
	{
		if (part.find(u*MAXN + v) != part.end()) return true;
		if (part.find(v*MAXN + u) != part.end()) return true;
		part[u*MAXN + v] = part[v*MAXN + u] = 1;
		return false;
	}
	void addedge(int u, int v)
	{
		edge[tot].to = v;
		edge[tot].next = head[u];
		edge[tot].cut = false;
		head[u] = tot++;
	}
	void Tarjan(int u, int pre)
	{
		int v;
		low[u] = DFN[u] = ++Index;
		Stack[top++] = u;
		Instack[u] = true;
		int son = 0;
		int pre_cnt = 0;
		for (int i = head[u]; i != -1; i = edge[i].next)
		{
			v = edge[i].to;
			if (v == pre && pre_cnt == 0)
			{
				pre_cnt++;
				continue;
			}
			if (!DFN[v])
			{
				son++;
				Tarjan(v, u);
				if (low[u] > low[v])
					low[u] = low[v];
				if (low[v] > DFN[u])
				{
					bridge++;
					edge[i].cut = true;
					edge[i ^ 1].cut = true;
				}
				if (u != pre && low[v] >= DFN[u])
				{
					cut[u] = true;
					add_block[u]++;
				}
			}
			else if (low[u] > DFN[v])
				low[u] = DFN[v];
		}
		if (u == pre && son > 1)
			cut[u] = true;
		if (u == pre)
			add_block[u] = son - 1;
		Instack[u] = false;
		top--;
	}
	int k;
	void solve(int N)
	{
		k = 0;
		memset(DFN, 0,sizeof(DFN));
		memset(Instack, 0, sizeof(Instack));
		memset(add_block, 0, sizeof(add_block));
		memset(cut, false, sizeof(cut));
		Index = top = 0;
		bridge = 0;
		int cnt = 0;
		for (int i = 1; i <= N; ++i)
		{
			if (!DFN[i])
			{
				Tarjan(i, i);
				cnt++;
			}
		}
		int ans = 0;
		for (int i = 1; i <= N; ++i)
			ans = max(ans, cnt + add_block[i]);
		cout << ans << endl;
	}
	void init()
	{
		tot = 0;
		memset(head, -1, sizeof(head));
	}
};
/*
int main()
{
	ios::sync_with_stdio(false);
	int n, m,u,v;
	while (cin >> n>>m)
	{
		if (n == 0 && m == 0)
			break;
		bridge1 part;
		part.init();
		while (m--)
		{
			cin >> u >> v;
			u++; v++;
			part.addedge(u, v);
			part.addedge(v, u);
		}
		part.solve(n);
	}
}*/