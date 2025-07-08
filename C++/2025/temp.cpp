#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAX = 1e5 + 5;

struct SegmentTree {
    int tree[4 * MAX], lazy[4 * MAX];

    void push(int id, int l, int r) {
        if (lazy[id] != 0) {
            tree[id] += lazy[id];
            if (l != r) {
                lazy[id * 2] += lazy[id];
                lazy[id * 2 + 1] += lazy[id];
            }
            lazy[id] = 0;
        }
    }

    void update(int id, int l, int r, int u, int v, int val) {
        push(id, l, r);
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            lazy[id] += val;
            push(id, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, u, v, val);
        update(id * 2 + 1, mid + 1, r, u, v, val);
        tree[id] = max(tree[id * 2], tree[id * 2 + 1]);
    }

    int get_max(int id, int l, int r, int u, int v) {
        push(id, l, r);
        if (v < l || r < u) return LLONG_MIN;
        if (u <= l && r <= v) return tree[id];
        int mid = (l + r) / 2;
        return max(get_max(id * 2, l, mid, u, v),
                   get_max(id * 2 + 1, mid + 1, r, u, v));
    }

    void reset(int n) {
        fill(tree, tree + 4 * n + 5, 0);
        fill(lazy, lazy + 4 * n + 5, 0);
    }
};

int n, m;
struct Query {
    int l, r, x;
} q[MAX];

SegmentTree st;

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> q[i].l >> q[i].r >> q[i].x;
    }

    st.reset(n);

    // Apply all m operations
    for (int i = 0; i < m; ++i) {
        st.update(1, 1, n, q[i].l, q[i].r, q[i].x);
    }

    int ans = LLONG_MAX;
    // Try removing each operation and compute max
    for (int i = 0; i < m; ++i) {
        st.update(1, 1, n, q[i].l, q[i].r, -q[i].x); // undo operation
        int cur_max = st.get_max(1, 1, n, 1, n);
        ans = min(ans, cur_max);
        st.update(1, 1, n, q[i].l, q[i].r, q[i].x); // restore
    }

    cout << ans << "\n";
}
