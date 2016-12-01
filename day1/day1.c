#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
int steps[4] = {0,0,0,0};	/* array of steps in each direction */
int facing = 0;				/* start facing north */

void step(char* directions) {
	if (directions[0] == 'R')
		facing = (facing == 3 ? 0 : facing + 1);
	else if (directions[0] == 'L')
		facing = (facing == 0 ? 3 : facing - 1);

	int walk = atoi(++directions);
	steps[facing] += walk;
}

void print_step_array() {
	int i;
	char card[] = {'N', 'E', 'S', 'W'};
	for (i = 0; i < 4; i++)
		printf("steps in %c: %d\n", card[i], steps[i]);
	printf("total distance: %d\n", abs(steps[0] - steps[2]) + abs(steps[1] - steps[3]));
}

int main (int argc, char** argv) {

	FILE* fp = fopen("day1-input", "r");
	assert(fp);

	char dir[10];
	while(fscanf(fp, "%s, ", &dir) == 1) {
		char* comma = strchr(dir, ',');
		if (comma)
			*comma = '\0';
		step(dir);
	}

	print_step_array();	



}