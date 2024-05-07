#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 12

//case 9 is specific to the starting location
void printm(int maze[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            switch(maze[i][j]){
                case 0:
                    printf("# ");
                    break;
                case 1:
                    printf(". ");
                    break;
                case 2:
                    printf("# ");
                    break;
                case 9:
                    printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

//status 1 is used for pathfinding, status 0 is used for initial generation
void mazeTraverse(int maze[SIZE][SIZE], int pos[2], int status){
    int direction = 2;
    if(maze[pos[0]][pos[1] - 1] == 9){
        maze[pos[0]][pos[1] - 1] = 8;
    }
    else{
        maze[pos[0] - 1][pos[1]] = 8;
    }
    if(status == 1){
        printm(maze);
    }
    maze[pos[0]][pos[1]] = 3;
    if(status == 1){
        printm(maze);
    }
    
    for(int i = 0; i < 500; i++){

        //terminates loop if it reaches an edge square
        if(pos[0] == SIZE - 1 || pos[1] == SIZE - 1){
            if(status == 0){
                for(int i = 0; i < SIZE; i++){
                    for(int j = 0; j < SIZE; j++){
                        if(maze[i][j] == 1){
                            maze[i][j] = 0;
                        }
                        else if(maze[i][j] == 3){
                            maze[i][j] = 1;
                        }
                        else if(maze[i][j] == 8){
                            maze[i][j] = 9;
                        }
                    }
                }
            }
            break;
        }

        //checks right, then checks forward, then checks left, and then back
        //0 is up, 1 is right, 2 is down, 3 is left
        switch(direction){
            case 0:
                if(maze[pos[0]][pos[1] + 1] == 1 || maze[pos[0]][pos[1] + 1] == 3){
                    direction = 1;
                    pos[1]++;
                }
                else if(maze[pos[0] - 1][pos[1]] == 1 || maze[pos[0] - 1][pos[1]] == 3){
                    pos[0]--;
                }
                else if(maze[pos[0]][pos[1] - 1] == 1 || maze[pos[0]][pos[1] - 1] == 3){
                    direction = 3;
                    pos[1]--;
                }
                else{
                    direction = 2;
                    pos[0]++;
                }
                break;
            case 1:
                if(maze[pos[0] + 1][pos[1]] == 1 || maze[pos[0] + 1][pos[1]] == 3){
                    direction = 2;
                    pos[0]++;
                }
                else if(maze[pos[0]][pos[1] + 1] == 1 || maze[pos[0]][pos[1] + 1] == 3){
                    pos[1]++;
                }
                else if(maze[pos[0] - 1][pos[1]] == 1 || maze[pos[0] - 1][pos[1]] == 3){
                    direction = 0;
                    pos[0]--;
                }
                else{
                    direction = 3;
                    pos[1]--;
                }
                break;
            case 2:
                if(maze[pos[0]][pos[1] - 1] == 1 || maze[pos[0]][pos[1] - 1] == 3){
                    direction = 3;
                    pos[1]--;
                }
                else if(maze[pos[0] + 1][pos[1]] == 1 || maze[pos[0] + 1][pos[1]] == 3){
                    pos[0]++;
                }
                else if(maze[pos[0]][pos[1] + 1] == 1 || maze[pos[0]][pos[1] + 1] == 3){
                    direction = 1;
                    pos[1]++;
                }
                else{
                    direction = 0;
                    pos[0]--;
                }
                break;
            case 3:
                if(maze[pos[0] - 1][pos[1]] == 1 || maze[pos[0] - 1][pos[1]] == 3){
                    direction = 0;
                    pos[0]--;
                }
                else if(maze[pos[0]][pos[1] - 1] == 1 || maze[pos[0]][pos[1] - 1] == 3){
                    pos[1]--;
                }
                else if(maze[pos[0] + 1][pos[1]] == 1 || maze[pos[0] + 1][pos[1]] == 3){
                    direction = 2;
                    pos[0]++;
                }
                else{
                    direction = 1;
                    pos[1]++;
                }
        }
        maze[pos[0]][pos[1]] = 3;

        if(status == 1){
            printm(maze);
        }
    }
}

int mazeGenerator(int maze[SIZE][SIZE], int start[2], int end[2]){

    //makes all edge squares walls
    for(int i = 0; i < SIZE; i++){
        maze[0][i] = 2;
        maze[i][0] = 2;
        maze[SIZE - 1][i] = 2;
        maze[i][SIZE - 1] = 2;
    }

    //randomly chooses either the top or right as starting side
    //randomly chooses 1 of (SIZE - 2) squares on that side
    int random = (rand() % (SIZE - 2)) + 1;
    if(rand() % 2 == 0){
        maze[0][random] = 9;
        start[0] = 1;
        start[1] = random;
        maze[1][random] = 1;
        random = (rand() % (SIZE - 2)) + 1;
        maze[SIZE - 2][random] = 1;
        end[0] = SIZE - 2;
        end[1] = random;
        maze[SIZE - 1][random] = 1;
    }
    else{
        maze[random][0] = 9;
        start[0] = random;
        start[1] = 1;
        maze[random][1] = 1;
        random = (rand() % (SIZE - 2)) + 1;
        maze[random][SIZE - 2] = 1;
        end[0] = random;
        end[1] = SIZE - 2;
        maze[random][SIZE - 1] = 1;
    }

    //randomly moves around. Any passed squares are changed to movable.
    int pos[] = {start[0], start[1]};
    for(int i = 0; i < 1000000; i++){
        if(pos[0] == end[0]){
            if(pos[1] == end[1]){
                break;
            }
        }
        if(i == 999){
            printf("Maze generation failed.\n");
            return(1);
        }
        switch((rand())%4){
            case 0:
                if(maze[pos[0] + 1][pos[1]] != 2 && maze[pos[0] + 1][pos[1]] != 9){
                    pos[0]++;
                }
                break;
            case 1:
                if(maze[pos[0]][pos[1] + 1] != 2 && maze[pos[0]][pos[1] + 1] != 9){
                    pos[1]++;
                }
                break;
            case 2:
                if(maze[pos[0] - 1][pos[1]] != 2 && maze[pos[0] - 1][pos[1]] != 9){
                    pos[0]--;
                }
                break;
            case 3:
                if(maze[pos[0]][pos[1] - 1] != 2 && maze[pos[0]][pos[1] - 1] != 9){
                    pos[1]--;
                }
        }
        maze[pos[0]][pos[1]] = 1;
    }

    //removes excess movable squares
    pos[0] = start[0];
    pos[1] = start[1];
    mazeTraverse(maze, pos, 0);

    //creates false paths by making squares that have only one adjacent movable square movable
    int count;
    for(int k = 0; k < SIZE/3; k++){
        count = rand() % 4;
        switch(count){
            case 0:
                for(int i = 1; i < SIZE - 1; i++){
                    for(int j = 1; j < SIZE - 1; j++){
                        if(maze[i][j] == 0){
                            count = 0;
                            if(maze[i + 1][j] == 1){
                                count++;
                            }
                            if(maze[i - 1][j] == 1){
                                count++;
                            }
                            if(maze[i][j + 1] == 1){
                                count++;
                            }
                            if(maze[i][j - 1] == 1){
                                count++;
                            }

                            if(count == 1){
                                maze[i][j] = 1;
                            }
                        }
                    }
                }

            case 1:
                for(int j = 1; j < SIZE - 1; j++){
                    for(int i = 1; i < SIZE - 1; i++){
                        if(maze[i][j] == 0){
                            count = 0;
                            if(maze[i + 1][j] == 1){
                                count++;
                            }
                            if(maze[i - 1][j] == 1){
                                count++;
                            }
                            if(maze[i][j + 1] == 1){
                                count++;
                            }
                            if(maze[i][j - 1] == 1){
                                count++;
                            }

                            if(count == 1){
                                maze[i][j] = 1;
                            }
                        }
                    }
                }

            case 2:
                for(int j = SIZE - 2; j > 0; j--){
                    for(int i = SIZE - 2; i > 0; i--){
                        if(maze[i][j] == 0){
                            count = 0;
                            if(maze[i + 1][j] == 1){
                                count++;
                            }
                            if(maze[i - 1][j] == 1){
                                count++;
                            }
                            if(maze[i][j + 1] == 1){
                                count++;
                            }
                            if(maze[i][j - 1] == 1){
                                count++;
                            }

                            if(count == 1){
                                maze[i][j] = 1;
                            }
                        }
                    }
                }

            case 3:
                for(int i = SIZE - 2; i > 0; i--){
                    for(int j = SIZE - 2; j > 0; j--){
                        if(maze[i][j] == 0){
                            count = 0;
                            if(maze[i + 1][j] == 1){
                                count++;
                            }
                            if(maze[i - 1][j] == 1){
                                count++;
                            }
                            if(maze[i][j + 1] == 1){
                                count++;
                            }
                            if(maze[i][j - 1] == 1){
                                count++;
                            }

                            if(count == 1){
                                maze[i][j] = 1;
                            }
                        }
                    }
                }
        }
    }

    printm(maze);
    return(0);
}

void main(){
    srand(time(0));
    int maze[SIZE][SIZE];
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            maze[i][j] = 0;
        }
    }
    int start[] = {0, 0};
    int end[] = {0, 0};
    int success = mazeGenerator(maze, start, end);
}