#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sort the linked list from high to low
void sort_elves(int * root, int num_elves)
{
	int is_unsorted = 1;
	while(is_unsorted == 1) {
		is_unsorted = 0;
		for(int i = 0; i < num_elves-1; i++) {
			if(root[i] < root[i+1]) {
				is_unsorted = 1;
				int tmp = root[i];
				root[i] = root[i+1];
				root[i+1] = tmp;
			}
		}
	}
	return;
}

int main(int argc, char ** argv)
{
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	long int cur_cals = 0;
	if(argc < 2) {
		printf("Not enough arguments\n");
		exit(1);
	}
	FILE *f = fopen(argv[1], "r");
	if(f == NULL) {
		printf("Couldn't open file\n");
		exit(1);
	}

	long int total_elves = 1;	//Starting at 1 because there is not a blank line at the end of the input

	//Just counting the number of blank lines to get a number of elves to allocate
	while((read = getline(&line, &len, f)) != -1) {
		if(read == 2) {
			total_elves++;
		}
	}

	fseek(f, 0, SEEK_SET);

	int * root_elf = (int *)malloc(sizeof(int) * total_elves);
	memset(root_elf, 0, sizeof(int) * total_elves);
	long int current_elf = 0;
	//Loop through each line of the input
	while ((read = getline(&line, &len, f)) != -1) {
		//printf("Length of line: %d\n", read);
		if(read == 2) {
			current_elf++;
						
			continue;
		}
		cur_cals = strtol(line, NULL, 10);
		root_elf[current_elf] += cur_cals;
	}

	sort_elves(root_elf, total_elves);

	//for(current_elf = 0; current_elf < total_elves; current_elf++) {
	//	printf("Elf %ld calories: %d\n", current_elf, root_elf[current_elf]);
	//}

	printf("Elf with most calories: %d\n", root_elf[0]);
	printf("Top 3 elves calories: %d\n", root_elf[0] + root_elf[1] + root_elf[2]);

	//Free the linked list
	free(root_elf);
	free(line);
	fclose(f);
}