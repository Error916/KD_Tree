#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kd_tree.h"

inline void swap(kd_node_t *x, kd_node_t *y) {
	double tmp[MAX_DIM];
	memcpy(tmp,  x->x, sizeof(tmp));
	memcpy(x->x, y->x, sizeof(tmp));
	memcpy(y->x, tmp,  sizeof(tmp));
}

inline double dist(kd_node_t *a, kd_node_t *b, int dim) {
	double t;
	double d = 0.0;
	while (dim--) {
		t = a->x[dim] - b->x[dim];
		d += t * t;
	}
	return d;
}

// quickselect method
kd_node_t* find_median(kd_node_t *start, kd_node_t *end, int idx) {
	if (end <= start) return NULL;
	if (end == start + 1) return start;

	kd_node_t *p, *store;
	kd_node_t *md = start + (end - start) / 2;
	double pivot;
	while (1) {
		pivot = md->x[idx];

		swap(md, end - 1);
		for (store = p = start; p < end; ++p) {
			if (p->x[idx] < pivot) {
				if (p != store) swap(p, store);
				++store;
			}
		}

		swap(start, end - 1);

		// median has duplicate values
		if (store->x[idx] == md->x[idx]) return md;

		if (store > md) end = store;
		else start = store;
	}
}

kd_node_t* make_tree(kd_node_t *t, int len, int i, int dim) {
	kd_node_t *n;

	if (!len) return NULL;

	if ((n = find_median(t, t + len, i))) {
		i = (i + 1) % dim;
		n->left  = make_tree(t, n - t, i, dim);
        	n->right = make_tree(n + 1, t + len - (n + 1), i, dim);
	}

	return n;
}

void nearest(kd_node_t *root, kd_node_t *nd, int i, int dim,
		kd_node_t **best, double *best_dist) {
	double d, dx, dx2;

	if (!root) return;
	d = dist(root, nd, dim);
	dx = root->x[i] - nd->x[i];
	dx2 = dx * dx;

	if (!*best || d < *best_dist) {
		*best_dist = d;
		*best = root;
	}

	// if chance of exact match is high
	if (!*best_dist) return;

	if (++i >= dim) i = 0;

	nearest(dx > 0 ? root->left : root->right, nd, i, dim, best, best_dist);
	if (dx2 >= *best_dist) return;
	nearest(dx > 0 ? root->right : root->left, nd, i, dim, best, best_dist);
}
