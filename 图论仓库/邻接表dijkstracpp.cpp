#include "pch.h"
#include <iostream>
#include<vector>
#include<cstring>
#include<list>
#include<set>
#include<queue>
#include<map>
#include<stack>
#include<algorithm>
#include<unordered_map>
using namespace std;
# define maxn 210000+10
const int N = 300010;
const long long inf = 1e18;
#define int long long
namespace bf
{
	long long dis[N], iq[N], pre[N];
	vector<pair<int, long long>> edge[N];
	int vis[N];
	bool inque[N];
	void add_edge(int u, int v, int w)
	{
		edge[u].push_back(make_pair(v, w));
	}
	void init()
	{
		memset(inque, 0, sizeof(inque));
		for (int i = 0; i < N; ++i)
		{
			dis[i] = inf;
			vis[i] = 0;
			edge[i].clear();
		}
	}
	bool relax(int u, int v, long long w)
	{
		if (dis[v] > dis[u] + w)
		{
			dis[v] = dis[u] + w;
			pre[v] = u;
			return true;
		}
		return false;
	}
	bool bellman_ford(int beginning, int n)
	{
		dis[beginning] = 0;
		priority_queue<pair<long long, int> > que;
		que.push({ 0,beginning });
		bool flag = true;
		int cur;
		while (!que.empty())
		{
			cur = que.top().second;
			que.pop();
			inque[cur] = false;
			//iq[cur] = 0;
			vis[cur]++;
			for (auto &s : edge[cur])
				if (relax(cur, s.first, s.second) && !inque[s.first])
				{
					que.push({ -dis[s.first],s.first });
					inque[s.first] = true;
				}
			if (vis[cur] > n + 1)
			{
				flag = false;
				break;
			}
		}
		return flag;
	}
}
using namespace bf;