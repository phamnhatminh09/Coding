#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int m, n;
vector<string> b;

int cntsegment(string row, char color) {
    int cnt = 0;
    bool ins = false;
    for (char c : row) {
        if (c == color) {
            if (!ins) {
                cnt++;
                ins = true;
            }
        }
        else ins = false;
    }
    return cnt;
}

void Solve() {
	cin >> m >> n;
    b.resize(m);
    for (int i = 0; i < m; i++) cin >> b[i];

    int maxseg = 0, brow = -1, bcolor = 'X';

    for (int i = 0; i < m; i++) {
        string modrow = b[i];
        for (char &c : modrow) {
            if (c == 'T') c = 'X';
        }

        int sx = cntsegment(modrow, 'X');
        if (sx > maxseg) {
            maxseg = sx;
            brow = i;
            bcolor = 'X';
        }
    }

    cout << maxseg << endl << brow + 1 << " " << bcolor << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}