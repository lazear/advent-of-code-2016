#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int vstate = 2;
int hstate = 0;
char pad[5][5] = {"  1  ", " 234 ", "56789", " ABC ", "  D  " };

void parse_line(char* line) {
	int i;
	int h = 0; 
	int v = 0;

	for (i = 0; i < strlen(line); i++) {
		switch (line[i]) {
			case 'R':
				if (vstate == 0 || vstate == 4)	
					break;		
				h = (vstate == 2) ? 4 : 3;
				hstate = (hstate != h ) ? hstate + 1 : h;
				break;
			case 'L':
				if (vstate == 0 || vstate == 4)	
					break;	
				h = (vstate == 2) ? 0 : 1;
				hstate = (hstate > h) ? hstate - 1 : h;
				break;
			case 'U':
				if (hstate == 0 || hstate == 4)
					break;
				v = (hstate == 2) ? 0 : 1;
				vstate = (vstate > v) ? vstate - 1 : v;
				break;
			case 'D':
				if (hstate == 0 || hstate == 4)
					break;
				v = (hstate == 2) ? 4 : 3;
				vstate = (vstate != v) ? vstate + 1 : v;
				break;
		}
	}
	printf("DONE %c\n", pad[vstate][hstate]);
}

int main (int argc, char** argv) {

	FILE* fp = fopen("day2-input", "r");
	assert(fp);

	/*
	TEST INPUT
	parse_line("ULL");
	parse_line("RRDDD");
	parse_line("LURDL");
	parse_line("UUUUD");
	*/

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