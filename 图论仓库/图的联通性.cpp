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

namespace strong
{
	const int MAXN = 500010;
	const int MAXM = 1001000;
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
	vector<pair<int, int> > edge2[MAXN];
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
	void solve(int N)
	{
		memset(DFN, 0, sizeof(DFN));
		memset(Instack, false, sizeof(Instack));
		memset(num, 0, sizeof(num));
		Index = scc = top = 0;
		for (int i = 1; i <= N; ++i)
			if (DFN[i] == 0)
				tarjan(i);
	}
	int ans[MAXN];
	void rebuild(int N)
	{
		for (int i = 1; i <= N; ++i)
			for (int j = head[i]; j != -1; j = edge[j].next)
			{
				if (Belong[i] != Belong[edge[j].to])
				{
					edge2[Belong[i]].push_back(make_pair(Belong[edge[j].to], edge[j].w));
				}
				else
				{
					if (edge[i].w == 1)
						ans[Belong[i]] = 1;
				}
			}
	}
	void init()
	{
		tot = 0;
		memset(head, -1, sizeof(head));
	}
}

namespace bridge2
{
	const int INF = 0x3f3f3f3f;
	/*
	*  已经自带去重边，加边时不用特判，若u，v间有重边则必不为桥
	*  求 无向图的割点和桥
	*  可以找出割点和桥，求删掉每个点后增加的连通块。
	*  需要注意重边的处理，可以先用矩阵存，再转邻接表，或者进行判重
	*/
	const int MAXN = 20010;
	const int MAXM = 100010;
	struct Edge
	{
		int to, next;
		int w;
		bool cut;//是否为桥的标记
	}edge[MAXM];
	int head[MAXN], tot;
	int Low[MAXN], DFN[MAXN], Stack[MAXN];
	int Index, top;
	bool Instack[MAXN];
	bool cut[MAXN];
	int add_block[MAXN];//删除一个点后增加的连通块
	int bridge;

	void addedge(int u, int v, int w)
	{
		edge[tot].to = v; edge[tot].next = head[u]; edge[tot].cut = false;
		edge[tot].w = w;
		head[u] = tot++;
	}


	void Tarjan(int u, int pre)
	{
		int v;
		Low[u] = DFN[u] = ++Index;
		Stack[top++] = u;
		Instack[u] = true;
		int son = 0;
		int pre_num = 0;
		for (int i = head[u]; i != -1; i = edge[i].next)
		{
			v = edge[i].to;
			if (v == pre && pre_num == 0)
			{
				pre_num++;
				continue;
			}
			if (!DFN[v])
			{
				son++;
				Tarjan(v, u);
				if (Low[u] > Low[v])Low[u] = Low[v];
				//桥
				//一条无向边(u,v)是桥，当且仅当(u,v)为树枝边，且满足DFS(u)<Low(v)。
				if (Low[v] > DFN[u])
				{
					bridge++;
					edge[i].cut = true;
					edge[i ^ 1].cut = true;
				}
				//割点
				//一个顶点u是割点，当且仅当满足(1)或(2) (1) u为树根，且u有多于一个子树。
				//(2) u不为树根，且满足存在(u,v)为树枝边(或称父子边，
				//即u为v在搜索树中的父亲)，使得DFS(u)<=Low(v)
				if (u != pre && Low[v] >= DFN[u])//不是树根
				{
					cut[u] = true;
					add_block[u]++;
				}
			}
			else if (Low[u] > DFN[v])
				Low[u] = DFN[v];
		}
		//树根，分支数大于1
		if (u == pre && son > 1)cut[u] = true;
		if (u == pre)add_block[u] = son - 1;
		Instack[u] = false;
		top--;
	}
	void init(int N)
	{
		memset(DFN, 0, sizeof(DFN));
		memset(Instack, false, sizeof(Instack));
		memset(add_block, 0, sizeof(add_block));
		memset(cut, false, sizeof(cut));
		Index = top = 0;
		bridge = 0;
		for (int i = 1; i <= N; i++)
			if (!DFN[i])
				Tarjan(i, i);
	}
	int  solve(int N)
	{
		int ret = INF;
		for (int u = 1; u <= N; u++)
			for (int i = head[u]; i != -1; i = edge[i].next)
				if (edge[i].cut)
					ret = min(ret, edge[i].w);
		if (ret == INF)ret = -1;
		if (ret == 0)ret++;
		return ret;
	}
	int slove2(int N)
	{
		int ans=0;
		for (int i = 1; i <= N; ++i)
			if (cut[i] == true)
				ans++;
		return ans;
	}
	
	//并查集判断图联通
	int F[MAXN];
	void graph_init()
	{
		memset(F, -1, sizeof(F));
		tot = 0;
		memset(head, -1, sizeof(head));
	}
	int find(int x)
	{
		if (F[x] == -1)return x;
		else return F[x] = find(F[x]);
	}	
	void bing(int u, int v)
	{
		int t1 = find(u);
		int t2 = find(v);
		if (t1 != t2)F[t1] = t2;
	}
}
using namespace bridge2;

