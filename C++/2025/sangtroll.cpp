#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const int MN = 1e6 + 1;
int isp[MN], p[MN], a[MN], cnt, pdiv[MN];

void sieve (int n) {
    for (int i = 2; i <= n; i++) isp[i] = true;
    isp[0] = false;
    isp[1] = false;
    for (int i = 2; i <= n; i++) {
        if (isp[i]) {
            for (int j = i * 2; j <= n; j += i) isp[j] = false;
        }
    }
    
    cnt = 1;
    for(int i = 2; i <= n; i++) {
        if(isp[i]){
            p[cnt] = i;
            cnt++;
        }
    }
    
    cnt--;
}

int check (long long x) {
    if(x < 2) return 0;
    if(x == 2) return 1;
    long long y = (int)(sqrt(x));
    int temp = lower_bound(p + 1, p + cnt + 1, y) - p;
    //return temp;
    for(int i = 1; i <= temp; i++){
        if(x % p[i] == 0) return 0;
    }
    
    return 1;
}

int cntdiv (long long x) {
    if (x == 1) return int(1);
    if (check(x) == 1) return int(2);
    int c = 1;
    vector<int> vec;
    while (x > 1){
        for (int i = 1; i <= cnt; i++){
            int tmp = 0;
            if (x % p[i] == 0){
                while (x % p[i] == 0){
                    tmp++;
                    x /= p[i];
                }
            }
            vec.push_back(tmp);
        }
    }
    
    for (auto v : vec) c = c * (v + 1);
    return c;
}

void Solve() {
	sieve(3200);
	int n,k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        a[i] = cntdiv(a[i]);
    }
    
    for(int i = 1; i <= n; i++) cout << a[i] << " ";
    
    int ans = INT_MIN;
    for(int i = 1; i <= n; i++) ans = max(ans, a[i]);
    
    for(int i = 1; i <= n; i++){
        if(a[i] == ans) pdiv[i] = pdiv[i - 1] + 1;
        else pdiv[i] = pdiv[i - 1];
    }
    
    int res = INT_MAX;
    for(int i = 1; i <= n; i++){
        int temp = lower_bound(pdiv + 1, pdiv + n + 1, pdiv[i - 1] + k) - pdiv;
        if(temp != (n + 1)) res = min(res, temp - i + 1);
    }
    
    if(res == INT_MAX){
        cout << -1;
        return;
    }
    
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}