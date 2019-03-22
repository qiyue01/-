#include "pch.h"
#include<cstdio>
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
/*
namespace strong
{
	const int MAXN = 5010;
	const int MAXM = 101000;
	class Edge
	{
	public:
		int to, next, w;
	};
	Edge edge[MAXM];
	int head[MAXN], tot;
	int Low[MAXN], DFN[MAXN], Stack[MAXN], Belong[MAXN];
	int Index, top;
	int scc;
	bool Instack[MAXN];
	int num[MAXN];
	void addedge(int u, int v, int w)
	{
		edge[tot].to = v;
		edge[tot].next = head[u];
		edge[tot].w = w;
		head[u] = tot++;
	}
	void tarjan(int u)
	{
		int v;
		Low[u] = DFN[u] = ++Index;
		Stack[top++] = u;
		Instack[u] = true;
		for (int i = head[u]; i != -1; i = edge[i].next)
		{
			v = edge[i].to;
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
	bool solve(int N)
	{
		memset(DFN, 0, sizeof(DFN));
		memset(Instack, false, sizeof(Instack));
		memset(num, 0, sizeof(num));
		Index = scc = top = 0;
		for (int i = 1; i <= N; ++i)
			if (DFN[i] == 0)
				tarjan(i);
		N = N / 2;
		for (int i = 1; i <= N; ++i)
			if (Belong[i] == Belong[i + N])
				return false;
		return true;
	}
	void init()
	{
		tot = 0;
		memset(head, -1, sizeof(head));
	}
}
using namespace strong;
*/