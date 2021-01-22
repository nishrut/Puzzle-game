/*
Programmer:- Nishrut Patel
ID:- 110028922
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function to swap two numbers in array in given address as a parameter
void swap(int *a, int *b);

// function to print array out
void printarray(int r, int c, int array[][c]);

// function to generate random numbers in a given range
int random_numbers(int min, int max);

// function to fill array (populate array)
void populate_array(int r, int c, int array[][c]);

// function to check if it has a duplicate values or not
int duplicate(int r, int c, int array[][c], int num);
int main()
{
    printf("\n\n                !-:Welcome to the Number Game:-!               \n\n");
    printf("Instruction:- Select the number of rows and colums you want.\n");
    printf("              Then, you can see the board on your command line.\n");
    printf("              Now, enter the number you want to move to the empty.\n\n");
    printf("Note:- Entered number must be from the number near to the empty box\n");
    printf("       (not the diagonal one).");

    srand(time(0));
    while (1) // a while loop
    {
        int row, col;                         // initializing both integers for size of array
        printf("\n\nEnter number of row(3-8): "); // asking user to enter number of rows
        while (1)                             // a while loop
        {
            scanf("%d", &row); // scanning row

            if (row < 3 || row > 8) // if condition matches then print following message and then 'continue;'
            {
                printf("\n!!!!Invalid numbers!!!!\n\nPlease enter number of rows between 3 and 8:\n");
                continue;
            }
            else // else break;
                break;
        }

        printf("Enter number of column(3-8): "); // asking user to enter number of rows
        while (1)
        {
            scanf("%d", &col);

            if (col < 3 || col > 8) // if condition matches then print following message and then 'continue;'
            {
                printf("\n!!!!Invalid numbers!!!!\n\nPlease enter number of columns between 3 and 8:\n");
                continue;
            }
            else // else break;
                break;
        }
        int p[row][col]; // initializing array p with row = row , column = col

        // Initializing all arrays to 10000
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                p[i][j] = 10000;
            }
        }

        // calling populate array with parameters row, col and array p
        populate_array(row, col, p);

        puts("");

        // calling printarray function with parameter roe col and array p
        // printing array
        printarray(row, col, p);

        // initialixing both integers to store zero value's index number
        int em_i, em_j;

        // assigning em_i and em_j to the index in which value is zero
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (p[i][j] == 0)
                {
                    em_i = i;
                    em_j = j;
                }
            }
        }

        // to record time
        time_t start, end;
        time(&start);

        // initializing integer won to check whether all numbers are on same place or not
        int won = row * col;

        // integer counter to display total number of guess.
        int counter = 1;

        do
        {
            won = row * col;

            // assigning em_i and em_j to the index in which value is zero
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (p[i][j] == 0)
                    {
                        em_i = i;
                        em_j = j;
                    }
                }
            }

            // integer answer to store number which user want to move
            int answer;
            while (1) // while loop
            {         // printing message to enter number
                printf("\n\n---> Move no.%d- Enter the number you want to move(0 to exit): ", counter);
                scanf("%d", &answer); // storing number in answer

                if (answer >= 0 && answer < row * col) // answer must be in range
                    break;
                else // else print this statement
                    printf("!!!!Invalid number!!!!\n");
            }
            if (answer == 0) // if answer is 0 then loop whole thing will start again
                break;

            // innitializing integers
            // not_found is to check invalid choice of number
            // integer 'check' to check whether all are on same position or not 'check' is one (1) if all are not in their location.
            // index_value is to give value of their index.
            int index_value = 1, check = 0, not_found = 0;

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (p[i][j] == answer)
                    {
                        if ((i == em_i - 1 && j == em_j) || (i == em_i && j == em_j - 1) || (i == em_i + 1 && j == em_j) || (i == em_i && j == em_j + 1))
                        {
                            // if the above condition is correct then following things will occur
                            swap(&p[em_i][em_j], &p[i][j]); // calling swap function to swap to elements

                            puts("");
                            printarray(row, col, p); // printing array with table
                            for (int i_for = 0; i_for < row; i_for++)
                            {
                                for (int j_for = 0; j_for < col; j_for++, index_value++)
                                {
                                    if (p[i_for][j_for] != index_value) // if the number is not equal to the given index_value then 'check' =1 and 'won' will decrement
                                    {
                                        check = 1;
                                        won--;
                                    }
                                }
                            }
                        }
                        else if ((i != em_i - 1 && j != em_j) || (i != em_i && j != em_j - 1) || (i != em_i + 1 && j != em_j) || (i != em_i && j != em_j + 1))
                        {
                            // if above condition is correct then not_found will increment
                            not_found++;
                        }
                    }
                }
            }

            if (won == row * col - 1) // if all numbers are on correct position then following thing wil happen
            {
                time(&end); // ending time recording
                double t = difftime(end, start);
                // print winning message with users time taken and number of guesses that user take
                printf("\n\n                    !!Excellent!!\n");
                printf("  you solved this puzzle in %d guesses and %3.0f seconds.", counter, t);
            }

            if (not_found >= 1) // if any invalid movement found, then following thing will happen
            {
                not_found = 0; // making not_found zero
                check = 0;     // making check zero
                puts("");
                // printing some message if move is not possible
                puts("    !!Invalid move!!     ");
                puts("This move is not possible");
                continue;
            }
            else if (check == 1) // if no invalid movement is found then following thing will happen
            {
                not_found = 0;
                check = 0;
                counter++; // incrementing number of guesses
                continue;
            }

        } while (won != row * col - 1); // if all numbers are on their position then it will terminate from this loop

        printf("\nWant to play again? please enter 1(else enter any number): "); // message asks user if they want to play again
        int answer;
        scanf("%d", &answer);
        if (answer != 1) // if answer is not 1 then it will terminate from the loop
            break;
    }
    printf("GoodBye!!"); // printing message of goodbye
    return 0;
}

void swap(int *a, int *b) // function to swap the numbers
{
    int hold = *a;
    *a = *b;
    *b = hold;
}

void printarray(int r, int c, int array[][c]) // function to print array in a table form
{
    for (int i = 0; i < r; i++)
    {
        printf("| ");
        for (int j = 0; j < c; j++)
        {
            if (array[i][j] == 0)
                printf("   | ");

            else
                printf("%2d | ", array[i][j]);
        }
        puts("");
    }
}

void populate_array(int r, int c, int array[][c]) // function to fill array place
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c;)
        {
            int e = random_numbers(0, r * c - 1); // initializinf integer 'e' to the randomly generated numbers in a given range
            if (!duplicate(r, c, array, e))       // checking whether the generated number has a duplication or not
            {
                array[i][j] = e; // if no dupliaction is found then the array will fill with that generated number
                j++;
            }
        }
    }
}

int duplicate(int r, int c, int array[][c], int num) // function to check the duplication of numbers
{

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (array[i][j] == num) // if any other number is equal to the generated number then it will return 1
                return 1;
        }
    }

    return 0; // else return 0
}

int random_numbers(int min, int max) // function that creates random number in a given range
{

    int range = max - min + 1;

    return rand() % range + min; // returning generated random number̥
}
