/*
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <random>
#include <map>
#include <set>
#include <deque>
#include <iomanip>
#include <sstream>
#include <stack>
#include <iostream>
#include <limits>
#include <bitset>
#include <list>
#include <queue>
#include <memory>
#include <functional>
#include<cstdio>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/exception.hpp>
#include<ext/pb_ds/list_update_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#include<ext/pb_ds/tag_and_trait.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
# define maxn 6000000+10
using namespace std;
int head[maxn];
int vis[maxn];
int num;
struct node
{
	int ne;
	int to;
	int co;
} q[maxn];

void add(int u, int v, int w)
{
	q[++num].ne = head[u];
	q[num].to = v;
	q[num].co = w;
	head[u] = num;
}
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
	vector<node> way;
	vector<__gnu_pbds::priority_queue<node>::point_iterator> Iter;
	void set(long i)
	{
		way.resize(i + 1);
		Iter.resize(i + 1);
	}
	void insert(long u, long v, long w)
	{
		add(u, v, w);
	}
	bool relax(long u, long v, long w)
	{
		if (way[v].distance > way[u].distance + w)
		{
			way[v].distance = way[u].distance + w;
			return true;
		}
		return false;
	}
	long shortest_path(long beginning, long ending)
	{
		for (long i = 0; i < way.size(); ++i)
		{
			way[i].distance = 110000000000;
			way[i].father = -1;
			way[i].sign = i;
		}
		way[beginning].distance = 0;
		__gnu_pbds::priority_queue<node, greater<node>> part;
		part.push(way[beginning]);
		while (part.size() != 0)
		{
			node part2 = part.top();
			part.pop();
			for (int i = head[part2.sign]; i != -1; i = q[i].ne)
			{
				int temp = q[i].to;
				if (relax(part2.sign, temp, q[i].co))
					if (Iter[temp] == NULL)
						Iter[temp] = part.push(way[temp]);
					else
						part.modify(Iter[temp], way[temp]);
			}
		}
		return way[ending].distance;
	}
};
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch<'0' || ch>'9') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch >= '0'&&ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int main()
{
	int n, m, k, u, v, c, T;
	T = read();
	while (T--)
	{
		memset(head, -1, sizeof(head));
		n = read(), m = read(), k = read();
		dijkstra part;
		part.set(n*(k + 2) + 10);
		for (int i = 0; i < m; ++i)
		{
			u = read();
			v = read();
			c = read();
			part.insert(u, v, c);
			if (k > 0)
				for (int j = 1; j <= k; ++j)
				{
					part.insert(n*(j - 1) + u, n*j + v, 0);
					part.insert(n*j + u, n*j + v, c);
				}
		}
		printf("%llu\n", part.shortest_path(1, n + n * k));
	}
	return 0;
}
*/
