#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("archer.inp", "r", stdin);
#define write freopen("archer.out", "w", stdout);
const ll N = 1e5 + 5;

struct frac {
    long long nume, deno;

    frac(long long num, long long den) {
        long long val = __gcd(abs(num), abs(den));
        nume = num / val;
        deno = den / val;
        if (deno < 0) {
            nume *= -1;
            deno *= -1;
        }
    }

    bool operator<(const frac& ot) const {
        return nume * ot.deno < ot.nume * deno;
    }

    bool operator==(const frac& ot) const {
        return nume == ot.nume && deno == ot.deno;
    }
};

struct pt {
    frac x, y;

    pt(long long xn, long long xd, long long yn, long long yd)
        : x(xn, xd), y(yn, yd) {}

    bool operator<(const pt& ot) const {
        if (x < ot.x) return true;
        if (ot.x < x) return false;
        return y < ot.y;
    }
};

void Solve() {
	int n;
    cin >> n;
    
    vector<tuple<long long, long long, long long>> bal(n);
    for (int i = 0; i < n; ++i) {
        long long x, y, z;
        cin >> x >> y >> z;
        bal[i] = {x, y, z};
    }

    int maxx = 0;
    for (int i = 0; i < n; ++i) {
        auto [xi, yi, zi] = bal[i];
        map<pt, int> cnt;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            
            auto [xj, yj, zj] = bal[j];
            long long dx = xj - xi, dy = yj - yi, dz = zj - zi;
            
            if (dz == 0) continue;
            pt d(dx, dz, dy, dz);
            cnt[d]++;
        }
        
        int curr = 0;
        
        for (auto& [dir, maxx] : cnt) curr = max(curr, maxx);
        maxx = max(maxx, curr + 1);
    }

    cout << maxx;
}

int main() {
	read
	write
    faster
    
    Solve();
    
    return 0;
}