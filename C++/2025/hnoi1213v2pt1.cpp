#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<long long> gen(int limit = 1000) {
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    set<long long> seen;
    vector<long long> X;
    
    pq.push(3); pq.push(5); pq.push(7);
    seen.insert(3); seen.insert(5); seen.insert(7);

    while (!pq.empty() && X.size() < limit) {
        long long num = pq.top();
        pq.pop();
        X.push_back(num);

        for (int factor : {3, 5, 7}) {
            long long nnum = num * factor;
            if (seen.find(nnum) == seen.end()) {
                seen.insert(nnum);
                pq.push(nnum);
            }
        }
    }
    return X;
}

bool checkx(long long n) {
    if (n == 1) return false;
    while (n % 3 == 0) n /= 3;
    while (n % 5 == 0) n /= 5;
    while (n % 7 == 0) n /= 7;
    return (n == 1);
}

char check(long long n, const vector<long long>& X) {
    auto it = lower_bound(X.begin(), X.end(), n);
    if (it == X.end() || *it != n) return 'K';
    int index = distance(X.begin(), it) + 1;
    return (index % 2 == 1) ? 'L' : 'C';
}

void Solve() {
    vector<ll> x = gen();
    ll n;
    
    while (cin >> n) cout << check(n, x) << '\n';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}
