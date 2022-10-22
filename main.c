/**
* Conway's Game of Life
* sequential version
* try padding the board with a border of 0s
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_board(short **board, int xlimit, int ylimit) {
    /* print out final board */
    int i,j;
    for (i = 0; i < xlimit; i++) {
        for (j = 0; j < ylimit; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}
//add parameter for file
void init_board(short **board, int xlimit, int ylimit, FILE *fd) {
    /* populate board with user file */
    //ask user for name of file
    char info[100];
    printf("what file do you want to use ");
    scanf("%s", info);
    strcat(info, ".txt");

    //open file
    fd = fopen(info, "r");

    //add error check for if pointer is null
    if (NULL == fd)
    {
        printf("error is happenigngn,");
    }


    //read values from file into board
    int i,j;
    for (i = 0; i < xlimit; i++)
    {
        for (j = 0; j < ylimit; j++)
        {
         char c = fgetc(fd);
         //convert to number
         int z = c - '0';
         //-1 = end
         if (z != -1)
         {
             board[i][j] = (short) z;
         }
        }
    }
}


int main (int argc, char* argv[]) {

    char *fname;
    FILE *fd;
    int xlimit, ylimit, iterations, iter;
    short *board1_data = NULL, *board2_data = NULL;
    short **b1_rows, **b2_rows;
    short **oldb = NULL, **newb = NULL, **tempb;
    int i, j, x, y, count;


    /* you can initialize the input for development*/
    xlimit = 5;
    ylimit = 5;
    iterations = 2;

    /* if you read from the command line */


    /* set up the boards - use 2, 1 for previous and 1 for current iteration,
     switching them every iteration */


    /* allocate space and initialize board to all 0's */
    board1_data = (short *) calloc(xlimit * ylimit, sizeof(short));
    if (board1_data == NULL) {
        fprintf(stderr, "Allocation failed for board1\n");
        //force exit if theres an error
        exit(-1);
    }
    board2_data = (short *) calloc(xlimit * ylimit, sizeof(short));
    if (board2_data == NULL) {
        fprintf(stderr, "Allocation failed for board1\n");
        exit(-1);
    }

    /* row pointers */
    b1_rows = (short **) malloc(xlimit * sizeof(short*));
    b1_rows[0] = board1_data;
    for (i = 1; i < xlimit; i++) {
        b1_rows[i] = b1_rows[i-1] + ylimit;
    }
    b2_rows = (short **) malloc(xlimit * sizeof(short*));
    b2_rows[0] = board2_data;
    for (i = 1; i < xlimit; i++) {
        b2_rows[i] = b2_rows[i-1] + ylimit;
    }

    /* initialize board1 with input data */
    init_board(b1_rows, xlimit, ylimit,  fd);

    //print starting board, adjust for boundary rows
     oldb = b1_rows;
     newb = b2_rows;
    print_board(oldb, xlimit, ylimit);

    /* perform the iterations, each time switching boards */
    for (iter = 0; iter < iterations; iter++)
    {
        //compute new board using array of index values rep. indices of neighbors
        //using -1 bc there's a boundary of 0s
        for(int i = 1; i < xlimit - 1; i++)
        {
            for(int j = 1; j < ylimit - 1; j++)
            {  //get cell being referenced thru forloops
                short cell = oldb[i][j];
                int neighbors = 0;

                int row[] = {i-1, i, i + 1};
                int col[] = {j - 1, j, j + 1};

                //get total of live cells neighboring inner cell
                for(int r = 0; r < 3; r++)
                {
                    for (int c = 0; c < 3; c++)
                    {
                        neighbors += oldb[row[r]][col[c]];
                    }
                }
                //delete innermost cell's  value from total
                neighbors -= (int) cell;

                //assign cell a new value
                //check if it should be alive or dead
                if(neighbors == 2 || neighbors == 3) //cell should be alive
                {
                    newb[i][j] = 1;
                }
                else //cell should die
                {
                   newb[i][j] = 0;
                }
            }
        }

        //print new board
        print_board(newb, xlimit, ylimit);

        /* switch boards */
        tempb = oldb;
        oldb = newb;
        newb = tempb;


    }

}
