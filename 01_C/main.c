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

char get_number_from_string(const char str[]) {
    if (strcmp(str, "one") == 0) {
        return '1';
    } else if (strcmp(str, "two") == 0) {
        return '2';
    } else if (strcmp(str, "three") == 0) {
        return '3';
    } else if (strcmp(str, "four") == 0) {
        return '4';
    } else if (strcmp(str, "five") == 0) {
        return '5';
    } else if (strcmp(str, "six") == 0) {
        return '6';
    } else if (strcmp(str, "seven") == 0) {
        return '7';
    } else if (strcmp(str, "eight") == 0) {
        return '8';
    } else if (strcmp(str, "nine") == 0) {
        return '9';
    } else {
        return '0';
    }
}

void substring(char source[], int start, int length, char destination[]) {
    int i, j;

    // Copy characters from source to destination
    for (i = start, j = 0; i < start + length && source[i] != '\0'; i++, j++) {
        destination[j] = source[i];
    }

    // Null-terminate the destination string
    // this I definitely copied from SO
    destination[j] = '\0';
}

int main()
{
    FILE *file_pointer;
    int sum = 0;
    int num = 0;
    char str[MAX_LINE_LENGTH] = "rsmcrqlnhsmjhspseven96vsckknrggbjd4tgtgbkxgvt";
    char line_str[3];
    file_pointer = fopen("input.txt", "r");

    int count = 0;

    char apparently_valid_digits[][9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    
    
    while(fgets(str, MAX_LINE_LENGTH, file_pointer)){
        // fgets(str, MAX_LINE_LENGTH, file_pointer);
        // printf("string: %s\n", str);
        int size = strlen(str);
        int start = 0;
        int end = size - 1;
        int found_start = 0;

        for(int j = 0; j <= size; j++){
            // printf("\nchecking these start:%c end: %c \n", str[j], str[size - j] );
           
            if(isdigit(str[j])){
                if(!found_start){
                    line_str[0] = str[j];
                    line_str[1] = str[j];
                    found_start = 1;
                    // printf("found a number substring: %c \n", str[j]);

                } else {
                    line_str[1] = str[j];
                    // printf("found a number substring: %c \n", str[j]);

                }
            } else {
                char substr[size]; 
                // if it's not a digit, check if it's a word
                for(int k = 0; k < 9; k++){
                    int length_of_word = strlen(apparently_valid_digits[k]);

                    substring(str, j, length_of_word, substr);
                    // printf("substring: %s word: %s\n\n", substr, apparently_valid_digits[k]);
                    if(strcmp(substr, apparently_valid_digits[k]) == 0){
                        if(!found_start){
                            // printf("found a string substring: %s word: %s\n\n adding it to start", substr, apparently_valid_digits[k]);
                            line_str[0] = get_number_from_string(apparently_valid_digits[k]);
                            line_str[1] = get_number_from_string(apparently_valid_digits[k]);
                            found_start = 1;

                        } else {
                            // printf("found a string substring: %s word: %s\n\n", substr, apparently_valid_digits[k]);
                            line_str[1] = get_number_from_string(apparently_valid_digits[k]);
                        }
                    }
                }; 
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