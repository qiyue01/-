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
bool trans[maxn];
int randd = 1;
long long curd[maxn];
class dijkstra
{
public:
	struct node
	{
		long long distance;
		int father;
		int sign, cnt;
		friend bool operator >(node a, node b)
		{
			return b.distance > a.distance;
		}
		friend bool operator <(node a, node b)
		{
			return b.distance < a.distance;
		}
	};
	vector<pair<pair<int, int>, int> > G[maxn];
	priority_queue<node> part;
	vector<node> way;
	void set(long i)
	{
		way.resize(i + 1);
	}
	void insert(long u, long v, int w, int s)
	{
		G[u].push_back({ make_pair(v, w),s });
	}
	bool relax(long u, long v, long long w, bool s)
	{
		if (way[v].distance > way[u].distance + w)
		{
			way[v].distance = way[u].distance + w;
			way[v].father = u;
			curd[v] = way[v].distance;
			trans[v] = s;
			return true;
		}
		else if ((way[v].distance == way[u].distance + w && s == false))
		{
			trans[v] = s;
			return false;
		}
		return false;
	}
	void shortest_path(long beginning)
	{
		for (long i = 0; i < way.size(); ++i)
		{
			way[i].distance = 0x3f3f3f3f3f3f3f;
			way[i].father = -1;
			way[i].sign = i;
			way[i].cnt = 0;
			curd[i] = 0x3f3f3f3f3f3f3f;
		}
		bool flag = false;
		way[beginning].distance = 0;
		part.push(way[beginning]);
		while (!part.empty())
		{
			node part2 = part.top();
			part.pop();
			if (curd[part2.sign] < part2.distance)
				continue;
			for (int i = 0; i < G[part2.sign].size(); ++i)
			{
				int temp = G[part2.sign][i].first.first;
				if (relax(part2.sign, temp, G[part2.sign][i].first.second, G[part2.sign][i].second))
				{
					part.push(way[temp]);
				}
			}
		}
	}
}dj;