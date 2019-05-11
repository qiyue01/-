/*
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
const int N = 100010;
const long long inf = 1e13;
namespace bf
{
	long long dis[N], iq[N],pre[N];
	vector<pair<int, long long>> edge[N];
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
			pre[v] = u;
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
				if (relax(cur, s.first, s.second) && iq[s.first] == false)
					que.push(s.first), iq[s.first] = 1;
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
const int OUT_LEN = 10000000;

char obuf[OUT_LEN], *oh = obuf;
std::streambuf *fb;

inline void print(char c) {
	oh == obuf + OUT_LEN ? (fb->sputn(obuf, OUT_LEN), oh = obuf) : 0;
	*oh++ = c;
}

template <class T>
inline void print(T x) {
	static int buf[30], cnt;
	if (x == 0)
	{
		print('0');
		return;
	}
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
	while (cnt) print((char)buf[cnt--]);
}

inline void flush() { fb->sputn(obuf, oh - obuf); }
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	fb = cout.rdbuf();
	int n, m, k, u, v, w;
	cin >> n >> m;
	memset(pre, -1, sizeof(pre));
	init();
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> w;
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	bellman_ford(1, n);
	stack<int> ans;
	if (pre[n] == -1)
		print('-'), print(1);
	else
	{
		int k = pre[n];
		ans.push(n);
		while (k != -1)
		{
			ans.push(k);
			k = pre[k];
		}
		while (!ans.empty())
		{
			print(ans.top()), print(' ');
			ans.pop();
		}
	}
	flush();
	return 0;
}
*/