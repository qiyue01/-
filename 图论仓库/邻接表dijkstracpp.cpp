#include "pch.h"
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
using namespace std;
# define maxn 200000+10

class dijkstra
{
public:
	struct node
	{
		long long distance;
		int father;
		int sign;
		friend bool operator <(node a, node b)
		{
			return b.distance > a.distance;
		}
		friend bool operator >(node a, node b)
		{
			return b.distance < a.distance;
		}
	};
	vector<pair<int,int> > G[1500];
	priority_queue<node> part;
	vector<node> way;
	void set(long i)
	{
		way.resize(i + 1);
		for (int i = 0; i < 1500; ++i)
			G[i].clear();
	}
	void insert(long u, long v, int w)
	{
		G[u].push_back(make_pair(v, w));
	}
	bool relax(long u, long v, long w)
	{
		if (way[v].distance > way[u].distance + w)
		{
			way[v].distance = way[u].distance + w;
			way[v].father = u;
			return true;
		}
		return false;
	}
	long long shortest_path(long beginning, long ending)
	{
		for (long i = 0; i < way.size(); ++i)
		{
			way[i].distance = 110000000000;
			way[i].father = -1;
			way[i].sign = i;
		}
		way[beginning].distance = 0;
		part.push(way[beginning]);
		while (part.size() != 0)
		{
			node part2 = part.top();
			part.pop();
			for (int i=0;i<G[part2.sign].size();++i)
			{
				int temp = G[part2.sign][i].first;
				if (relax(part2.sign, temp, G[part2.sign][i].second))
					part.push(way[temp]);
			}
		}
		return way[ending].distance;
	}
};
