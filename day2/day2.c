#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int vstate = 1;
int hstate = 1;
char pad[3][3] = {"123", "456", "789"};

void parse_line(char* line) {
	int i;
	for (i = 0; i < strlen(line); i++) {
		switch (line[i]) {
			case 'R':
				hstate = (hstate != 2) ? hstate + 1 : 2;
				break;
			case 'L':
				hstate = (hstate != 0) ? hstate - 1 : 0;
				break;
			case 'U':
				vstate = (vstate != 0) ? vstate - 1 : 0;
				break;
			case 'D':
				vstate = (vstate != 2) ? vstate + 1 : 2;
				break;
		}
	}
	printf("h %d v %d -- %c\n", hstate, vstate, pad[vstate][hstate]);

}

int main (int argc, char** argv) {

	FILE* fp = fopen("day2-input", "r");
	assert(fp);

	char* line = malloc(0x1000);
	int index = 0;
	int c;
	while((c = getc(fp)) != EOF) {
		if (c == '\n') {
			line[index++] = '\0';
			parse_line(line);
			index = 0;
			memset(line, 0, 0x1000);
		}
		line[index++] =  c;
	}
	if (index) {
		line[index] = '\0';
		parse_line(line);
	}
}