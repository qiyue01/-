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
namespace strong
{
	
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
			memset(DFN, 0, sizeof(DFN));
			memset(Instack, false, sizeof(Instack));
			memset(num, 0, sizeof(num));
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
}
namespace bridge{
	struct edge {
		int nxt, mark;
	}pre[200010];
	int n, m, idx, cnt, tot;
	int head[100010], DFN[100010], LOW[100010];
	bool cut[100010];
	void add(int x, int y)
	{
		pre[++cnt].nxt = y;
		pre[cnt].mark = head[x];
		head[x] = cnt;
	}
	void tarjan(int u, int fa)
	{
		DFN[u] = LOW[u] = ++idx;
		int child = 0;
		for (int i = head[u]; i != 0; i = pre[i].mark)
		{
			int nx = pre[i].nxt;
			if (!DFN[nx])
			{
				tarjan(nx, fa);
				LOW[u] = min(LOW[u], LOW[nx]);
				if (LOW[nx] >= DFN[u] && u != fa)
					cut[u] = 1;
				if (u == fa)
					child++;
			}
			LOW[u] = min(LOW[u], DFN[nx]);
		}
		if (child >= 2 && u == fa)
			cut[u] = 1;
	}
	void init()
	{
		memset(DFN, 0, sizeof(DFN));
		memset(head, 0, sizeof(head));
	}
	void solve(int n)
	{
		for (int i = 1; i <= n; ++i)
			if (DFN[i] == 0)
				tarjan(i, i);
	}
}
using namespace bridge;
int main()
{
	ios::sync_with_stdio(false);
	int n, m, u, v;
	cin >> n >> m;
	init();
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	solve(n);
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		if (cut[i] == true)
			ans++;
	cout << ans << endl;
	if (ans != 0)
		for (int i = 1; i <= n; ++i)
			if (cut[i] == true)
				cout << i << endl;
}