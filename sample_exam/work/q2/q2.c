// COMP9315 22T1 Final Exam Q1
// Find longest tuple in a no-frills file

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
	char longest[MAXTUPLEN];
	int max_tup_len = 0;

	// Add variables and code here to find
	// the longest tuple in the data file

	// check that it contains at least one page worth of data
	fseek(fd, 0, SEEK_END);
	long int res = ftell(fd);
	if (res < PAGESIZE) {
		printf("%s\n", "<none>");
		return 0;
	}
	fseek(fd, 0, SEEK_SET);

	char* buf = malloc(PAGESIZE);
	while (1) {
		long int init_fpos = ftell(fd);

		fread(buf, PAGESIZE, 1, fd);

		// upon passing the end of file (after reading the last page), feof() will return true. 
		// Although fread will only read the bytes that exist, ftell() will still report a position beyond EOF. 
		if (feof(fd)) {
			// Therefore, seek fp back to EOF, this way ftell with actually say the proper EOF position
			fseek(fd, 0, SEEK_END);
			// get size of last page
			int size_of_curr_page = ftell(fd) - init_fpos;
			if (size_of_curr_page > 0 && size_of_curr_page < PAGESIZE) {
				printf("%s\n", "<none>");
				return 0;
			}
			break;
		}
		
		int ntuples = (int)buf[0];
		if (ntuples == 0) {
			printf("%s\n", "<none>");
			return 0;
		}

		int tup_count = 0;
		int i = 0;
		while (tup_count <= ntuples) {
			// increment j to the end of the next tuple
			int j = i;
			for (; buf[j] != '\0'; j++) {}
			tup_count++;
			if ((j - i) > max_tup_len) {
				max_tup_len = (j - i);
				strcpy(longest, &buf[i]);
			}
			i = j + 1;
		}
	}

	free(buf);

	printf("%s\n",longest);
	return 0;
}
