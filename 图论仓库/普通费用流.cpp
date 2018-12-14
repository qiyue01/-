
#include "pch.h"
#include <iostream>
#include<cmath>
#include<cstring>
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
namespace cost_flow_normal
{
	const int MAXN = 5920;
	const int INF = 0x3f3f3f3f;

	template <typename T>
	inline bool tense(T &x, const T v) {
		return (x > v) ? (x = v, true) : false;
	}

	struct Costflow {
		struct Node {
			int v, f, w, i;
			Node(int v, int f, int w, int i) : v(v), f(f), w(w), i(i) {}
		};

		std::vector<Node> g[MAXN];

		typedef std::vector<Node>::iterator Iterator;

		int s, t, n, iter[MAXN], que[MAXN * 3], h[MAXN];
		bool vis[MAXN];

		inline void addEdge(int u, int v, int f, int w) {
			g[u].push_back(Node(v, f, w, g[v].size()));
			g[v].push_back(Node(u, 0, -w, g[u].size() - 1));
		}

		inline void bellmanFord() {
			memset(h, 0x3f, sizeof(int) * (n + 1));
			int qh = 0, qt = 0;
			h[que[qt++] = s] = 0;
			for (int u; qh < qt;) {
				vis[u = que[qh++]] = false;
				for (Iterator p = g[u].begin(); p != g[u].end(); ++p) {
					if (p->f > 0 && h[u] + p->w < h[p->v]) {
						h[p->v] = h[u] + p->w;
						if (!vis[p->v]) vis[que[qt++] = p->v] = true;
					}
				}
			}
		}

		int dfs(int u, int flow, int &cost) {
			if (u == t) {
				cost += h[t] * flow;
				return flow;
			}
			int ret = 0;
			vis[u] = true;
			for (int &i = iter[u]; i < (int)g[u].size(); i++) {
				Node &p = g[u][i];
				if (!vis[p.v] && p.f > 0 && h[u] == h[p.v] - p.w) {
					int df = dfs(p.v, std::min(flow - ret, p.f), cost);
					p.f -= df;
					g[p.v][p.i].f += df;
					if ((ret += df) == flow) break;
				}
			}
			vis[u] = false;
			iter[u] = 0;
			return ret;
		}

		inline int mincostMaxflow(int s, int t, int &cost) {
			this->s = s;
			this->t = t;
			int ret = 0;
			for (cost = 0;;) {
				bellmanFord();
				if (h[t] == INF) break;
				ret += dfs(s, INF, cost);
			}
			return ret;
		}
		void init()
		{
			for (int i = 0; i < MAXN; ++i)
				g[i].clear();
			memset(que, 0, sizeof(que));
			memset(h, 0, sizeof(h));
			memset(vis, 0, sizeof(vis));
			memset(iter, 0, sizeof(iter));
		}
	} g;//每次都要初始化g.n;
}
