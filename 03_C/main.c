/*
--- Day 3: Gear Ratios ---
You and the Elf eventually reach a gondola lift station; he says the gondola lift will take you up to the water source, but this is as far as he can bring you. You go inside.

It doesn't take long to find the gondolas, but there seems to be a problem: they're not moving.

"Aaah!"

You turn around to see a slightly-greasy Elf with a wrench and a look of surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working right now; it'll still be a while before I can fix it." You offer to help.

The engineer explains that an engine part seems to be missing from the engine, but nobody can figure out which one. If you can add up all the part numbers in the engine schematic, it should be easy to work out which part is missing.

The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers and symbols you don't really understand, but apparently any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

Here is an example engine schematic:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
In this schematic, two numbers are not part numbers because they are not adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.

Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine schematic?

*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int is_special_character(char c){
    char chars[] = {'*', '=', '+', '/', '&', '#', '%', '-', '$', '@'};
    for(int i = 0; i < 10; ++i){
        if(c == chars[i] && c != '\0' && c != '\n'){
            return 1;
        }
    }

    return 0;
}

int main(){
    FILE *file_pointer = NULL;

    file_pointer = fopen("input.txt", "r");

    if (file_pointer == NULL) {
        perror("Error opening file");
        return 1;
    }

    char current_line[300];
    char all_lines[300][300];

    int builder_cursor = 0;
    char builder[3];

    int sum = 0;

    int counter = 0;

    while(fgets(current_line, sizeof(current_line) / sizeof(current_line[0]), file_pointer) != NULL){
        if (strcmp(current_line, "\n") == 0) {
            printf("what the fuck %d\n", counter);
            return 1;
        }
        if (strchr(current_line, '\n') == NULL) {
            printf("counter %d\n", counter);
            printf("Line too long:\n%s \n", current_line);
            break;
        }
        

        strcpy(all_lines[counter], current_line);
        counter++;
    }
    fclose(file_pointer);

    int found_item = 0;

    for(int i = 0; i < counter; ++i){
        // check each character in current all_lines
        // printf("%s", all_lines[i]);
        for(int j = 0; j < 140; ++j){

            // if it's a digit add it
            if(isdigit(all_lines[i][j]) && builder_cursor < 3 ){
                builder[builder_cursor] = all_lines[i][j];
                builder_cursor++;
            }

            if(all_lines[i][j] == '.' || is_special_character(all_lines[i][j]) || all_lines[i][j + 1] == '\n' ) {
                int should_reduce_cursor_for_edge = all_lines[i][j + 1] == '\n' && isdigit(all_lines[i][j]);

                if(builder_cursor > 0){
                    found_item = 0;
                    // printf("what number are we looking for %s, character: %c\n ", builder, all_lines[i][j]);
                    // printf("my builder is %s and my builder length is %d\n", builder, builder_cursor);
                    // check every character above, adjacent to, and below the builder
                    for(int n = i - 1; n < i + 2; ++n){
                        for(int k = j - builder_cursor - 1 + should_reduce_cursor_for_edge; k < j + 1; ++k){
                            // printf("        checking this character %c @ %i, %i \n", all_lines[n][k], n, k);

                            if(n < 0 || k < 0 || n > 139 || k > 139){
                                continue;
                            } 

                            
                            if(is_special_character(all_lines[n][k])){
                                printf("    found %s \t %c \t [ %i,\t%i ]\n ", builder, all_lines[n][k], n, k);
                                sum += atoi(builder);

                                // reset cursor
                                found_item = 1;
                                builder_cursor = 0;
                                memset(builder, 0, 3);
                                break;
                            }
                            
                        }
                        if(found_item){
                            break;
                        }
                    }
                }

                builder_cursor = 0;
                memset(builder,0,3);
            }

        }
        builder_cursor = 0;
        memset(builder,0,3);
    }

    printf("\ntotal %i \n", sum);

    return 0;
}