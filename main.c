#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "kd_tree.h"

#define N 1000000
#define rand1() (rand() / (double)RAND_MAX)
#define rand_pt(v) { v.x[0] = rand1(); v.x[1] = rand1(); v.x[2] = rand1(); }

int main(void) {
	double best_dist;
	kd_node_t *million, *root;
	kd_node_t *found = NULL;
	kd_node_t testNode;

	million = (kd_node_t*) calloc(N, sizeof(kd_node_t));
	srand(time(0));
	for (int i = 0; i < N; i++) rand_pt(million[i]);

	root = make_tree(million, N, 0, 3);
	rand_pt(testNode);

	found = 0;
	nearest(root, &testNode, 0, 3, &found, &best_dist);

	printf(">> Million tree\nsearching for (%g, %g, %g)\n"
		"found (%g, %g, %g) dist %g\n",
		testNode.x[0], testNode.x[1], testNode.x[2],
		found->x[0], found->x[1], found->x[2],
		sqrt(best_dist));

	free(million);

	return 0;
}
