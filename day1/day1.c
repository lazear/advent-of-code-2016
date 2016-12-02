#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

struct stops {
	int steps[4];
} *all_stops;


int steps[4] = {0,0,0,0};	/* array of steps in each direction */
int facing = 0;				/* start facing north */
int nstop = 0;

void print_step_array(int array[4]) {
	int i;
	char card[] = {'N', 'E', 'S', 'W'};
	for (i = 0; i < 4; i++)
		printf("%c: %d\t", card[i], array[i]);
	printf("total distance: %d\n", abs(array[0] - array[2]) + abs(array[1] - array[3]));
}


int check_and_add(int this_stop[4]) {
	int i;
	int ns_this = this_stop[0] - this_stop[2];
	int ew_this = this_stop[1] - this_stop[3];

	for(i = 0; i < nstop; i++) {

		int ns_iter = all_stops[i].steps[0] - all_stops[i].steps[2];
		int ew_iter = all_stops[i].steps[1] - all_stops[i].steps[3];
		if ((ns_iter == ns_this) && (ew_iter == ew_this)) {
			printf("MATCH!\n");
			print_step_array(all_stops[i].steps);
			print_step_array(this_stop);
		}
		else if ((abs(ns_iter) + abs(ew_iter)) ==  (abs(ns_this) + abs(ew_this))) {
			print_step_array(all_stops[i].steps);
			print_step_array(this_stop);
		}
	}
	memcpy((void*) all_stops[nstop++].steps, (void*) this_stop, sizeof(int) * 4);
}


void step(char* directions) {
	if (directions[0] == 'R')
		facing = (facing == 3 ? 0 : facing + 1);
	else if (directions[0] == 'L')
		facing = (facing == 0 ? 3 : facing - 1);
	steps[facing] += atoi(++directions);
	check_and_add(steps);
}


int main (int argc, char** argv) {

	FILE* fp = fopen("day1-input", "r");
	assert(fp);

	all_stops = malloc(sizeof(struct stops) * 200);

	char dir[10];
	while(fscanf(fp, "%s, ", &dir) == 1) {
		char* comma = strchr(dir, ',');
		if (comma)
			*comma = '\0';
		step(dir);
	}
	print_step_array(all_stops[0].steps);	
	free(all_stops);


}