// COMP9315 22T1 Final Exam Q3
// Read tuples from stdin and store in no-frills file
// Start from empty file, add new pages as needed

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "no-frills.h"

int main(int argc, char **argv)
{
	if (argc < 3) {
		fprintf(stderr, "Usage: %s DataFile TupleFile\n", argv[0]);
		exit(1);
	}
	// unsigned int mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;
	FILE* fd = fopen(argv[1],"w+");
	if (fd < 0) {
		fprintf(stderr, "Can't open data file.\n");
		exit(1);
	}
	FILE *input = fopen(argv[2],"r");
	if (input == NULL) {
		fprintf(stderr, "Can't open input file.\n");
		exit(1);
	}

	// Add variables and code here to read tuples from
	// input and append them to the "no-frills" file

	char* page_buf = malloc(PAGESIZE);
	char buf_ntuples = 0;
	// indicates where to start adding the next tuple
	int buf_index = 1;
	size_t readlen = 0;
	char * line = malloc(MAXTUPLEN);
	size_t max_tup_len = MAXTUPLEN;

	while ((readlen = getline(&line, &max_tup_len, input)) != -1) {
		if ((buf_index + readlen) >= PAGESIZE - 1) {
			// add ntuples as first item in buffer
			memcpy(&page_buf[0], &buf_ntuples, 1);
			// write out buffer
			fwrite(page_buf, PAGESIZE, 1, fd);
			// reset page_buf index
			buf_index = 1;
			buf_ntuples = 0;
			// zero out buffer
			memset(page_buf, '\0', PAGESIZE);
		}

		line[readlen - 1] = '\0';
		memcpy(&page_buf[buf_index], line, readlen);
		buf_index += readlen;
		buf_ntuples += 1;

	}

	if (buf_ntuples > 0) {
		// add ntuples as first item in buffer
		memcpy(&page_buf[0], &buf_ntuples, 1);
		// write out buffer
		fwrite(page_buf, PAGESIZE, 1, fd);
	} else {
		// write out buffer full of '\0's
		fwrite(page_buf, PAGESIZE, 1, fd);
	}

	free(page_buf);
	free(line);



	return 0;
}
