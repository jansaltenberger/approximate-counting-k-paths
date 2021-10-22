// exact_k_paths.hpp version 1.0; Jan Saltenberger, August 2021.

#ifndef __BLSZ_APPROXIMATE_K_PATHS_H__
#define __BLSZ_APPROXIMATE_K_PATHS_H__

#include <cstdint>
#include <vector>

#include "boost/dynamic_bitset.hpp"

typedef boost::dynamic_bitset<> bitset;
typedef std::vector<uint64_t> alpha_t;

alpha_t k_paths_rec(int** A, unsigned n, bitset G,
    unsigned k, alpha_t alpha)
{
    if (k == 1) {
        for (unsigned u = 0; u < n; ++u) {
            for (unsigned i = 1; i <= A[u][0] ; ++i) {
                unsigned v = A[u][i];
                if (!G[u] && G[v])
                    alpha[v] += alpha[u];
            }
        }
        return alpha;
    }
    else {
        alpha_t alpha_out(n);

        unsigned p =  ceil(k / 2.0);
        unsigned q = floor(k / 2.0);

        double prob = static_cast<double>(p) / k;

        bitset f(n);

        for (int i = 0; i < (n-1); ++i)
            if (rand() <= prob * ((double)RAND_MAX + 1.0))
                f[i] = 1;

        bitset intersection_f_G = f & G;
        bitset difference_G_f = G & ~f;

        for (unsigned i = 0; i < n; ++i) {
            if (difference_G_f[i])
                alpha[i] = 0;
        }

        alpha_t aF_hat = k_paths_rec(A, n,
            intersection_f_G, p, alpha);

        for (unsigned i = 0; i < n; ++i) {
            if (!G[i])
                aF_hat[i] = 0;
        }

        alpha_t aF = k_paths_rec(A, n,
            difference_G_f, q, aF_hat);

        for (unsigned i = 0; i < n; ++i) {
            if (difference_G_f[i])
                alpha_out[i] += aF[i];
        }
        for (int i = 0; i < n; ++i)
            alpha_out[i] /= ((pow(p, p) * pow(q, q)) / pow(k, k));
        return alpha_out;
    }
}

uint64_t k_paths(int** A, unsigned n, unsigned k, unsigned t) {
    if (!k || (k > n))
        return 0;

    unsigned s = n + 1;

    uint64_t x = 0, x_sum = 0;

    for (int i = 1; i <= t; ++i) {
        alpha_t alpha(s);
        alpha[n] = 1;

        bitset G(s);
        G.set();
        G[n] = 0;

        alpha = k_paths_rec(A, s, G, k, alpha);
        uint64_t result = 0;
        for (unsigned j = 0; j < n; ++j)
            result += alpha[j];

        x_sum += result;

#ifdef DEBUG
        std::cout << i << "," << (x_sum / i) << "\n";
#endif // !DEBUG
    }
    x = x_sum / t;
    return (uint64_t)(x + 0.5);
}
#endif // __BLSZ_EXACT_K_PATHS_H__