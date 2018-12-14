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

namespace primal_dual
{
	const int MAXN = 6100;
	struct node
	{
		int v, f, w, index;
		node(int v,int f,int w,int index) : v(v), f(f), w(w), index(index) {}
	};
	vector<node> edge[MAXN];
	void addedge(int u,int v,int flow,int cost)
	{
		edge[u].push_back(node(v, flow, cost, edge[v].size()));
		edge[v].push_back(node(u, 0, -cost, edge[u].size() - 1));
	}
	const int inf= 0x3f3f3f3f;
	int pree[MAXN], prev[MAXN];
	int h[MAXN], dis[MAXN];
	bool vis[MAXN];
	priority_queue<pair<int,int>> pq;
	void spfa(const int s,const int n)
	{
		queue<int> q;
		memset(h, 0x3f, sizeof(h));
		memset(vis, 0, sizeof(vis));
		q.push(s);
		h[s] = 0;
		while (!q.empty())
		{
			int u= q.front();
			q.pop();
			vis[u] = false;
			for (auto &p : edge[u])
			{
				if (p.f > 0 && h[u] + p.w < h[p.v])
				{
					h[p.v] = h[u] + p.w;
					if (!vis[p.v])
						q.push(p.v), vis[p.v] = true;
				}
			}
		}
	}
	void dijkstra(int s,int n)
	{
		memset(vis, 0, n + 1);
		memset(dis, 0x3f, sizeof(dis));
		int v,w;
		dis[s] = 0;
		pq.push(make_pair(0,s));
		while (!pq.empty())
		{
			pair<int,int> now = pq.top();
			pq.pop();
			v = now.second;
			if (dis[v]<now.first)continue;
			vis[v] = true;
			for (int i=0;i<edge[v].size();++i)
			{
				node *p = &edge[v][i];
				w = dis[v] + p->w + h[v] - h[p->v];
				if (p->f > 0 && dis[p->v] > w)
				{
					dis[p->v] = w, prev[p->v] = v, pree[p->v] = i;
					pq.push(make_pair(dis[p->v],p->v));
				}
			}
		}
	}
	pair<int,int> MCMF(int s,int t,int n,int f)
	{
		pair<int, int> ans;
		spfa(s, n);
		while (f > 0)
		{
			dijkstra(s, n);
			if (dis[t] == inf) break;
			for (int i = 0; i <= n; ++i) h[i] += dis[i];
			int flow = f;
			for (int i = t; i != s; i = prev[i])
				flow = min(flow, edge[prev[i]][pree[i]].f);
			f -= flow, ans.first += flow, ans.second += flow * h[t];
			for (int i = t; i != s; i = prev[i])
			{
				node *p = &edge[prev[i]][pree[i]];
				{
					p->f -= flow;
					edge[p->v][p->index].f += flow;
				}
			}
		}
		return  ans;
	}
	void init()
	{
		for (int i = 0; i < MAXN; ++i) edge[i].clear();
	}

}
using namespace std;
using namespace primal_dual;
#define For(i,j) for(int i=0;i<j;++i)
/*
struct node2
{
	int x, y, w;
	node2(int i, int j, int k) :x(i), y(j), w(k) {}
};
list<node2> part;
set<int> part2, part4;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int a;
	cin >> a;
	int a1, a2, a3, b1, b2, b3;
	while (a--)
	{
		init();
		part.clear(), part2.clear(), part4.clear();
		cin >> a1 >> a2 >> a3;
		for (int i = 0; i < a3; ++i)
		{
			cin >> b1 >> b2 >> b3;
			part.push_back(node2(b1, b2, b3));
			part2.insert(b1);
			part2.insert(b2);
		}
		map<int, int> trans;
		int L = 1;
		for (auto &s : part2)
		{
			trans[s] = L++;
		}
		for (auto &s : part)
		{
			s.x = trans[s.x];
			s.y = trans[s.y] + 1;
			addedge(s.x, s.y, 1, -s.w);
			part4.insert(s.x);
			part4.insert(s.y);
		}
		addedge(0, 1, a2, 0);
		vector<int> part3(part4.begin(), part4.end());
		for (int i = 0; i < part3.size() - 1; ++i)
		{
			addedge(part3[i], part3[i + 1], a2, 0);
		}
		int n = part3.back() + 10;
		addedge(part3.back(), part3.back() + 5, a2, 0);
		int cost;
		pair<int,int> res = MCMF(0, n - 5, n, INT_MAX);
		cout << -res.second << endl;
	}
	return 0;
}*/