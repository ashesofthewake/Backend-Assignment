#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define vll vector<ll>
#define N 1000005

ll arrival[N], departure[N], vis[N], parent[N];
vector<pair<ll, ll>> g[N];
set<ll> cache[N];
ll n, m;

void dijkstra()
{
	for(int i = 1; i <= n; i++)
	{
		arrival[i] = 1e18;
		departure[i] = 1e18;
		vis[i] = 0;
	}
	arrival[1] = 0;
	set<pair<int, int>> s;
	s.insert({0, 1});
	while(!s.empty())
	{
		auto x = *(s.begin());
		s.erase(x);
		vis[x.second] = 1;
		ll prev = arrival[x.second];
		auto it = cache[x.second].lower_bound(prev);
		while(it != cache[x.second].end() and *it == prev) {
			it++;
			prev++;
		}
		departure[x.second] = prev;
		for(auto it: g[x.second])
		{
			if(arrival[it.first] > departure[x.second] + it.second)
			{
				s.erase({arrival[it.first], it.first});
				arrival[it.first] = departure[x.second] + it.second;
				s.insert({arrival[it.first], it.first});
				parent[it.first] = x.second;
			}
		}
	}
}


void solve()
{
   cin >> n >> m;
   for(int i = 0; i < m; i++) {
   	    ll u, v, w; cin >> u >> v >> w;
   	    g[u].push_back({v, w});
   	    g[v].push_back({u, w});
   }
   for(int i = 1; i <= n; i++) {
   	    ll k; cin >> k;
   	    for(int j = 0; j < k; j++) {
   	    	ll x; cin >> x;
   	    	cache[i].insert(x);
   	    }
   }
   dijkstra();
   cout << arrival[n] << endl;
}


signed main()
{
   std::ios::sync_with_stdio(false);
   int T=1;
   //cin>>T;
   // cin.ignore(); must be there when using getline(cin, s)
   while(T--)
   {
      solve();
   }
   return 0;
}
