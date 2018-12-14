#include "pch.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define For(a) for(int i=0;i<a;++i)
using namespace std;
const int MAXN = 305;
const int MAXV = 0x3F3F3F3F;
struct mininum_cut{ //���ֻ����1-N�����ø�
	int n, m, v[MAXN], mat[MAXN][MAXN], dis[MAXN];
	bool vis[MAXN];
	int res, s;
	void init(long a, long b)
	{
		n = a, m = b;
		memset(mat, 0, sizeof(mat));
	}
	void add_edge(long i, long j, long k)
	{
		mat[i][j] += k;
		mat[j][i] += k;
	}
	int Stoer_Wagner(int n)
	{
		int i, j;
		int res = MAXV;
		for (i = 0; i < n; i++)
			v[i] = i + 1;//��ʼ����i��������i
		while (n > 1)
		{
			int maxp = 1, prev = 0;
			for (i = 1; i < n; i++) //��ʼ������Ȧ���ϵĸ��С,���ҳ�������Ķ���
			{
				dis[v[i]] = mat[v[0]][v[i]];
				if (dis[v[i]] > dis[v[maxp]])
					maxp = i;
			}
			memset(vis, 0, sizeof(vis));
			vis[v[0]] = true;
			for (i = 1; i < n; i++)
			{
				if (i == n - 1)  //ֻʣ���һ��û���뼯�ϵĵ㣬������С��
				{
					res = min(res, dis[v[maxp]]);
					for (j = 0; j < n; j++)  //�ϲ����һ�����Լ��Ƴ����ļ����еĵ�
					{
						mat[v[prev]][v[j]] += mat[v[j]][v[maxp]];
						mat[v[j]][v[prev]] = mat[v[prev]][v[j]];
					}
					v[maxp] = v[--n];//��maxp���ڵ�ȥ������n���ڵ��ɵ�maxp��
				}
				vis[v[maxp]] = true;
				prev = maxp;
				maxp = -1;
				for (j = 1; j < n; j++)
					if (!vis[v[j]])  //���ϴ����maxp���뼯�ϣ��ϲ��������ڵıߵ��
					{
						dis[v[j]] += mat[v[prev]][v[j]];
						if (maxp == -1 || dis[v[maxp]] < dis[v[j]])
							maxp = j;
					}
			}
		}
		return res;
	}
};
/*
int main()
{
	ios::sync_with_stdio(false);
	long a, b, c;
	long N, M, K;
	mininum_cut p;
	while (cin>>N>>M)
	{
		p.init(N, M);
		For(M)
		{
			cin >> a >> b >> c;
			p.add_edge(a, b, c);
		}
		cout << p.Stoer_Wagner(N) << endl;
	}
}*/
