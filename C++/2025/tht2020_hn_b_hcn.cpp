#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int N;
    cin >> N;
    map<int, vector<int>> xy;

    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        xy[x].push_back(y);
    }

    map<pair<int, int>, int> cnt;

    for (auto& ent : xy) {
        vector<int>& ys = ent.second;
        sort(ys.begin(), ys.end());
        for (int i = 0; i < ys.size(); ++i) {
            for (int j = i + 1; j < ys.size(); ++j) {
                pair<int, int> yp = {ys[i], ys[j]};
                cnt[yp]++;
            }
        }
    }

    long long res = 0;
    for (auto& ent : cnt) {
        long long k = ent.second;
        res += k * (k - 1) / 2;
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