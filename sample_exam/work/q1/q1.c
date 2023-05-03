// COMP9315 22T1 Final Exam Q1
// Count tuples in a no-frills file

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "no-frills.h"

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s DataFile\n", argv[0]);
		exit(1);
	}
	FILE* fd = fopen(argv[1],"r");
	// if (fd < 0) {
	// 	printf("Can't open file %s\n", argv[1]);
	// 	exit(1);
	// }

	// Add variables and code here to work out
	// the total number of tuples
	// printf("DataFile: %s", argv[1]);
	int ntuples = 0;

	// check that it contains at least one page worth of data
	fseek(fd, 0, SEEK_END);
	long int res = ftell(fd);
	if (res < PAGESIZE) {
		printf("%d\n", -1);
		return 0;
	}
	fseek(fd, 0, SEEK_SET);

	char* buf = malloc(PAGESIZE);
	while (fread(buf, PAGESIZE, 1, fd) == 1) {
		// check that this chunk is actually a page - i.e. ends in '\0\0'
		if (!(buf[PAGESIZE - 1] == '\0' && buf[PAGESIZE - 2] == '\0')) {
			printf("%d\n", -1);
			return 0;
		}
		// check that there are no instance of just '\0\0' anywhere else in the page
		for (int i = 0; i < PAGESIZE - 2; i++) {
			if (buf[i] == '\0' && buf[i + 1] == '\0' && buf[i + 2] != '\0') {
				printf("%d\n", -1);
				return 0;
			}
		}
		ntuples += (int)buf[0];
	}

	free(buf);

	printf("%d\n",ntuples);
	return 0;
}
