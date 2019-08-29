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
struct node
{
	long long anti, flow, sign;
	node(long a, long b, long c)
	{
		anti = c, flow = b, sign = a;
	}
};
struct rel    //relabel
{
	long long of, high, sign;  //overflow
	friend bool operator<(rel a, rel b) { return a.of < b.of; }
};
struct Highest_relabel_to_front
{
	vector<rel> rel1;
	vector<vector<node>::iterator> parttt;
	vector<vector<node>> flow_map;
	list<rel> ofc[10000]; //overflow_collection
	long node_sum, level, beginning1, ending1; //begin，end给定s，t
	vector<long> height;
	Highest_relabel_to_front(long s = 0, long a = 0, long b = 0) :beginning1(a), ending1(b), rel1(s + 1)
	{
		flow_map.resize(s + 1);
		parttt.resize(s + 1);
		height.resize(s * 2 + 2, 0);
		node_sum = s;
	}
	void relabel(long node_sign)
	{
		long long h = 1000000;
		long floor = rel1[node_sign].high;
		for (auto &p : flow_map[node_sign])
			if (p.flow > 0)
				h = min(rel1[p.sign].high, h);
		rel1[node_sign].high = h + 1;
		height[floor]--, height[h + 1]++;
		if (h > level) level = h;
	}
	void sign_part()
	{
		for (long s = 0; s < rel1.size(); ++s) rel1[s].sign = s;
		for (auto &s : height) s = 0;
		height[node_sum] = 1;
		height[0] = node_sum - 1;
	}
	void initialize_preflow(long beginning)
	{
		for (auto &s : rel1)
		{
			s.high = 0;
			s.of = 0;
		}
		rel1[beginning].high = node_sum;
		for (auto &p : flow_map[beginning])
		{
			flow_map[p.sign][p.anti].flow = p.flow;
			rel1[p.sign].of = p.flow;
			rel1[beginning].of -= p.flow;
			p.flow = 0;
			ofc[rel1[p.sign].high].push_back(rel1[p.sign]);
			if (rel1[p.sign].high > level)
				level = rel1[p.sign].high;
			height[rel1[p.sign].high]++;
		}
	}
	void add_edge(long a, long b, long c)
	{
		if (!flow_map[a].empty())
			for (auto &s : flow_map[a])
				if (s.sign == b)
				{
					s.flow += c;
					return;
				}
		flow_map[a].push_back(node(b, c, flow_map[b].size()));
		flow_map[b].push_back(node(a, 0, flow_map[a].size() - 1));
	}
	void speed_up(long k)
	{
		for (auto &s : rel1)
			if (s.high > k &&s.high < node_sum)
				s.high = node_sum + 1;
	}
	void push(int node_sign)
	{
		while (rel1[node_sign].of > 0 && node_sign != beginning1 && node_sign != ending1)
		{
			auto s = parttt[node_sign];
			if (s == flow_map[node_sign].end())
			{
				relabel(node_sign);
				parttt[node_sign] = flow_map[node_sign].begin();
			}
			else if (s->flow > 0 && rel1[node_sign].high == rel1[s->sign].high + 1)
			{
				if (s->flow > rel1[node_sign].of)
				{
					flow_map[s->sign][s->anti].flow += rel1[node_sign].of;
					s->flow -= rel1[node_sign].of;
					rel1[s->sign].of += rel1[node_sign].of;
					rel1[node_sign].of = 0;
				}
				else
				{
					flow_map[s->sign][s->anti].flow += s->flow;
					rel1[node_sign].of -= s->flow;
					rel1[s->sign].of += s->flow;
					s->flow = 0;
				}
				if (s->sign != beginning1 && s->sign != ending1)
					ofc[rel1[s->sign].high].push_back(rel1[s->sign]);
			}
			else
				parttt[node_sign]++;
		}
	}
	long long max_flow()
	{
		sign_part();
		level = 0;
		for (int i = 0; i < node_sum + 1; ++i)
			parttt[i] = flow_map[i].begin();
		initialize_preflow(beginning1);
		while (level >= 0)
		{
			int level2 = level;
			if (!ofc[level2].empty())
			{
				int s = ofc[level].back().sign;
				ofc[level].pop_back(), push(s);
				if (height[level2] == 0) speed_up(level2);
			}
			else
				level--;
		}
		return rel1[ending1].of;
	}
	void reset()
	{
		parttt.clear();
		height.clear();
		parttt.resize(node_sum + 1);
		height.resize(node_sum * 2 + 2, 0);
	}
	//完全清空
	void reset(int s)
	{
		for (int i = 0; i < node_sum; ++i)
			ofc[i].clear();
		rel1.clear();
		flow_map.clear();
		parttt.clear();
		height.clear();
		rel1.resize(s + 1);
		flow_map.resize(s + 1);
		parttt.resize(s + 1);
		height.resize(s * 2 + 2, 0);
	}
};
const int inf = 0x6fffffff;





