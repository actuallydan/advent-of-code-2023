/*
The Elf leads you over to the pile of colorful cards. There, you discover dozens of scratchcards, all with their opaque covering already scratched off. Picking one up, it looks like each card has two lists of numbers separated by a vertical bar (|): a list of winning numbers and then a list of numbers you have. You organize the information into a table (your puzzle input).

As far as the Elf has been able to figure out, you have to figure out which of the numbers you have appear in the list of winning numbers. The first match makes the card worth one point and each match after the first doubles the point value of that card.

For example:

Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
In the above example, card 1 has five winning numbers (41, 48, 83, 86, and 17) and eight numbers you have (83, 86, 6, 31, 17, 9, 48, and 53). Of the numbers you have, four of them (48, 83, 17, and 86) are winning numbers! That means card 1 is worth 8 points (1 for the first match, then doubled three times for each of the three matches after the first).

Card 2 has two winning numbers (32 and 61), so it is worth 2 points.
Card 3 has two winning numbers (1 and 21), so it is worth 2 points.
Card 4 has one winning number (84), so it is worth 1 point.
Card 5 has no winning numbers, so it is worth no points.
Card 6 has no winning numbers, so it is worth no points.
So, in this example, the Elf's pile of scratchcards is worth 13 points.

Take a seat in the large pile of colorful cards. How many points are they worth in total?
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void clear_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

int main()
{

    FILE *file_pointer = NULL;

    file_pointer = fopen("input.txt", "r");
    // actual data
    int chars_to_first_number = 10;
    int num_winning_nums = 10;
    int num_to_your_numbers = chars_to_first_number + (num_winning_nums * 3) + 2;
    int num_your_numbers = 25;
    int length_game_num = 3;
    int max_games = 199;

    // test data
    // int chars_to_first_number = 8;
    // int num_winning_nums = 5;
    // int num_to_your_numbers = chars_to_first_number + (num_winning_nums * 3) + 2;
    // int num_your_numbers = 8;
    // int length_game_num = 1;
    // int max_games = 6;

    if (file_pointer == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // each line is 116 characters (adding for safety?)
    char current_line[200];
    char number_str[2];
    char game_str[3];

    int sum = 0;
    int matches_count = 0;

    // store the winning numbers in this array like a hash table, we'll check that a number is a winner if it = 1 in here
    int winning_numbers[100];
    clear_array(winning_numbers, 100);

    int card_quantities[200];
    clear_array(card_quantities, 200);

    while (fgets(current_line, sizeof(current_line) / sizeof(current_line[0]), file_pointer) != NULL)
    {

        // get the game number
        for (int i = 0; i < length_game_num; ++i)
        {
            game_str[i] = current_line[i + 5];
        }

        int game_num = atoi(game_str);
        card_quantities[game_num]++;

        printf("======================\t GAME:\t%i ======================\n", game_num);

        printf("\twinning numbers: \t");
        // build the dictionary of winning numbers
        for (int i = chars_to_first_number; i < chars_to_first_number + num_winning_nums * 3; i += 3)
        {
            number_str[0] = current_line[i];
            number_str[1] = current_line[i + 1];
            printf("%s\t", number_str);
            winning_numbers[atoi(number_str)] = 1;
        }
        printf("\n");

        memset(number_str, 0, 2);

        printf("\tmatching numbers: \t");

        // grab each 2 digit number, then move an additional space to get the next
        for (int i = num_to_your_numbers; i < num_to_your_numbers + num_your_numbers * 3; i += 3)
        {
            number_str[0] = current_line[i];
            number_str[1] = current_line[i + 1];

            int my_number = atoi(number_str);

            if (winning_numbers[my_number])
            {
                printf("%s\t", number_str);
                matches_count++;
            }
        }

        printf("\n");
        printf("\ttotal matches on this card: \t%i \n\n", matches_count);
        printf("---\n");

        // for each copy of current card, add a subsequent card for every match
        // if the current card is card #2, and there are 3  #2 cards, and card #2 has 4 matches
        // we would add 1 #3 card, 1 #4 card, 1 #5 card, and 1 #6 card for each #2 card
        printf("\tThere are %i copies of card \t%i, adding won cards\n", card_quantities[game_num], game_num);
        for (int i = 0; i < card_quantities[game_num]; ++i)
        {
            for (int i = 1; i < matches_count + 1; ++i)
            {
                int game_index = game_num + i;

                if (game_index <= max_games)
                {
                    // printf("\t\tyou won an additional \t%i\n", game_index);
                    card_quantities[game_index]++;
                }
            }
        }
        printf("---\n");
        printf("---\n");

        memset(number_str, 0, 2);
        clear_array(winning_numbers, 100);
        matches_count = 0;
    }

    // sum total cards
    for (int i = 1; i <= max_games; ++i)
    {
        printf("there are %i cards from game %i\n", card_quantities[i], i);
        printf("adding %i #%i cards\n", card_quantities[i], i);

        sum += card_quantities[i];
    }

    printf("this is the sum of cards %d\n", sum);

    return 0;
}