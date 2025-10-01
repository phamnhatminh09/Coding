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
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

static ll cnt(ll h){
    if(h <= 1) return 0;
    ll l = 0, r = 1;
    
    while ((__int128)r * (r + 1) / 2 < h) r <<= 1;
    while (l < r){
        ll m = (l + r + 1) >> 1;
        
        if ((__int128)m * (m + 1) / 2 < h) l = m;
        else r = m - 1;
    }
    
    return l;
}

static ll maxdist(ll h, ll br){
    ll dist = 0, x = br + 1;
    
    while (x > 0){
        ll t = cnt(h);
        
        if (t == 0){
            h += 1;
            --x;
            continue;
        }
        
        if (t == 1){
            if (h > 1){
                dist += x;
                break;
            }
            else {
                h += 1;
                --x;
                continue;
            }
        }
        
        ll S = t * (t + 1) / 2, maxk;
        if (S == 1) maxk = x - 1;
        else {
            ll num = h - S - 1, denom = S - 1;
            
            if (num < 0) maxk = -1;
            else maxk = num / denom;
        }
        
        ll check = maxk + 1;
        if (check <= 0){
            dist += t;
            h -= (S - 1);
            --x;
        }
        else {
            ll m = min(x, check);
            dist += m * t;
            h -= m * (S - 1);
            x -= m;
        }
    }
    
    return dist;
}

void Solve() {
	int t;
    if(!(cin >> t)) return ;
    
    while (t--){
        ll h, d;
        cin >> h >> d;
        
        ll l = 0, r = d;
        while (l < r){
            ll m = (l + r) >> 1;
            if (maxdist(h, m) >= d) r = m;
            else l = m + 1;
        }
        
        cout << d + l << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}