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
const int INF = 0x7f7f7f7f;
struct HK
{//uN为x方点，从0开始编号
	vector<int> G[MAXN];
	int uN;
	int Mx[MAXN], My[MAXN];
	int dx[MAXN], dy[MAXN];
	int dis;
	bool used[MAXN];
	bool hk_search()
	{
		queue<int> Q;
		dis = INF;
		memset(dx, -1, sizeof(dx));
		memset(dy, -1, sizeof(dy));
		for(int i=0;i<uN;++i)
			if (Mx[i] == -1)
			{
				Q.push(i);
				dx[i] = 0;
			}
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			if (dx[u] > dis)
				break;
			int sz = G[u].size();
			for (int i = 0; i < sz; ++i)
			{
				int v = G[u][i];
				if (dy[v] == -1)
				{
					dy[v] = dx[u] + 1;
					if (My[v] == -1)
						dis = dy[v];
					else
					{
						dx[My[v]] = dy[v] + 1;
						Q.push(My[v]);
					}
				}
			}

		}
		return dis != INF;
	}
	bool DFS(int u)
	{
		int sz = G[u].size();

	}
	int MaxMatch()
	{
		int res = 0;
		memset(Mx, -1, sizeof(Mx));
		memset(My, - 1, sizeof(My));
		while (hk_search())
		{
			memset(used, false, sizeof(used));
			for (int i = 0; i < uN; ++i)
				if (Mx[i] == -1 && DFS(i))
					res++;
		}
		return res;
	}
};
const int maxn = 500 + 5;
const int inf = 0x7fffffff;
class KM_max
{
public:
	int n, m;
	int lx[maxn], ly[maxn], visx[maxn], visy[maxn];
	int link[maxn], slack[maxn], w[maxn][maxn];
	KM_max()
	{
		//memset(w, -1, sizeof(w));
	}
	int dfs(int x)
	{
		visx[x] = 1;
		for (int y = 1; y <= m; y++) if (w[x][y] != -1)
		{
			if (visy[y]) continue;
			int t = lx[x] + ly[y] - w[x][y];
			if (t == 0)
			{
				visy[y] = 1;
				if (link[y] == -1 || dfs(link[y]))
				{
					link[y] = x;
					return 1;
				}
			}
			else if (slack[y] > t) slack[y] = t;
		}
		return 0;
	}

	int KM()
	{
		memset(link, -1, sizeof(link));
		memset(ly, 0, sizeof(ly));
		for (int x = 1; x <= n; x++)
		{
			lx[x] = -inf;
			for (int y = 1; y <= m; y++)
				lx[x] = max(lx[x], w[x][y]);
		}
		for (int x = 1; x <= n; x++)
		{
			for (int i = 1; i <= m; i++) slack[i] = inf;
			int flag = 0;
			for (int i = 1; i <= m; i++) if (w[x][i] != -1) flag = 1;
			while (flag)
			{
				memset(visx, 0, sizeof(visx));
				memset(visy, 0, sizeof(visy));
				if (dfs(x)) break;
				int d = inf;
				for (int i = 1; i <= m; i++)
					if (!visy[i] && d > slack[i]) d = slack[i];
				for (int i = 1; i <= n; i++)
					if (visx[i]) lx[i] -= d;
				for (int i = 1; i <= m; i++)
				{
					if (visy[i]) ly[i] += d;
					else slack[i] -= d;
				}
			}
		}
		int ans = 0;
		int vis[maxn];
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= m; i++)
		{
			if (link[i] != -1)
			{
				ans += w[link[i]][i];
				vis[link[i]] = 1;
			}
		}
		int i = 1;
		for (i = 1; i <= n; i++)
			if (vis[i] == 0) return -1;
		return ans;
	}
};
int g[MAXN][MAXN];
int linker[MAXN][MAXN];
class match_2   //二分图多重匹配
{
public:
	int uN, vN;
	bool used[510];
	int num[MAXN];
	bool dfs(int u)
	{
		for(int v=0;v<vN;++v)
			if (g[u][v] && !used[v])
			{
				used[v] = true;
				if (linker[v][0] < num[v])
				{
					linker[v][++linker[v][0]] = u;
					return true;
				}

				for (int i = 1; i <= num[v]; ++i)
					if (dfs(linker[v][i]))
					{
						linker[v][i] = u;
						return true;
					}
			}
		return false;
	}
	int hungary()
	{
		int res = 0;
		for (int i = 0; i < vN; ++i)
			linker[i][0] = 0;
		for (int u = 0; u < uN; ++u)
		{
			memset(used, false, sizeof(used));
			if (dfs(u)) res++;
		}
		return res;
	}
};
