#ifndef KD_TREE_H_
#define KD_TREE_H_

#ifndef MAX_DIM
#	define MAX_DIM 3
#endif

typedef struct kd_node_t {
	double x[MAX_DIM];
	struct kd_node_t *left, *right;
} kd_node_t;

double dist(kd_node_t *a, kd_node_t *b, int dim);
kd_node_t* find_median(kd_node_t *start, kd_node_t *end, int idx);
kd_node_t* make_tree(kd_node_t *t, int len, int i, int dim);
void nearest(kd_node_t *root, kd_node_t *nd, int i, int dim,
		kd_node_t **best, double *best_dist);
#endif // KD_TREE_H_
