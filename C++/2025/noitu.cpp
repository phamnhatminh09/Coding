#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	unordered_map<string, int> syl;
    int ncnt = 0;
    
    auto get_id = [&](const string& s) {
        auto it = syl.find(s);
        if (it == syl.end()) {
            syl[s] = ncnt;
            return ncnt++;
        }
        return it -> second;
    };

    int n;
    cin >> n;
    string line;
    getline(cin, line);

    if (n == 0) {
        cout << "Hieu\n";
        return;
    }

    set<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        size_t pos = line.find(' ');
        if (pos == string::npos) continue;
        
        string s1 = line.substr(0, pos), s2 = line.substr(pos + 1);
        edges.insert({get_id(s1), get_id(s2)});
    }

    if (ncnt == 0) {
        cout << "Hieu\n";
        return;
    }

    vector<vector<int>> adj(ncnt);
    vector<int> deg(ncnt, 0);

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adj[v].push_back(u);
        deg[u]++;
    }

    vector<int> stat(ncnt, 0), rem = deg;
    queue<int> q;

    for (int i = 0; i < ncnt; ++i) {
        if (deg[i] == 0) {
            stat[i] = 2;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (stat[v] == 2) {
            for (int u : adj[v]) {
                if (stat[u] == 0) {
                    stat[u] = 1;
                    q.push(u);
                }
            }
        }
        else {
            for (int u : adj[v]) {
                if (stat[u] == 0) {
                    rem[u]--;
                    if (rem[u] == 0) {
                        stat[u] = 2;
                        q.push(u);
                    }
                }
            }
        }
    }

    bool cw = false, cd = false;

    for (const auto& edge : edges) {
        int v = edge.second;
        if (deg[v] > 0) {
            if (stat[v] == 2) {
                cw = true;
                break;
            }
            if (stat[v] == 0) cd = true;
        }
    }

    if (cw) cout << "Quang\n";
    else if (cd) cout << "Hoa\n";
    else cout << "Hieu\n";
}

int main() {
	//read
	//write
    faster
    
    int t;
    cin >> t;
    while (t--) {
        Solve();
    }
    
    return 0;
}