#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define DEFAULT_TITLE_MAX_LENGTH 100
#define DEFAULT_DESCRIPTION_MAX_LENGTH 1000
#define DEFAULT_NUMBER_OF_GENERATED_SETS 100
/*#define DEFAULT_FREE_ARRAY_SIZE 5

unsigned int tofreesize = DEFAULT_FREE_ARRAY_SIZE;
char** tofree = (char**)malloc(sizeof(char*)*tofreesize);
unsigned int tofreeidx = 0;


void AppendToFree(char* subj) {
	tofree[tofreeidx] = subj;
	tofreeidx++;
	if (tofreeidx + 2 == tofreesize) {
		tofreesize += DEFAULT_FREE_ARRAY_SIZE;
		tofree = (char**)realloc(tofree, sizeof(char*)*tofreesize);
	}
}

void FreeTool() {
	if (tofreeidx > 0) {
		for (int i = 0; i < tofreeidx; i++) {
			free(tofree[i]);
		}
	}
	free(tofree);
}*/

int StrToInt(char* strint) {
	char goodSymbSet[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	if (strint[0] != '0') {
		int res = 0;
		int multiplier = 1;
		for (int i = strlen(strint)-1; i >= 0; i--) {
			int j = 0;
			while (j < 10 && (strint[i] != goodSymbSet[j])) {
				j++;
			}
			res += multiplier * j;
			multiplier *= 10;
		}
		return res;
	} 
	return -1;
}

char* RandomStringGenerate(int maxlen, short int nextLineFlag) {
	char symbols[] = "ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz";
	short int symNum = strlen(symbols);
	int len = random() % (maxlen) + 1;
	char* res = (char*)malloc(sizeof(char)*len);
	for (int i = 0; i < len; i++) {
		res[i] = symbols[random() % symNum];
	} 
	return res;
}


int main(int argc, char** argv) {
	/* init */
	int tlm = DEFAULT_TITLE_MAX_LENGTH;
	int dlm = DEFAULT_DESCRIPTION_MAX_LENGTH;
	int n = DEFAULT_NUMBER_OF_GENERATED_SETS;
	int i = 1;
	if (argc == 1) {
		printf("Type -h for help\n");
		return -1;
	}
	while (i < argc) {
		int reacted = 0;
		if (strcmp(argv[i], "-tlm") == 0) {
			reacted = 1;
			tlm = StrToInt(argv[i+1]);
			if (tlm < 0) {
				printf("incorrect param -tlm\n");
				return -1;
			} else {
				i++;
			}
		}
		if (strcmp(argv[i], "-dlm") == 0) {
			reacted = 1;
			dlm = StrToInt(argv[i+1]);
			if (tlm < 0) {
				printf("incorrect param -dlm\n");
				return -1;
			} else {
				i++;
			}
		}
		if (strcmp(argv[i], "-n") == 0) {
			reacted = 1;
			n = StrToInt(argv[i+1]);
			if (tlm < 0) {
				printf("incorrect param -n\n");
				return -1;
			} else {
				i++;
			}
		}
		if (strcmp(argv[i], "-h") == 0) {
			reacted = 1;
			printf("books data generator in .yaml format\n");
			printf("This is list of available commands, take a look:\n");
			printf("-h         -> this page\n");
			printf("-tlm <int> -> maximum length of the book title\n");
			printf("-dlm <int> -> maximum length of the book description\n");
			printf("-n   <int> -> number of genereated sets\n");
			return 0;
		}
		if (reacted < 1) {
			printf("incorrect param! exiting, use help to know available commands\n");
			return -1;
		}
		i++;
	}


	/*create yaml file for our books and generate*/

	int fd = open("books.yaml", O_CREAT|O_WRONLY|O_APPEND, 0666); 
	if (fd != -1) {
		char* gen;
		for (int i = 0; i < n; i++) {
			if (write(fd, "- model: books.Book\n", 20) < 0) {
				printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
				exit(errno);
			}
			if (write(fd, "  fields:\n", 10) < 0) {
				printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
				exit(errno);
			}
			if (write(fd, "    title: ", 11) < 0) {
				printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
				exit(errno);
			}
			
			gen = RandomStringGenerate(tlm, 0);
			if (write(fd, gen, strlen(gen)) < 0) {
				printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
				free(gen);
				exit(errno);
			}
			if (write(fd, "\n", 1) < 0) {
				printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
				free(gen);
				exit(errno);
			}
			if (write(fd, "    content: ", 13) < 0) {
				printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
				free(gen);
				exit(errno);
			}
			free(gen);
			gen = RandomStringGenerate(dlm, 0);
			if (write(fd, gen, strlen(gen)) < 0) {
				printf("error while writing to file, write 4\n");
				free(gen);
				exit(errno);
			}
			if (write(fd, "\n", 1) < 0) {
				printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));
				free(gen);
				exit(errno);
			}
			free(gen);
		}
		close(fd);
	} else {
		printf("error, while opening file\n");
		exit(errno);
	}

	return 0;
}