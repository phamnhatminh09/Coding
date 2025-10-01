#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const ll oo = 1e18;

void Solve() {
	
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}

/*#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

void solve() {
    int n;
    std::cin >> n;
    std::string a, b;
    std::cin >> a >> b;

    std::vector<long long> pa(n + 1, 0);
    std::vector<long long> pb(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        pa[i + 1] = pa[i] + (a[i] - '0');
        pb[i + 1] = pb[i] + (b[i] - '0');
    }

    int offset = n;
    int g_size = 2 * n + 2;
    std::vector<long long> count_g(g_size, 0);
    std::vector<long long> sum_pb_g(g_size, 0);
    std::vector<long long> sum_y_minus_pb_g(g_size, 0);

    for (int y = 1; y <= n; ++y) {
        long long g_val = 2 * pb[y] - y;
        int idx = g_val + offset;
        count_g[idx]++;
        sum_pb_g[idx] += pb[y];
        sum_y_minus_pb_g[idx] += y - pb[y];
    }
    
    std::vector<long long> pref_count_g(g_size, 0);
    std::vector<long long> pref_sum_pb_g(g_size, 0);
    std::vector<long long> pref_sum_y_minus_pb_g(g_size, 0);

    pref_count_g[0] = count_g[0];
    pref_sum_pb_g[0] = sum_pb_g[0];
    pref_sum_y_minus_pb_g[0] = sum_y_minus_pb_g[0];

    for (int i = 1; i < g_size; ++i) {
        pref_count_g[i] = pref_count_g[i - 1] + count_g[i];
        pref_sum_pb_g[i] = pref_sum_pb_g[i - 1] + sum_pb_g[i];
        pref_sum_y_minus_pb_g[i] = pref_sum_y_minus_pb_g[i - 1] + sum_y_minus_pb_g[i];
    }

    long long total_sum_y_minus_pb = pref_sum_y_minus_pb_g.back();
    long long total_f = 0;

    for (int x = 1; x <= n; ++x) {
        long long k_x = (long long)x - 2 * pa[x];
        int k_idx = k_x + offset;

        long long count_le = pref_count_g[k_idx];
        long long sum_pb_le = pref_sum_pb_g[k_idx];
        
        long long count_gt = n - count_le;
        long long sum_y_minus_pb_gt = total_sum_y_minus_pb - pref_sum_y_minus_pb_g[k_idx];

        long long sum_x = 0;
        sum_x += count_le * pa[x] + sum_pb_le;
        sum_x += count_gt * (x - pa[x]) + sum_y_minus_pb_gt;
        
        total_f += sum_x;
    }

    std::cout << total_f << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}*/