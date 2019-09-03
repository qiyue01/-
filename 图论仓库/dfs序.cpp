/*
array<vector<int>, 310000> edge;
array<int, 310000> B, E, deep, id, ans2;
array<bool, 310000> vis;
vector<tuple<int, int, int> > PP;
int len = 0;
void dfs(int a)
{
	vis[a] = true;
	B[a] = ++len;
	id[len] = a;

	for (auto &p : edge[a])
		if (!vis[p])
			deep[p] = deep[a] + 1, dfs(p);
	E[a] = len;
	PP[a - 1] = make_tuple(B[a], deep[a], 0);
}
*/