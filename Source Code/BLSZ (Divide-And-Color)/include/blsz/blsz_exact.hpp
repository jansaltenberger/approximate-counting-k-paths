// exact_k_paths.hpp version 1.0; Jan Saltenberger, August 2021.

#ifndef __BLSZ_EXACT_K_PATHS_H__
#define __BLSZ_EXACT_K_PATHS_H__

#include <cmath>
#include <cstdint>
#include <vector>

#include "boost/dynamic_bitset.hpp"
#include "boost/multiprecision/cpp_int.hpp"

typedef boost::dynamic_bitset<> bitset;
typedef std::vector<uint64_t> alpha_t;

using namespace boost::multiprecision;

cpp_int nCr(cpp_int n, cpp_int r) {
    cpp_int result = 1;
    for (cpp_int i = n - r + 1; i <= n; ++i)
        result *= i;
    for (cpp_int i = 2; i <= r; ++i)
        result /= i;
    return result;
}

bitset decode_p_set(uint64_t n, cpp_int p, cpp_int ordinal) {
    bitset bits(n);
    for (uint64_t bit = n; p > 0; --bit) {
        cpp_int nCk = nCr(bit, p);
        if (ordinal >= nCk) {
            ordinal -= nCk;
            bits[bit] = 1;
            --p;
        }
    }
    return bits;
}

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

        bitset f;
        cpp_int ordinal = nCr(n, p);
        while (ordinal-- > 0) {
            f = decode_p_set(n, p, ordinal);

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
        }
        return alpha_out;
    }
}

uint64_t k_paths(int** A, unsigned n, unsigned k) {
    if (!k || (k > n))
        return 0;

    unsigned s = n + 1;

    alpha_t alpha(s);
    alpha[n] = 1;

    bitset G(s);
    G.set();
    G[n] = 0;

    alpha = k_paths_rec(A, s, G, k, alpha);
    uint64_t result = 0;
    for (unsigned i = 0; i < n; ++i)
        result += alpha[i];

    return result;
}

#endif // __BLSZ_EXACT_K_PATHS_H__