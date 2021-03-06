#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 105, maxm = 10301, INF = 0x3f3f3f3f;
int N, M, S, T, lev[maxn], lnk[maxn], cur[maxn], dt[maxn];
struct Edge {
	int nxt, v, w;
} e[maxm << 1 | 1];
inline void addEdge(int u, int v, int w)
{
	e[M] = (Edge){lnk[u], v, w};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs()
{
	int L = 0, R = 0;
	static int que[maxn];
	memset(lev, -1, N * sizeof(int));
	lev[S] = 0;
	que[R++] = S;
	while(L < R)
	{
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].w > 0 && lev[e[it].v] == -1)
			{
				lev[e[it].v] = lev[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return lev[T] != -1;
}
int dfs(int u, int upp)
{
	if(u == T) // || !upp
		return upp;
	int ret = 0, tmp;
	for(int &it = cur[u]; it != -1; it = e[it].nxt)
		if(lev[e[it].v] == lev[u] + 1 && e[it].w
		&& (tmp = dfs(e[it].v, std::min(upp - ret, e[it].w))) > 0)
		{
			e[it].w -= tmp;
			e[it ^ 1].w += tmp;
			if((ret += tmp) == upp)
				break;
		}
	if(!ret)
		lev[u] = -1;
	return ret;
}
inline int dinic()
{
	int flow = 0;
	while(bfs())
	{
		memcpy(cur, lnk, N * sizeof(int));
		for(int tmp; (tmp = dfs(S, INF)) > 0; flow += tmp);
	}
	return flow;
}
int main()
{
	int n;
	while(scanf("%d", &n) == 1)
	{
		N = n + 4;
		M = 0;
		S = N - 4;
		T = N - 3;
		memset(lnk, -1, N * sizeof(int));
		memset(dt, 0, N * sizeof(int));
		for(int i = 0; i < n; ++i)
		{
			addEdge(S, i, INF);
			addEdge(i, T, INF);
			int c;
			scanf("%d", &c);
			dt[i] -= c;
			while(c--)
			{
				int j;
				scanf("%d", &j);
				--j;
				++dt[j];
				addEdge(i, j, INF);
			}
		}
		int ctr = 0, SS = N - 2, TT = N - 1, MM = M;
		for(int i = 0; i < N; ++i)
			if(dt[i] > 0)
			{
				ctr += dt[i];
				addEdge(SS, i, dt[i]);
			}
			else if(dt[i] < 0)
				addEdge(i, TT, -dt[i]);
		addEdge(T, S, INF);
		std::swap(S, SS);
		std::swap(T, TT);
		if(dinic() != ctr)
		{
			puts("-1\n");
			continue;
		}
		int flow = e[M - 1].w;
		std::swap(S, SS);
		std::swap(T, TT);
		for( ; MM < M; M -= 2) // destroy edges
		{
			int u = e[M - 1].v, v = e[M - 2].v;
			lnk[u] = e[M - 2].nxt;
			lnk[v] = e[M - 1].nxt;
		}
		std::swap(S, T);
		flow -= dinic(); // old flow - new flow
		printf("%d\n", flow);
	}
	return 0;
}
