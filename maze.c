#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x, y;
} Point;


int turnLeft(int dir);
int turnRight(int dir);


void go_forward(Point * curr, int dir);

char ** read_input(char filename[], Point * maze_size, Point * start, Point * end, char ** maze);
char ** create_2d_array(int number_rows, int number_columns, char ** arr);

void find_path(char ** maze, Point * maze_size, Point * start, Point * end);

int main(int argc, char ** argv) {
    int i, j;
    char * fname = "maze2.txt";
    
    printf("Hey!\n");
    
    Point maze_size;
    Point start;
    Point end;
    
    //char ** maze;
    
    //Don;t think about his picutre.
    //First index is the horizontal axis, accessed by x positions within the code.
    //The second index is the vertical axis, accessed by y within the code.
    
    char maze[4][16] ={
        {'X', 'X', 'X', 'X', 'X', '0', 'X', 'X', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'X', 'X', 'X', 'X', 'X', '0', 'X', 'X', '0', 'X', 'X', 'X', '0', '0', '0', '0'},
        {'0', '0', 'X', 'X', 'X', '0', 'X', 'X', '0', 'X', 'X', 'X', '0', '0', '0', '0'},
        {'0', '0', 'X', 'X', 'X', '0', '0', '0', '0', '0', 'X', '0', '0', '0', '0', '0'}
    };
    
    maze_size.x = 4;
    maze_size.y = 16;
    
    start.x = 0;
    start.y = 5;
    
    end.x = 2;
    end.y = 15;
    
    /*
     printf("argc: %d\n", argc);
     for (i = 0; i < argc; ++i) {
     printf("argv[%d]: %s \n", i, argv[i]);
     }*/
    
    //maze = read_input(fname, &maze_size, &start, &end, maze);
    /*
     maze = create_2d_array(width, height, maze);
     
     for (i = 0; i < width; ++i)
     {
     for (j = 0; j < height; ++j)
     {
     printf("i: %d j: %d\n", i, j);
     maze[i][j] = 63 + i+j;
     }
     printf("\n");
     }
     */
    for (j = 0; j < maze_size.y; ++j) {
        for (i = 0; i < maze_size.x; ++i) {
        
            
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    
    
    
    return 0;
}

int turnLeft(int dir) {
    return (dir - 1 + 4) % 4;
}

int turnRight(int dir) {
    return (dir + 1) % 4;
}

void go_forward(Point * curr, int dir)
{
    switch (dir)
    {
        case 0: //north
            --curr->x;
            break;
        case 1: //east
            ++curr->y;
            break;
        case 2: //south
            ++curr->x;
            break;
        case 3: //west
            --curr->y;
            break;
        default:
            printf("you are eaten by the minotaur");
            break;
    }
}

bool is_in_maze(Point maze_size, Point pos)
{
    if (pos.x < 0)
        return false;
    if (pos.x >= maze_size.x)
        return false;
    if (pos.y < 0)
        return false;
    if (pos.y >= maze_size.y)
        return false;
    return true;
}

bool is_wall(char ** maze, Point maze_size, Point pos)
{
    if (!is_in_maze(maze_size, pos))
        return true;
    return (maze[pos.x][pos.y] == 'X');
}

//bool is_wall_left()
bool is_wall_next_to(char ** maze, Point maze_size, Point * pos, int dir)
{
    Point target;
    target.x = pos->x;
    target.y = pos->y;
    
    go_forward(&target, dir);
    return is_wall(maze, maze_size, target);
    
}


void find_path(char ** maze, Point * maze_size, Point * start, Point * end)
{
    int dir = 2; //South
    bool solved = false;
    Point curr;
    
    curr.x = start->x;
    curr.y = start->y;
    
    while (!solved)
    {
        if (!is_wall_next_to(maze, &maze_size, &curr, dir)) //no wall ahead
        {
            go_forward(&curr, dir);
        }
        else if (!is_wall_next_to(maze, &maze_size, &curr, turn_right(dir))) // no wall to the right
        {
            dir = turnRight(dir);
            go_forward(&curr, dir);
        }
        else if (!is_wall_next_to(maze, &curr, turn_left(dir))) // no wall to the right
        {
            dir = turnRight(dir);
            go_forward(&curr, dir);

        }
        
        if ((curr.x == end->x) &&(curr.y == end->y) )
            solved = true;
    }
    
}


//
//char ** create_2d_array(int nrows, int ncolumns, char ** array) {
//    int i;
//
//    printf("rows: %d, columns: %d\n", nrows, ncolumns);
//    array = malloc(nrows * sizeof (char *));
//    for (i = 0; i < nrows; i++) {
//        printf("current row: %d\n", i);
//        array[i] = malloc(ncolumns * sizeof (char));
//    }
//    /*
//     for (i = 0; i < nrows; ++i)
//     {
//     for (j = 0; j < ncolumns; ++j)
//     {
//     printf("place to add: i: %d j: %d\n", i, j);
//     array[i][j] = 63 + i+j;
//     printf("value at i: %d j: %d is %d\n", i, j, array[i][j]);
//     }
//     printf("\n");
//     }
//
//     */
//
//    /*
//     int i;
//     arr = malloc( number_rows *sizeof(char*));
//     for (i = 0; i < number_rows; i++)
//     {
//     arr[i] = malloc(number_columns *sizeof(char));
//     }*/
//    return array;
//}

char ** read_input(char filename[], Point * maze_size, Point * start, Point * end, char ** maze) {
    FILE *fp;
    int SIZE = 6000;
    char line[SIZE];
    int line_number = 0;
    
    int current_row, current_column;
    /*
     int width;
     int height;
     
     int startx, starty;
     int endx, endy;
     */
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("File open not successful.\n");
        return 0;
    } else {
        while (fgets(line, SIZE, fp) != NULL) {
            if (line_number == 0) {
                sscanf(line, "%d,%d", &(maze_size->x), &(maze_size->y));
                printf("width: %d, height: %d\n", maze_size->x, maze_size->y);
            } else if (line_number == 1) {
                sscanf(line, "%d,%d", &(start->x), &(start->y));
                //printf("startx: %d, starty: %d\n", startx, starty);
            } else if (line_number == 2) {
                sscanf(line, "%d,%d", &(end->x), &(end->y));
                //printf("end x: %d, end y: %d\n", endx, endy);
            } else if (line_number == 3) {
                current_row = 0;
                //maze = create_2d_array(maze_size->x, maze_size->y, maze);
            }
            
            if (line_number >= 3) {
                current_column = 0;
                while (line[current_column] != '\0') {
                    printf("row: %d col: %d \n", current_row, current_column);
                    maze[current_row][current_column] = line[current_column];
                    current_column++;
                }
                current_row++;
            }
            //sscanf(line, "%lf %lf %lf %lf ", &charges[i].charge, &charges[i].x, &charges[i].y, &charges[i].z);
            //printf("%s ", line);
            ++line_number;
        }
        
        printf("File open successful.\n");
        if (fclose(fp) == EOF) {
            printf("File close not successful.\n");
            return 0;
        }
    }
    return maze;
}
