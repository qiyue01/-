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
namespace match_normal1
{
	const int MAXN = 250;
	class match_normal {
	public:
		int N;
		bool graph[MAXN][MAXN], inqueue[MAXN], inpath[MAXN], inblossom[MAXN];
		int head, tail;
		int queue[MAXN], father[MAXN], base[MAXN], match[MAXN];
		int start, finish, newbase;

		match_normal( int n)
		{
			N = n;
			memset(graph, 0, sizeof(graph));
		}
		void push(int u) {
			queue[tail] = u;
			tail++;
			inqueue[u] = true;
		}

		int pop() {
			int res = queue[head];
			head++;
			return res;
		}

		int find_common_ancestor(int u, int v) {
			memset(inpath,0,sizeof(inpath));
			while (true) {
				u = base[u];
				inpath[u] = true;
				if (u == start)
					break;
				u = father[match[u]];
			}
			while (true) {
				v = base[v];
				if (inpath[v]) break;
				v = father[match[v]];
			}
			return v;
		}

		void resert_trace(int u) {
			int v;
			while (base[u] != newbase) {
				v = match[u];
				inblossom[base[u]] = inblossom[base[v]] = true;
				u = father[v];
				if (base[u] != newbase) father[u] = v;
			}
		}

		void blossomconstract(int u, int v) {
			newbase = find_common_ancestor(u, v);
			memset(inblossom, 0,sizeof(inblossom));
			resert_trace(u);
			resert_trace(v);
			if (base[u] != newbase) father[u] = v;
			if (base[v] != newbase) father[v] = u;
			for (int tu = 1; tu <= N; tu++)
				if (inblossom[base[tu]]) {
					base[tu] = newbase;
					if (!inqueue[tu]) push(tu);
				}
		}

		void find_aug() {
			memset(inqueue, false,sizeof(inqueue));
			memset(father, 0,sizeof(father));
			for (int i = 1; i <= N; ++i)
				base[i] = i;
			head = tail = 1;
			push(start);
			finish = 0;
			while (head < tail) {
				int u = pop();
				for (int v = 1; v <= N; v++) {
					if (graph[u][v] && (base[u] != base[v]) && (match[u] != v)) 
					{
						if (v == start || (match[v] > 0) && father[match[v]] > 0)
							blossomconstract(u, v);
						else if (father[v] == 0) {
							father[v] = u;
							if (match[v] > 0)
								push(match[v]);
							else {
								finish = v;
								return;
							}
						}
					}
				}
			}
		}
		void aug_path()
		{
			int u, v, w;
			u = finish;
			while (u > 0)
			{
				v = father[u];
				w = match[v];
				match[v] = u;
				match[u] = v;
				u = w;
			}
		}
		void edmond()
		{
			memset(match, 0,sizeof(match));
			for (int u = 1; u <= N; ++u)
				if (match[u] == 0)
				{
					start = u;
					find_aug();
					if (finish > 0) aug_path();
				}
		}
	};
}
using namespace match_normal1;
