/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(int d);
void draw(int d);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init(d);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(d);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(int d)
{
    //create the board d x d squares where d is input by the user DIM_MIN to DIM_MAX
    //nested for loop d times
    
    //find max number of the board
    int max = ((d * d) - 1);
    int even = d % 2;
    int i, j;
    
    //board rows
    for(i = 0; i < d; i++)
    {
        //board columns
        for(j = 0; j < d; j++)
        {
            //enter the values of j'th square on i'th row
            //numbers should start reversed and go to 1

            //insert the numbers into the board starting at max and decreasing each iteration
            board[i][j] = max;
            max--;
        }
    }
    
    //if d is even then swap values #2 and #1 on the board
    if(even == 0)
    {
        int temp = board[d - 1][d - 2];
        board[d - 1][d - 2] = board[d - 1][d - 3];
        board[d - 1][d - 3] = temp;
    }

}

/**
 * Prints the board in its current state.
 */
void draw(int d)
{

    int i, j;
    
    //board rows
    for(i = 0; i < d; i++)
    {
        //board columns
        for(j = 0; j < d; j++)
        {

            //print each space with a leading space if a single digit
            printf("%2i ", board[i][j]);
        
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int i, j;
    
    //iterate over board rows
    for(i = 0; i < d; i++)
    {
        //iterate over board columns looking for tile
        for(j = 0; j < d; j++)
        {
            //find the empty tile and determine if a move can be made
            if(board[i][j] == 0){
                
                if(board[i - 1][j] == tile){
                    int temp = board[i - 1][j];
                    board[i - 1][j] = board[i][j];
                    board[i][j] = temp;
                    return true;
                }
                else if(board[i + 1][j] == tile){
                    int temp = board[i + 1][j];
                    board[i + 1][j] = board[i][j];
                    board[i][j] = temp;
                    return true;
                }
                else if(board[i][j - 1] == tile){
                    int temp = board[i][j - 1];
                    board[i][j - 1] = board[i][j];
                    board[i][j] = temp;
                    return true;
                }
                else if(board[i][j + 1] == tile){
                    int temp = board[i][j + 1];
                    board[i][j + 1] = board[i][j];
                    board[i][j] = temp;
                    return true;
                } else {
                    return false;
                }
            }
            
        }
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    //find max number of the board
    int max = ((d * d) - 1);
    int i, j, count = 1;
    
    //board rows
    for(i = 0; i < d; i++)
    {
        //board columns
        for(j = 0; j < d; j++)
        {
            //search each spot starting at 0 and count up to the max, if every spot equals the count then win!

            if(board[i][j] == count){
                if(count == max){
                    return true;
                }
                count++;
            } else { return false; }
        }
    }
    
    return false;
}
