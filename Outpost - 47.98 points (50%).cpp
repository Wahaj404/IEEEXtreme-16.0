#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;
using vl = vector<ll>;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vi = vector<int>;
using vs = vector<string>;
using vb = vector<bool>;
using vvb = vector<vb>;
const ll mod = 998244353;
const ll INF = ll(1e16);
#define in(File) freopen(File, "r", stdin);
#define out(File) freopen(File, "w", stdout);

int lookup[10][50000][17], lookup2[10][50000][17];
 
void buildSparseTableMin(int row, vector<int> arr, int n)
{
    for (int i = 0; i < n; i++)
        lookup[row][i][0] = arr[i];
 
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
 
            if (lookup[row][i][j - 1] <
                        lookup[row][i + (1 << (j - 1))][j - 1])
                lookup[row][i][j] = lookup[row][i][j - 1];
            else
                lookup[row][i][j] =
                         lookup[row][i + (1 << (j - 1))][j - 1];
        }
    }
}

void buildSparseTableMax(int row, vector<int> arr, int n)
{
    for (int i = 0; i < n; i++)
        lookup2[row][i][0] = arr[i];
 
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
 
            if (lookup2[row][i][j - 1] <
                        lookup2[row][i + (1 << (j - 1))][j - 1])
                lookup2[row][i][j] = lookup2[row][i + (1 << (j - 1))][j - 1];
            else
                lookup2[row][i][j] =
                         lookup2[row][i][j - 1];
        }
    }
}
 
int queryMin(int row, int L, int R)
{
    int j = (int)log2(R - L + 1);
 
    if (lookup[row][L][j] <= lookup[row][R - (1 << j) + 1][j])
        return lookup[row][L][j];
 
    else
        return lookup[row][R - (1 << j) + 1][j];
}

int queryMax(int row, int L, int R)
{
    int j = (int)log2(R - L + 1);
 
    if (lookup2[row][L][j] >= lookup2[row][R - (1 << j) + 1][j])
        return lookup2[row][L][j];
 
    else
        return lookup2[row][R - (1 << j) + 1][j];
}

void solve(int test) {
    int n, m, t;
    cin >> n >> m >> t;
    // n < m, n <= 10, m <= 5000
    vector<vector<int>> a(n, vector<int> (m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j)
            cin >> a[i][j];
    }

    if (n == 1) {
        int result = 0;
        for(int i = 0; i < n; ++i) {
            buildSparseTableMin(i, a[i], a[i].size());
            buildSparseTableMax(i, a[i], a[i].size());
        }
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < i; ++j) {
                int max_perimeter = queryMax(0, j, i);
                int min_perimeter = queryMin(0, j, i);
                if (max_perimeter - min_perimeter <= t) {
                    result = max(result, i - j + 1);
                }
            }
        }
        cout << result << "\n";
        return;
    }

    int mx[m][n][n], mn[m][n][n];
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            mx[i][j][j] = a[j][i];
            mn[i][j][j] = a[j][i];
            for(int k = j + 1; k < n; ++k) {
                mx[i][j][k] = max(a[k][i], mx[i][j][k-1]);
                mn[i][j][k] = min(a[k][i], mn[i][j][k-1]);
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        buildSparseTableMin(i, a[i], a[i].size());
        buildSparseTableMax(i, a[i], a[i].size());
    }
    int result = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < i; ++k) {
                int lo = 0, hi = j - 1;
                while (lo < hi) {
                    int mid = (lo + hi) >> 1;

                    int max_perimeter = max(mx[j][k][i], mx[mid][k][i]);
                    
                    max_perimeter = max(max_perimeter, queryMax(i, mid, j));
                    max_perimeter = max(max_perimeter, queryMax(k, mid, j));
                    
                    int max_outpost = 0;
                    for(int it = k; it <= i; ++it) {
                        max_outpost = max(max_outpost, queryMax(it, mid, j));
                    }
                    if (max_perimeter == max_outpost) {
                        int min_outpost = INT_MAX;
                        for(int it = k; it <= i; ++it) {
                            min_outpost = min(min_outpost, queryMin(it, mid, j));
                        }
                        if (max_outpost - min_outpost <= t) {
                            hi = mid;
                        } else {
                            lo = mid + 1;
                        }
                    } else {
                        lo = mid + 1;
                    }
                }
                // if (i==2 && k==0 && j==4) {
                //     cout << lo << "\n";
                // }
                // for(int l = 0; l < j; ++l) {
                    
                // }
                int max_perimeter = max(mx[j][k][i], mx[lo][k][i]);
                    
                max_perimeter = max(max_perimeter, queryMax(i, lo, j));
                max_perimeter = max(max_perimeter, queryMax(k, lo, j));
                
                int max_outpost = 0;
                for(int it = k; it <= i; ++it) {
                    max_outpost = max(max_outpost, queryMax(it, lo, j));
                }
                if (max_perimeter == max_outpost) {
                    int min_outpost = INT_MAX;
                    for(int it = k; it <= i; ++it) {
                        min_outpost = min(min_outpost, queryMin(it, lo, j));
                    }
                    if (max_outpost - min_outpost <= t) {
                        result = max(result, (i - k + 1) * (j - lo + 1));
                    }
                }
            }
        }
    }
    cout << result << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
        in("input.txt");
    #endif

    bool mt =false;
    int tests = 1;
    if (mt) cin >> tests;
    for(int tt = 1; tt <= tests; ++tt)
        solve(tt);
    return 0;
}