#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool isPrime(long long p) {
    if (p <= 1) return false;
    for (long long i = 2; i * i <= p; ++i) {
        if (p % i == 0) return false;
    }
    return true;
}

vector<long long> gen(long long w) {
    vector<long long> perfnum;
    for (int p = 2; ; ++p) {
        long long mersenne = (1LL << p) - 1;
        if (mersenne > w) break;
        if (isPrime(mersenne)) {
            long long perf = (1LL << (p - 1)) * mersenne;
            if (perf > w) break;
            perfnum.push_back(perf);
        }
    }
    return perfnum;
}

void Solve() {
	long long n, w;
    cin >> n >> w;
    vector<long long> a(n + 1), psum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        psum[i] = psum[i - 1] + a[i];
    }

    vector<long long> perfnum = gen(w);
    unordered_set<long long> perfset(perfnum.begin(), perfnum.end());
    unordered_map<long long, int> pcnt;
    pcnt[0] = 1;
    long long cnt = 0;

    for (int i = 1; i <= n; ++i) {
        for (long long num : perfnum) {
            long long x = psum[i] - num;
            if (pcnt.find(x) != pcnt.end()) cnt += pcnt[x];
        }
        pcnt[psum[i]]++;
    }

    cout << cnt;
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}