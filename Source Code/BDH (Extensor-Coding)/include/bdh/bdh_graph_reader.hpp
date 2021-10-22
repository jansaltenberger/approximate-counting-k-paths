#define BIAS6 63
#define SMALLN 62
#define SMALLISHN 258047
#define TOPBIT6 32

#define SIZELEN(n) ((n)<=SMALLN?1:((n)<=SMALLISHN?4:8))

int graphsize(const char* s) {
    const char* p;
    int n;

    if (s[0] == ':' || s[0] == '&') p = s + 1;
    else                            p = s;

    n = *p++ - BIAS6;

    if (n > SMALLN) {
        n = *p++ - BIAS6;
        if (n > SMALLN) {
            n = *p++ - BIAS6;
            n = (n << 6) | (*p++ - BIAS6);
            n = (n << 6) | (*p++ - BIAS6);
            n = (n << 6) | (*p++ - BIAS6);
            n = (n << 6) | (*p++ - BIAS6);
            n = (n << 6) | (*p++ - BIAS6);
        }
        else {
            n = (n << 6) | (*p++ - BIAS6);
            n = (n << 6) | (*p++ - BIAS6);
        }
    }
    return n;
}

int** bdh_g6tograph(const char* s, int slen, unsigned long* n_out) {
    const char* p;
    int i, j, k, x;
    unsigned long n;
    int** G;

    n = graphsize(s);
    if (n == 0) exit(1);

    G = (int**)calloc(n, sizeof(int*));
    if (G == 0)
        exit(1);
    for (i = 0; i < n; ++i) {
        G[i] = (int*)calloc(n, sizeof(int));
        if (G[i] == 0)
            exit(1);
    }

    p = s + SIZELEN(n);

    k = 0;
    x = *(p++) - BIAS6;
    for (j = 1; j < n; ++j) {
        for (i = 0; i < j; ++i) {
            if (x & (1 << (6 - k - 1))) {
                G[j][++G[j][0]] = i;
                G[i][++G[i][0]] = j;
            }
            k++;
            if (k == 6) {
                x = *(p++) - BIAS6;
                k = 0;
            }
        }
    }
    *n_out = n;
    return G;
}