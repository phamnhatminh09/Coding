//#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int mod = 1e9 + 7;

long long nhan_mod(long long x,long long y) {
    if (y == 1) return x % mod;
    if (y % 2 == 0) return nhan_mod(x * 2 % mod, y / 2) % mod;
    else return ((nhan_mod(x * 2 % mod, y / 2)) % mod + x) % mod;
}

void solve() {
    long long n,q;
    cin >> n >> q;
    long long ghdp, ghtt, ghdt, ghtp, a, b, thct, thcp;
    long long pos;
    long long vtdt, vtdp, vttt, vttp, kq, tt1, tt2;
    for (int i = 1; i <= q; i++) {
        cin >> a >> b;
        ghdp = n - max(a, b);
        ghtt = min(a, b) - 1;
        if(a + b <= n) ghdt = b - 1;
        else ghdt = n - a;
        if(a + b <= n) ghtp = a - 1;
        else ghtp = n - b;
        pos = (a - 1) * n + b;
        vtdt = pos + ghdt * (n - 1);
        vttp = pos - ghtp * (n - 1);
        vtdp = pos + ghdp * (n + 1);
        vttt = pos - ghtt * (n + 1);
        thct = ghdt + ghtp + 1;
        thcp = ghdp + ghtt + 1;
        tt1 = vtdt + vttp;
        tt2 = vtdp + vttt;
        if(thct % 2 == 0) thct /= 2;
        else tt1 /= 2;
        if(thcp % 2 == 0) thcp /= 2;
        else tt2 /= 2;
        kq = (nhan_mod(tt1, thct) + nhan_mod(tt2, thcp) - pos) % mod;
        cout << (kq + mod) % mod << "\n";
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}