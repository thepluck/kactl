/**
 * Author: minhnhatnoe
 * Date: 2022-11-12
 * License: CC0
 * Source: minhnhatnoe and tuanlinh123
 * Description: Suffix Automaton, supporting multiple strings.
 * The beginning iterator is $0$. Make calls to itmove to progress iterator.
 * Time: O(n)
 * Status: stress-tested
 */

struct SuffixAutomaton{
    struct Node{
        int len, link = -1, nxt[26];
        Node(int len): len(len) {fill(nxt, nxt + 26, -1);}
        Node(int len, int link, int _nxt[26]):
        len(len), link(link) {memcpy(nxt, _nxt, sizeof nxt);}
    };
    vector<Node> g = {0};
    int ptrans(int p, char c, int nxt) {
        for (int q = g[p].nxt[c]; p != -1 && g[p].nxt[c] == q;
            p = g[p].link) g[p].nxt[c] = nxt;
        return p;
    }
    int fbuild(int p, char c) {
        if (p == -1) return 0;
        int q = g[p].nxt[c];
        if (g[p].len + 1 == g[q].len) return q;
        int qc = g.size();
        g.emplace_back(g[p].len+1, g[q].link, g[q].nxt);
        ptrans(p, c, qc); return g[q].link = qc;
    }
    int addc(int p, char c) { // Progress iterator
        if (g[p].nxt[c] != -1) return fbuild(p, c);
        int nc = g.size();
        g.emplace_back(g[p].len+1);
        int r = fbuild(ptrans(p, c, nc), c);
        g[nc].link = r; return nc;
    }
};