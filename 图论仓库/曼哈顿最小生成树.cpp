#include "pch.h"
#include <iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
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
namespace  Manhattan_tree
{
		const int inf = 0x3f3f3f3f;
		const int maxn = 100010;
		struct point 
		{ 
			int x, y, id; 
		}p[maxn];
		bool cmp(point a, point b)
		{
			if (a.x != b.x)
				return a.x < b.x;
			else
				return a.y < b.y;
		}
		struct BIT
		{
			int min_val, pos;
			void init()
			{
				min_val = inf;
				pos = -1;
			}
		}bit[maxn];
		struct Edge 
		{ 
			int u, v, d; 
		}edge[maxn<<2];
		bool cmpedge(Edge a,Edge b)
		{
			return a.d < b.d;
		}
		int tot;
		int n;
		int F[maxn];
		int find(int x)
		{
			if (F[x] == -1)
				return x;
			else
				return F[x] = find(F[x]);
		}
		void add_edge(int u,int v,int d)
		{
			edge[tot].u = u;
			edge[tot].v = v;
			edge[tot].d = d;
			tot++;
		}
		int lowbit(int x)
		{
			return x & (-x);
		}
		void update(int i,int val,int pos)
		{
			while (i>0)
			{
				if (val < bit[i].min_val)
				{
					bit[i].min_val = val;
					bit[i].pos = pos;
				}
				i -= lowbit(i);
			}
		}
		int ask(int i,int m)
		{
			int min_val = inf, pos = -1;
			while (i<=m)
			{
				if (bit[i].min_val < min_val)
				{
					min_val = bit[i].min_val;
					pos = bit[i].pos;
				}
				i += lowbit(i);
			}
			return pos;
		}
		int distance(point a,point b)
		{
			return abs(a.x - b.x) + abs(a.y - b.y);
		}
		void Manhattan(int n,point p[])
		{
			int a[maxn], b[maxn];
			tot = 0;
			for (int dir = 0; dir < 4; dir++)
			{
				if (dir == 1 || dir == 3)
					for (int i = 0; i < n; ++i)
						swap(p[i].x, p[i].y);
				else if (dir == 2)
				{
					for (int i = 0; i < n; ++i)
						p[i].x = -p[i].x;
				}
				sort(p, p + n, cmp);
				for (int i = 0; i < n; ++i)
					a[i] = b[i] = p[i].y - p[i].x;
				sort(b, b + n);
				int m = unique(b, b + n) - b;
				for (int i = 1; i <= m; ++i)
					bit[i].init();
				for (int i = n - 1; i >= 0; --i)
				{
					int pos = lower_bound(b, b + m, a[i]) - b + 1;
					int ans = ask(pos, m);
					if (ans != -1)
						add_edge(p[i].id, p[ans].id, distance(p[i], p[ans]));
					update(pos, p[i].x + p[i].y, i);
				}
			}
		}
		int solve(int k)//ÕÒµÚk´óµÄ±ß
		{
			Manhattan(n, p);
			memset(F, -1, sizeof(F));
			sort(edge, edge + tot, cmpedge);
			int u, v;
			for (int i = 0; i < tot; ++i)
			{
				u = edge[i].u;
				v = edge[i].v;
				int t1 = find(u), t2 = find(v);
				if (t1!=t2)
				{
					F[t1] = t2;
					k--;
					if (k == 0)
						return edge[i].d;
				}
			}
		}
}
using namespace Manhattan_tree;

