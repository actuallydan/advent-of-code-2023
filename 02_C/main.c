#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_GREEN_CUBES 13  
#define NUM_RED_CUBES 12 
#define NUM_BLUE_CUBES 14

// I hate the way I'm doing this but grug-brain tells me if I have a low N it doesn't make a difference
// thanks Illinois education system https://systems-encyclopedia.cs.illinois.edu/articles/c-strtok/
int main()
{
    char my_string[] = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
    char colon_tok[1] = ":";
    char semi_tok[1] = ";";
    char comma_tok[1] = ",";
    char space_tok[1] = " ";

    int sum = 0;

    int fewest_green_seen = 0;
    int fewest_red_seen = 0;
    int fewest_blue_seen = 0;
    
    char* save_game;
    char* save_rounds;
    char* save_color;
    char* save_count;

    FILE *file_pointer;

    char str[200];

    file_pointer = fopen("input.txt", "r");

    while(fgets(str, 200, file_pointer)){
        int power = 0;

        if(strcmp(str, "\n") == 0){
            continue;
        }
        // split each line by : to get the game
        for(char *game_ptr = strtok_r(str, colon_tok, &save_game); game_ptr != NULL; game_ptr = strtok_r(NULL, colon_tok, &save_game)) {

            // printf("%s\n", game_ptr);

            if(*game_ptr != 'G'){
                // -> split [1] by semi colon
                for(char *rounds_ptr = strtok_r(game_ptr, semi_tok, &save_rounds); rounds_ptr != NULL; rounds_ptr = strtok_r(NULL, semi_tok, &save_rounds)) {
                    // printf("  %s\n", rounds_ptr);

                    // --> trim and split each by comma
                    for(char *color_ptr = strtok_r(rounds_ptr, comma_tok, &save_color); color_ptr != NULL; color_ptr = strtok_r(NULL, comma_tok, &save_color)) {
                        int pull_count = 0;
                        char pull_color;
                        // printf("    %s\n", color_ptr);
                        // --> trim and split each by space
                        for(char *count_ptr = strtok_r(color_ptr, space_tok, &save_count); count_ptr != NULL; count_ptr = strtok_r(NULL, space_tok, &save_count)) {
                            // printf("      %s\n", count_ptr);

                            if(isdigit(count_ptr[0])){
                                pull_count = atoi(count_ptr);
                            } else {
                                // printf("color: %s", count_ptr);
                                pull_color = count_ptr[0];
                            }

                        }

                        if(pull_color == 'g' && pull_count > fewest_green_seen){
                            fewest_green_seen = pull_count;
                        }
                        if(pull_color == 'b' && pull_count > fewest_blue_seen){
                            fewest_blue_seen = pull_count;
                        }
                        if(pull_color == 'r' && pull_count > fewest_red_seen){
                            fewest_red_seen = pull_count;
                        }
                    }
                }
            }
        }

        printf("green: %i, red: %i, blue: %i\n", fewest_green_seen, fewest_red_seen, fewest_blue_seen);

        // -> get power of game by multiplying together rgb
        power = fewest_green_seen * fewest_red_seen * fewest_blue_seen;

        sum += power;

        fewest_green_seen = 0;
        fewest_red_seen = 0;
        fewest_blue_seen = 0;
        power = 0;
    }

    printf("\nsum %i\n", sum);


    return 0;
}