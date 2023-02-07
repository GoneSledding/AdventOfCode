#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_score(char opp, char usr)
{
    int score = 0;
    if(opp == 'A' && usr == 'X') score+= 4;
    else if(opp == 'A' && usr == 'Y') score += 8;
    else if(opp == 'A' && usr == 'Z') score += 3;
    else if(opp == 'B' && usr == 'X') score += 1;
    else if(opp == 'B' && usr == 'Y') score += 5;
    else if(opp == 'B' && usr == 'Z') score += 9;
    else if(opp == 'C' && usr == 'X') score += 7;
    else if(opp == 'C' && usr == 'Y') score += 2;
    else if(opp == 'C' && usr == 'Z') score += 6;

    return score;
}

int calculate_alt_strategy(char opp, char usr)
{
    int score = 0;
    if(opp == 'A' && usr == 'X') score+= 3;
    else if(opp == 'A' && usr == 'Y') score += 4;
    else if(opp == 'A' && usr == 'Z') score += 8;
    else if(opp == 'B' && usr == 'X') score += 1;
    else if(opp == 'B' && usr == 'Y') score += 5;
    else if(opp == 'B' && usr == 'Z') score += 9;
    else if(opp == 'C' && usr == 'X') score += 2;
    else if(opp == 'C' && usr == 'Y') score += 6;
    else if(opp == 'C' && usr == 'Z') score += 7;

    return score;
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

	long int part1_score = 0;
    long int part2_score = 0;
	//Loop through each line of the input
	while ((read = getline(&line, &len, f)) != -1) {
		part1_score += calculate_score(line[0], line[2]);
        part2_score += calculate_alt_strategy(line[0], line[2]);
	}

	printf("%ld\n", part1_score);
	printf("%ld\n", part2_score);

	fclose(f);
}