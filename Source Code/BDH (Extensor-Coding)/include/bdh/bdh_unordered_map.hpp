/* bdh_unordered_map_approx.hpp version 1.0; Jan Saltenberger, August 2021. */

#ifndef __BDH_APROXIMATE_K_PATHS_H__
#define __BDH_APROXIMATE_K_PATHS_H__

#include <cstdint>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>

#include "boost/dynamic_bitset.hpp"

typedef uint64_t bitset;
typedef std::unordered_map<bitset, int> extensor;

int count_bits_64(uint64_t v) {
	v = v - ((v >> 1) & (uint64_t)~(uint64_t)0 / 3);
	v = (v & (uint64_t)~(uint64_t)0 / 15 * 3) + ((v >> 2) & (uint64_t)~(uint64_t)0 / 15 * 3);
	v = (v + (v >> 4)) & (uint64_t)~(uint64_t)0 / 255 * 15;
	return (uint64_t)(v * ((uint64_t)~(uint64_t)0 / 255)) >> (sizeof(uint64_t) - 1) * 8;
}

int sign(bitset I, bitset J) {
	unsigned count = 0;
	I >>= 1;
	while (I > 0) {
		count += count_bits_64(I & J);
		I >>= 1;
	}
	return (count % 2 != 0) ? 1 : -1;
}

void add(extensor& lhs, const extensor& rhs) {
	for (const auto& r : rhs) {
		lhs[r.first] += r.second;
		if (lhs[r.first] == 0)
			lhs.erase(r.first);
	}
}

void wedge(const extensor& lhs, const extensor& rhs, extensor& result) {
	for (auto const& l : lhs)
		for (auto const& r : rhs)
			if (!(l.first & r.first))
				result[l.first|r.first] += sign(l.first, r.first) * l.second * r.second;
}

void lifted_bernoulli(extensor& e, unsigned k) {
	extensor B, L;
	int i, c;

	for (i = 0; i < k; ++i) {
		c = rand() <= 0.5 * ((double)RAND_MAX + 1.0) ? -1 : 1;
		B[0x1ull << i] = c;
		L[0x1ull << (i + k)] = c;
	}
	wedge(B, L, e);
}

uint64_t factorial(unsigned k) {
	uint64_t i, factorial;
	factorial = 1;
	for (i = k; i > 1; --i)
		factorial *= i;
	return factorial;
}

double run_trial(int*** A, unsigned n, unsigned k) {
	std::vector<extensor> B(n), v(n), tmp(n);
	extensor w;
	unsigned i, j, row, col, len;
	double X, t;

	for (i = 0; i < n; ++i)
		lifted_bernoulli(B[i], k);

	X = 0;
	for (i = 0; i < (k - 1); ++i) {
		for (row = 0; row < n; ++row) {
			len = (*A)[row][0];
			for (col = 1; col <= len; ++col) {
				w = extensor();
				if (i == 0)
					wedge(B[row], B[(*A)[row][col]], w);
				else
					wedge(B[row], v[(*A)[row][col]], w);
				add(tmp[row], w);
			}
		}
		v = std::move(tmp);
		tmp = std::vector<extensor>(n);
	}

	for (const auto& e : v) {
		int64_t tmp = 0;
		for (const auto& j : e)
			tmp += j.second;
		X += abs(tmp);
	}
	return X;
}

uint64_t k_paths(int** A, unsigned n, unsigned k, unsigned t) {
	extensor B, v, tmp;
	uint64_t x = 0, x_sum = 0;
	uint64_t k_factorial;

	if (!k || k > n)
		return 0;

	k_factorial = factorial(k);

	for (int i = 1; i < (t + 1); ++i) {
		x_sum += run_trial(&A, n, k);
#ifdef DEBUG
		std::cout << i << "," << (x_sum / (i * k_factorial)) << "\n";
#endif // !DEBUG
	}
	x = x_sum / (t * factorial(k));
	return (uint64_t)(x + 0.5);
}

#endif // __BDH_APROXIMATE_K_PATHS_H__