/**
 * Author: adamant
 * Date: 2024-10-24
 * License: CC0
 * Source: https://codeforces.com/blog/entry/13959
 * Description: Builds palindromic tree for a string.
 * Status: stress-tested
 */

namespace PalindromicTree {
const int N = 1e5, sigma = 26;
int s[N], len[N], link[N], to[N][sigma], n, last, sz;
void init() {s[n++] = -1; link[0] = 1; len[1] = -1; sz = 2;}
int get_link(int v) {
    while (s[n - len[v] - 2] != s[n - 1]) v = link[v];
    return v;
}
void add_letter(int c) {
    s[n++] = c; last = get_link(last);
    if (!to[last][c]) {
        len[sz] = len[last] + 2;
        link[sz] = to[get_link(link[last])][c];
        to[last][c] = sz++;
    }
    last = to[last][c];
}
}