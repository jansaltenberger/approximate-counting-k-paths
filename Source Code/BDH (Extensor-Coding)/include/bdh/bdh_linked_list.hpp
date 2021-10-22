/* bdh_linked_list.hpp version 1.0; Jan Saltenberger, August 2021. */

#ifndef __BDH_APROXIMATE_K_PATHS_H__
#define __BDH_APROXIMATE_K_PATHS_H__

#include <stdlib.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

typedef uint64_t set_type;

typedef struct extensor_lnk extensor_lnk;
struct extensor_lnk {
	set_type indices;
	int coef;
	extensor_lnk* next;
};

void destroy(extensor_lnk** e) {
	extensor_lnk* prev;
	if (!e || !*e)
		return;
	prev = *e;
	while (*e) {
		*e = (*e)->next;
		free(prev);
		prev = *e;
	}
}

int count_bits_64(uint64_t v) {
	v = v - ((v >> 1) & (uint64_t)~(uint64_t)0 / 3);
	v = (v & (uint64_t)~(uint64_t)0 / 15 * 3) + ((v >> 2) & (uint64_t)~(uint64_t)0 / 15 * 3);
	v = (v + (v >> 4)) & (uint64_t)~(uint64_t)0 / 255 * 15;
	return (uint64_t)(v * ((uint64_t)~(uint64_t)0 / 255)) >> (sizeof(uint64_t) - 1) * 8;
}

int sign(set_type I, set_type J) {
	unsigned count = 0;
	I >>= 1;
	while (I > 0) {
		count += count_bits_64(I & J);
		I >>= 1;
	}
	return (count % 2 != 0) ? 1 : -1;
}

extensor_lnk* merge(extensor_lnk* left, extensor_lnk* right) {
	extensor_lnk head, * tail, * result;

	tail = &head;
	while (left && right) {
		if (left->indices <= right->indices) {
			tail->next = left;
			left = left->next;
			tail = tail->next;
		}
		else {
			tail->next = right;
			right = right->next;
			tail = tail->next;
		}
	}
	if (left)  tail->next = left;
	if (right) tail->next = right;

	result = head.next;
	return result;
}

extensor_lnk* mergesort(extensor_lnk* head) {
	while (!head || !head->next)
		return head;
	extensor_lnk* slow = head;
	extensor_lnk* fast = head->next;
	while (fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	extensor_lnk* mid = slow->next;
	slow->next = NULL;
	return merge(mergesort(head), mergesort(mid));
}

void simplify(extensor_lnk** head) {
	extensor_lnk* prev, * curr = NULL;
	extensor_lnk* next_next, * next;

	prev = NULL;
	curr = *head;

	while (curr) {
		if (curr->coef == 0) {
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			next = curr->next;
			free(curr);
			curr = next;
		}
		if (curr && curr->next &&
			curr->indices == curr->next->indices)
		{
			curr->coef += curr->next->coef;
			next_next = curr->next->next;
			free(curr->next);
			curr->next = next_next;
		}
		else if (curr) {
			prev = curr;
			curr = curr->next;
		}
	}
}

extensor_lnk* wedge(extensor_lnk* lhs, extensor_lnk* rhs) {
	extensor_lnk res_head, * res_curr;
	extensor_lnk* ei, * ej;
	set_type I, J;

	if (!rhs)
		return NULL;

	res_head.next = NULL;
	res_curr = &res_head;

	ei = lhs;
	ej = rhs;

	while (ei != NULL) {
		while (ej != NULL) {

			I = ei->indices;
			J = ej->indices;
			if (I & J) {
				ej = ej->next;
				continue;
			}
			int p_vec = I | J;
			int c = sign(I, J) * ei->coef * ej->coef;

			res_curr->next = (extensor_lnk*)malloc(sizeof(extensor_lnk));
			res_curr = res_curr->next;
			res_curr->next = NULL;
			res_curr->indices = p_vec;
			res_curr->coef = c;

			ej = ej->next;
		}
		ej = rhs;
		ei = ei->next;
	}
	res_curr = res_head.next;

	if (!res_curr)
		return NULL;

	res_curr = mergesort(res_curr);
	simplify(&res_curr);
	return res_curr;
}

extensor_lnk* add(extensor_lnk* a, extensor_lnk* b) {
	extensor_lnk head, * next, * a_prev;
	head.next = NULL;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;

	head.next = a;
	a_prev = &head;

	while (a && b) {
		if (b->indices < a->indices) {
			a_prev->next = b;
			a_prev = b;
			next = b->next;
			b->next = a;
			b = next;
		}
		else if (b->indices == a->indices) {
			a->coef += b->coef;
			if (a->coef == 0) {
				next = a->next;
				free(a);
				a = next;
				a_prev->next = a;
			}
			next = b->next;
			free(b);
			b = next;
		}
		else if (b->indices > a->indices) {
			a_prev = a;
			a = a->next;
		}
	}
	if (!a)
		a_prev->next = b;
	return head.next;
}

void replace(extensor_lnk* a[],
	extensor_lnk* b[], int n)
{
	for (int i = 0; i < n; ++i) {
		destroy(&a[i]);
		a[i] = b[i];
		b[i] = NULL;
	}
}

extensor_lnk* lifted_bernoulli(int k) {
	extensor_lnk b_head, l_head, * b, * l, * result;
	int i, c;

	b = &b_head;
	l = &l_head;

	for (i = 0; i < k; ++i) {
		c = rand() <= 0.5 * ((double)RAND_MAX + 1.0) ? -1 : 1;
		b->next = (extensor_lnk*)malloc(sizeof(extensor_lnk));
		b = b->next;
		b->indices = 0x1ull << i;
		b->coef = c;

		l->next = (extensor_lnk*)malloc(sizeof(extensor_lnk));
		l = l->next;
		l->indices = 0x1ull << (i + k);
		l->coef = c;
	}
	b->next = NULL;
	l->next = NULL;

	b = b_head.next;
	l = l_head.next;

	result = wedge(b, l);

	destroy(&b);
	destroy(&l);

	return result;
}

uint64_t factorial(unsigned k) {
	uint64_t i, factorial;
	factorial = 1;
	for (i = k; i > 1; --i)
		factorial *= i;
	return factorial;
}

uint64_t run_trial(int*** A, unsigned n, unsigned k) {
	extensor_lnk **B, **v, **tmp;
	extensor_lnk* w;
	unsigned row, col, len;
	uint64_t x, t;

	B   = (extensor_lnk**)malloc(n * sizeof(extensor_lnk*));
	v   = (extensor_lnk**)malloc(n * sizeof(extensor_lnk*));
	tmp = (extensor_lnk**)malloc(n * sizeof(extensor_lnk*));

	for (int i = 0; i < n; ++i) {
		B[i]   = NULL;
		v[i]   = NULL;
		tmp[i] = NULL;
	}

	for (int i = 0; i < n; ++i)
		B[i] = lifted_bernoulli(k);

	x = 0;
	for (int i = 0; i < (k - 1); ++i) {
		for (row = 0; row < n; ++row) {
			len = (*A)[row][0];
			for (col = 1; col <= len; ++col) {
				if (i == 0)
					w = wedge(B[row], B[(*A)[row][col]]);
				else
					w = wedge(B[row], v[(*A)[row][col]]);
				tmp[row] = add(tmp[row], w);
			}
		}
		replace(v, tmp, n);
	}

	for (int i = 0; i < n; ++i) {
		w = v[i];
		int64_t tmp = 0;
		while (w) {
			tmp += w->coef;
			w = w->next;
		}
		x += abs(tmp);
	}

	for (int i = 0; i < n; ++i) {
		destroy(&v[i]);
		destroy(&B[i]);
	}

	free(v);
	free(tmp);
	free(B);

	return x;
}

uint64_t k_paths(int** A, unsigned n, unsigned k, unsigned t) {
	extensor_lnk** B, **v, **tmp;
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

#endif // __APROXIMATE_K_PATHS_H__ 