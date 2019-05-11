#include<string>
#include<cstring>
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
#include<cstdio>
using namespace std;
const int N = 100010;
const long long inf = 1e13;
namespace bf
{
	long long dis[N],iq[N];
	list<pair<int, long long>> edge[N];
	int vis[N];
	void add_edge(int u, int v, int w)
	{
		edge[u].push_back(make_pair(v, w));
	}
	void init()
	{
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
			return true;
		}
		return false;
	}
	bool bellman_ford(int beginning, int n)
	{
		dis[beginning] = 0;
		queue<int> que;
		que.push(beginning);
		bool flag = true;
		int cur;
		while (!que.empty())
		{
			cur = que.front();
			que.pop();
			iq[cur] = 0;
			vis[cur]++;
			for (auto &s : edge[cur])
				if (relax(cur, s.first, s.second) && iq[s.first]==false)
					que.push(s.first),iq[s.first]=1;
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