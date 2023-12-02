/*
--- Day 1: Trebuchet?! ---
Something is wrong with global snow production, and you've been selected to take a look. The Elves have even given you a map; on it, they've used stars to mark the top fifty locations that are likely to be having problems.

You've been doing this long enough to know that to restore snow operations, you need to check all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

You try to ask why they can't just use a weather machine ("not powerful enough") and where they're even sending you ("the sky") and why your map looks mostly blank ("you sure ask a lot of questions") and hang on did you just say the sky ("of course, where do you think snow comes from") when you realize that the Elves are already loading you into a trebuchet ("please hold still, we need to strap you in").

As they're making the final adjustments, they discover that their calibration document (your puzzle input) has been amended by a very young Elf who was apparently just excited to show off her art skills. Consequently, the Elves are having trouble reading the values on the document.

The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.

Consider your entire calibration document. What is the sum of all of the calibration values?
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

int main()
{
    FILE *file_pointer;
    int sum = 0;
    int num = 0;
    char str[MAX_LINE_LENGTH];
    char line_str[3];
    file_pointer = fopen("input.txt", "r");

    int count = 0;

    char apparently_valid_digits[][9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    
    while(fgets(str, MAX_LINE_LENGTH, file_pointer)){
        // fgets(str, MAX_LINE_LENGTH, file_pointer);
        printf("string: %s\n", str);
        int size = strlen(str);
        int start = 0;
        int end = size - 1;
        int found_start = 0;
        int found_end = 0;
        char first_num;
        char second_num;


        for(int j = 0; j <= size; j++){
            // printf("\nchecking these start:%c end: %c \n", str[j], str[size - j] );
            if(found_start && found_end){
                break;
            }

            if(!found_start){
                if(isdigit(str[j])){
                    line_str[0] = str[j];
                    found_start = 1;
                }
            }

            if(!found_end){
                if(isdigit(str[size - j])){
                    line_str[1] = str[size - j];
                    found_end = 1;
                }
            }

        }

        num = atoi(line_str);

        sum += num;


        printf("num:%d \n\n", num);
        count++;
    }


    fclose(file_pointer);

    printf("%i, last num: %i\n", sum, num);
    return 0;
}