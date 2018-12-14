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
	int gap[MAXN], h[MAXN];

	struct Node {
		int v, f, index;
		Node(int v, int f, int index) : v(v), f(f), index(index) {}
	};

	std::vector<Node> edge[MAXN];

	inline void addEdge(int u, int v, int f) {
		edge[u].push_back(Node(v, f, edge[v].size()));
		edge[v].push_back(Node(u, 0, edge[u].size() - 1));
	}

	inline int sap(int v, int flow, int s, int t, int n) {
		static int iter[MAXN];
		if (v == t) return flow;
		register int rec = 0;
		for (register int i = iter[v]; i < edge[v].size(); i++) {
			Node *p = &edge[v][i];
			if (h[v] == h[p->v] + 1) {
				register int ret = sap(p->v, std::min(flow - rec, p->f), s, t, n);
				p->f -= ret, edge[p->v][p->index].f += ret, iter[v] = i;
				if ((rec += ret) == flow) return flow;
			}
		}
		if (!(--gap[h[v]])) h[s] = n;
		gap[++h[v]]++, iter[v] = 0;
		return rec;
	}

	inline int sap(int s, int t, int n) {
		register int ret = 0;
		gap[0] = n;
		while (h[s] < n) ret += sap(s, INT_MAX, s, t, n);
		return ret;
	}
	void init()
	{
		for (int i = 0; i < MAXN; ++i)
			edge[i].clear();
		memset(h, 0, sizeof(h));
		memset(gap, 0, sizeof(gap));
	}
