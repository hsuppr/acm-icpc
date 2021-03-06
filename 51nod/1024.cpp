#include <cmath>
#include <stdio.h>
#include <algorithm>
const int maxd = 9, INF = (int)2e4;
int Gcd[maxd][maxd], xLow, xUpp, yLow, yUpp;
int dfs(int x, int prd) {
	if(prd > yUpp)
		return 0;
	if(x == xUpp)
		return yUpp / prd - (yLow - 1) / prd;
	int rem = prd % x;
	return rem ? dfs(x + 1, prd) - dfs(x + 1, prd * (x / Gcd[rem][x])) : 0;
}
int solve(int xL, int xR, int yL, int yR) {
	int ret = (xR - xL + 1) * (yR - yL + 1);
	for(xLow = xL; xLow < xR; ++xLow)
		for(xUpp = xLow + 1; xUpp <= xR; ++xUpp) {
			yLow = yL * xUpp;
			yUpp = yR * xLow;
			bool chk = yLow <= yUpp;
			int prd = xLow * (xUpp / Gcd[xLow][xUpp]);
			for(int i = xLow + 1; chk && i < xUpp; ++i)
				chk &= prd % i > 0;
			if(chk)
				ret -= dfs(xLow + 1, prd);
		}
	return ret;
}
int tot, pL[maxd], pR[maxd], low[maxd], upp[maxd], pos[maxd << 1 | 1], tp[maxd], sp[maxd << 1 | 1];
int iPow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = x * x)
		(k & 1) && (ret = ret * x);
	return ret;
}
int iRoot(int x, int k) {
	int ret = (int)ceil(pow(x, 1.0 / k));
	for( ; pow(ret, k) <= INF && iPow(ret, k) <= x; ++ret);
	for( ; pow(ret, k) > INF || iPow(ret, k) > x; --ret);
	return ret;
}
int main() {
	int mx, xL, xR, yL, yR;
	scanf("%d%d%d%d", &yR, &xR, &xL, &yL);
	xR += xL - 1;
	yR += yL - 1;
	pos[tot++] = 1;
	for(mx = 1; 1 << mx <= xR; ++mx) {
		pos[tot++] = low[mx] = iRoot(xL - 1, mx);
		pos[tot++] = upp[mx] = iRoot(xR, mx);
		Gcd[0][mx] = Gcd[mx][0] = mx;
	}
	std::sort(pos, pos + tot);
	tot = std::unique(pos, pos + tot) - pos;
	for(int i = 1; i < tot; ++i) {
		pL[i] = maxd;
		pR[i] = 0;
		int len;
		for(len = 1; 1 << len <= pos[i]; ++len)
			tp[len] = iRoot(pos[i], len) - 1;
		for(int j = len - 1; j >= 1; --j)
			for(int k = j + j; k < len; k += j)
				tp[j] -= tp[k];
		sp[i] = tp[1];
	}
	for(int i = 1; i < mx; ++i) {
		int sta = std::lower_bound(pos, pos + tot, low[i]) - pos + 1;
		int end = std::lower_bound(pos, pos + tot, upp[i]) - pos + 1;
		for( ; sta < end; ++sta) {
			pL[sta] = std::min(pL[sta], i);
			pR[sta] = std::max(pR[sta], i);
		}
		for(int j = i; j < mx; ++j)
			Gcd[i][j] = Gcd[j][i] = Gcd[i][j - i];
	}
	int ans = 0;
	for(int i = 1; i < tot; ++i)
		if(pL[i] <= pR[i])
			ans += (sp[i] - sp[i - 1]) * solve(pL[i], pR[i], yL, yR);
	printf("%d\n", ans);
	return 0;
}
