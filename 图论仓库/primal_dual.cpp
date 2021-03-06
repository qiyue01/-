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
/*
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
namespace PrimalDual {
const int MAXN = 400000;
struct Node {
	int v, f, w, index;

	Node(int v, int f, int w, int index) : v(v), f(f), w(w), index(index) {}
};

std::vector<Node> edge[MAXN];

inline void addEdge(const int u, const int v, const int f, const int w) {
	edge[u].push_back(Node(v, f, w, edge[v].size()));
	edge[v].push_back(Node(u, 0, -w, edge[u].size() - 1));
}

typedef std::pair<int, int> Pair;

const int INF = 0x3f3f3f3f;

typedef __gnu_pbds::priority_queue<Pair, std::greater<Pair> > PriorityQueue;
int pree[MAXN], prev[MAXN];
PriorityQueue::point_iterator id[MAXN];

int h[MAXN], d[MAXN];
bool vis[MAXN];

inline void spfa(const int s, const int n) {
	static std::queue<int> q;
	memset(h, 0x3f, sizeof(int) * (n + 1));
	memset(vis, 0, sizeof(bool) * (n + 1));
	q.push(s), h[s] = 0;
	while (!q.empty()) {
		register int u = q.front();
		q.pop();
		vis[u] = false;
		for (register int i = 0; i < edge[u].size(); i++) {
			Node *e = &edge[u][i];
			if (e->f && h[u] + e->w < h[e->v]) {
				h[e->v] = h[u] + e->w;
				if (!vis[e->v]) q.push(e->v), vis[e->v] = true;
			}
		}
	}
}

inline void dijkstra(const int s, const int n) {
	memset(vis, 0, n + 1);
	memset(d, 0x3f, sizeof(int) * (n + 1));
	memset(id, 0, sizeof(PriorityQueue::point_iterator) * (n + 1));
	static PriorityQueue q;
	d[s] = 0, id[s] = q.push(Pair(0, s));
	while (!q.empty()) {
		Pair now = q.top();
		q.pop();
		register int v = now.second;
		if (vis[v] || d[v] < now.first) continue;
		vis[v] = true;
		for (register int i = 0; i < edge[v].size(); i++) {
			Node *p = &edge[v][i];
			register int w = d[v] + p->w + h[v] - h[p->v];
			if (p->f > 0 && d[p->v] > w) {
				d[p->v] = w, prev[p->v] = v, pree[p->v] = i;
				if (id[p->v] != NULL) q.modify(id[p->v], Pair(d[p->v], p->v));
				else id[p->v] = q.push(Pair(d[p->v], p->v));
			}
		}
	}
}

inline Pair minCostFlow(const int s, const int t, const int n, int f) {
	Pair ans(0, 0);
	dijkstra(s, n);
	while (f > 0) {
		dijkstra(s, n);
		if (d[t] == INF) break;
		//std::cout<<h[t]<<" "<<d[t]<<std::endl;
		for (register int i = 0; i <= n; i++) h[i] += d[i];
		register int flow = f;
		//std::cout<<h[t]<<" "<<d[t]<<std::endl;
		for (register int i = t; i != s; i = prev[i])
			flow = std::min(flow, edge[prev[i]][pree[i]].f);
		f -= flow, ans.first += flow, ans.second += flow * h[t];
		for (register int i = t; i != s; i = prev[i]) {
			Node *p = &edge[prev[i]][pree[i]];
			p->f -= flow, edge[p->v][p->index].f += flow;
		}
	}
	return ans;
}
void init()
{
	for(int i=0;i<MAXN;++i)
		edge[i].clear();
}
}
using namespace std;
using namespace PrimalDual;
*/