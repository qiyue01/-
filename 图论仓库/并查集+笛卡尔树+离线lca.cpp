struct unionfind
{
	array<int, N> fa, rank;
	unionfind()
	{
		for (int i = 0; i < N; ++i)
			fa[i] = i;
		rank.fill(0);
	}
	void link(int x, int y)
	{
		if (rank[x] > rank[y])
			fa[y] = x;
		else
		{
			fa[x] = y;
			if (rank[x] == rank[y])
				rank[y]++;
		}
	}
	int find(int x)
	{
		if (fa[x] != x)
			fa[x] = find(fa[x]);
		return fa[x];
	}
	void union_(int x, int y)
	{
		link(find(x), find(y));
	}
	void union_normal(int x, int y)
	{
		fa[find(x)] = fa[find(y)];
	}
};
struct graph
{
	vector<int> Begin, to, Next, weight;
	int e;
	void add(int u, int v)
	{
		to[++e] = v;
		Next[e] = Begin[u];
		Begin[u] = e;
	}
	void add(int u, int v, int w)
	{
		to[++e] = v;
		Next[e] = Begin[u];
		Begin[u] = e;
		weight[e] = w;
	}
	graph(int n) :Begin(n * 2, -1), to(n * 2), Next(n * 2), weight(n * 2)
	{
		e = 0;
	}
	void reset()
	{
		fill(Begin.begin(), Begin.end(), -1);
	}
};
graph p(210000), query(1010000);
unionfind un;
int ans[1010000], fa[N];
bitset<N> vis;
void tarjanlca(int cur)
{
	vis[cur] = true;
	for (int i = p.Begin[cur]; i != -1; i = p.Next[i])
	{
		if (vis[p.to[i]] == false)
			fa[p.to[i]] = cur, tarjanlca(p.to[i]);
	}
	un.union_normal(cur, fa[cur]);
	for (int i = query.Begin[cur]; i != -1; i = query.Next[i])
		if (vis[query.to[i]] && ans[query.weight[i]] == 0)
		{
			ans[query.weight[i]] = un.find(query.to[i]);
		}
}
int root;
int arr[N];
void addedge(int u, int v, int s)
{
	if (v)
	{
		p.add(u, v);
		p.add(v, u);
	}
}
inline void build(int *a, int n) {
	static int stack[N], u, pre;
	int top = 0;
	for (register int i = 1; i <= n; i++) {
		u = i;
		pre = 0;
		while (top && a[stack[top]] > a[i]) {
			pre = stack[top];
			stack[top--] = 0;
		}
		if (top)
			addedge(stack[top], u, 1);
		addedge(u, pre, 0);
		stack[++top] = u;
	}
	root = stack[1];
}