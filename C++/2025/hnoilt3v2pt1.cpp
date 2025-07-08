#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int maxcnt(int n, int k, vector<pair<int, int>>& tree) {
    sort(tree.begin(), tree.end());
    int maxo = 0, curr = 0, l = 0;
    for (int r = 0; r < n; r++) {
        curr += tree[r].second;
        while (tree[r].first - tree[l].first > k) {
            curr -= tree[l].second;
            l++;
        }
        maxo = max(maxo, curr);
    }

    return maxo + 1;
}

void Solve() {
	int n, k;
    cin >> n >> k;
    vector<pair<int, int>> trees(n);

    for (int i = 0; i < n; i++) cin >> trees[i].second >> trees[i].first;

    cout << maxcnt(n, k, trees);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}