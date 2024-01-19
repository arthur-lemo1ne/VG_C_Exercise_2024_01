#include "Libraries.h"

// Maze will be a 5x5 grid
// Room will be 10x10 grids as bellow
//   ---  ---
//  |********|
//  |********|
//  |********|
//  |********|
//   --------
//
//
//
//

char hiddenLayout[10][20] = {{' ','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',' '},{'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},{'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},{'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},{'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},{'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},{'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},{'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},{'|','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','|'},{' ','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',' '}};

enum RoomContent
{
    Empty,
    Monster,
    Shop,
    Treasure,
    End,
};

typedef struct Room
{
    int id;
    int visited;
    int entryPoints[4];
    char layout[10][20];
    enum RoomContent content;
}T_Room;

typedef struct Maze
{
    T_Room rooms[5][5];
}T_Maze;

void DisplayRoom(T_Room room)
{
    for(int i = 0; i< 10; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            printf("%c",room.layout[i][j]);
        }
        printf("\n");
    }
}

void DisplayMaze(T_Maze* maze)
{
    for(int i = 0; i< 5; i++)
    {
        for(int h = 0; h < 10; h++)
        {
            for(int j = 0; j < 5; j++)
            { 
                for(int k = 0; k < 20; k++)
                {
                    if(maze->rooms[i][j].visited)
                    {
                        printf("%c",maze->rooms[i][j].layout[h][k]);
                    }
                    else
                    {
                        printf("%c",hiddenLayout[h][k]);
                    }
                }
            }
            printf("\n");
        }
    }
}

void RoomInit(T_Room *room)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if((i== 0 || i == 9) && (j == 0 || j == 19))
            {
                room->layout[i][j] = ' ';
            }
            else
            {
                if(i == 0 || i == 9)
                {
                    room->layout[i][j] = '-';
                }
                else
                {
                    if(j == 0 || j == 19)
                    {
                        room->layout[i][j] = '|';
                    }
                    else
                    {
                        room->layout[i][j] = ' ';
                    }  
                }   
            }
        }
    }
    if(room->entryPoints[0] == 1)
    {
        room->layout[0][9] = '|';
        room->layout[0][10] = '|';
    }
    if(room->entryPoints[1] == 1)
    {
        room->layout[4][19] = '-';
        room->layout[5][19] = '-';
    }
    if(room->entryPoints[2] == 1)
    {
        room->layout[9][9] = '|';
        room->layout[9][10] = '|';
    }
    if(room->entryPoints[3] == 1)
    {
        room->layout[4][0] = '-';
        room->layout[5][0] = '-';
    }
    if(room->content == Shop)
    {
        for(int i = 7; i<13;i++)
        {
            room->layout[2][i] = '_';
            room->layout[4][i] = '_';
            room->layout[6][i] = '-';
            room->layout[7][i] = '_';
        }
        for(int i = 3; i < 8; i++)
        {
            room->layout[i][6] = '|';
            room->layout[i][13] = '|';
        }
        room->layout[3][8] = 'S';
        room->layout[3][9] = 'H';
        room->layout[3][10] = 'O';
        room->layout[3][11] = 'P';
        room->layout[5][9] = 'o';
        room->layout[5][10] = '/';
    }
    if(room->content == Treasure)
    {
        for(int i = 7; i<13;i++)
        {
            room->layout[4][i] = '_';
            room->layout[5][i] = '_';
            room->layout[7][i] = '_';
        }
        room->layout[5][6] = '/';
        room->layout[6][6] = '|';
        room->layout[7][6] = '|';
        room->layout[5][13] = '\\';
        room->layout[6][13] = '|';
        room->layout[7][13] = '|';
    }
    if(room->content == Monster)
    {
        room->layout[4][7] = '\\';
        room->layout[4][8] = '_';
        room->layout[4][9] = '{';
        room->layout[4][11] = ')';
        room->layout[5][9] = '(';
        room->layout[5][11] = ')';
        room->layout[6][9] = '/';
        room->layout[6][11] = '|';
    }
    if(room->content == End)
    {
        for(int i = 6; i < 13; i ++)
        {
            room->layout[2][i] = '_';
            room->layout[8][i] = '_';
        }
        for(int i = 3; i < 9; i ++)
        {
            room->layout[i][5] = '|';
            room->layout[i][9] = '|';
            room->layout[i][13] = '|';
        }
        room->layout[2][9] = '_';
        room->layout[3][5] = '/';
        room->layout[3][13] = '\\';
    }
}

void Initialisation(T_Maze *maze)
{
    // Room 01
    T_Room room01;
    room01.entryPoints[0] = 0;
    room01.entryPoints[1] = 1;
    room01.entryPoints[2] = 0;
    room01.entryPoints[3] = 0;
    room01.content = Empty;
    maze->rooms[0][0] = room01;
    // Room 02
    T_Room room02;
    room02.entryPoints[0] = 0;
    room02.entryPoints[1] = 1;
    room02.entryPoints[2] = 1;
    room02.entryPoints[3] = 1;
    room02.content = Monster;
    maze->rooms[0][1] = room02;
    // Room 03
    T_Room room03;
    room03.entryPoints[0] = 0;
    room03.entryPoints[1] = 0;
    room03.entryPoints[2] = 1;
    room03.entryPoints[3] = 1;
    room03.content = Empty;
    maze->rooms[0][2] = room03;
    // Room 04
    T_Room room04;
    room04.entryPoints[0] = 0;
    room04.entryPoints[1] = 1;
    room04.entryPoints[2] = 1;
    room04.entryPoints[3] = 0;
    room04.content = Monster;
    maze->rooms[0][3] = room04;
    // Room 05
    T_Room room05;
    room05.entryPoints[0] = 0;
    room05.entryPoints[1] = 0;
    room05.entryPoints[2] = 0;
    room05.entryPoints[3] = 1;
    room05.content = Treasure;
    maze->rooms[0][4]= room05;
    // Room 06
    T_Room room06;
    room06.entryPoints[0] = 0;
    room06.entryPoints[1] = 1;
    room06.entryPoints[2] = 0;
    room06.entryPoints[3] = 0;
    room06.content = Treasure;
    maze->rooms[1][0] = room06;
    // Room 07
    T_Room room07;
    room07.entryPoints[0] = 1;
    room07.entryPoints[1] = 0;
    room07.entryPoints[2] = 0;
    room07.entryPoints[3] = 1;
    room07.content = Empty;
    maze->rooms[1][1] = room07;
    // Room 08
    T_Room room08;
    room08.entryPoints[0] = 1;
    room08.entryPoints[1] = 1;
    room08.entryPoints[2] = 1;
    room08.entryPoints[3] = 0;
    room08.content = Monster;
    maze->rooms[1][2] = room08;
    // Room 09
    T_Room room09;
    room09.entryPoints[0] = 1;
    room09.entryPoints[1] = 0;
    room09.entryPoints[2] = 0;
    room09.entryPoints[3] = 1;
    room09.content = Empty;
    maze->rooms[1][3] = room09;
    // Room 10
    T_Room room10;
    room10.entryPoints[0] = 0;
    room10.entryPoints[1] = 0;
    room10.entryPoints[2] = 1;
    room10.entryPoints[3] = 0;
    room10.content = Shop;
    maze->rooms[1][4] = room10;
    // Room 11
    T_Room room11;
    room11.entryPoints[0] = 0;
    room11.entryPoints[1] = 1;
    room11.entryPoints[2] = 1;
    room11.entryPoints[3] = 0;
    room11.content = Empty;
    maze->rooms[2][0] = room11;
    // Room 12
    T_Room room12;
    room12.entryPoints[0] = 0;
    room12.entryPoints[1] = 1;
    room12.entryPoints[2] = 0;
    room12.entryPoints[3] = 1;
    room12.content = Monster;
    maze->rooms[2][1] = room12;
    // Room 13
    T_Room room13;
    room13.entryPoints[0] = 1;
    room13.entryPoints[1] = 0;
    room13.entryPoints[2] = 0;
    room13.entryPoints[3] = 1;
    room13.content = Empty;
    maze->rooms[2][2] = room13;
    // Room 14
    T_Room room14;
    room14.entryPoints[0] = 0;
    room14.entryPoints[1] = 1;
    room14.entryPoints[2] = 1;
    room14.entryPoints[3] = 0;
    room14.content = Monster;
    maze->rooms[2][3] = room14;
    // Room 15
    T_Room room15;
    room15.entryPoints[0] = 1;
    room15.entryPoints[1] = 0;
    room15.entryPoints[2] = 1;
    room15.entryPoints[3] = 1;
    room15.content = Empty;
    maze->rooms[2][4] = room15;
    // Room 16
    T_Room room16;
    room16.entryPoints[0] = 1;
    room16.entryPoints[1] = 1;
    room16.entryPoints[2] = 1;
    room16.entryPoints[3] = 0;
    room16.content = Monster;
    maze->rooms[3][0] = room16;
    // Room 17
    T_Room room17;
    room17.entryPoints[0] = 0;
    room17.entryPoints[1] = 1;
    room17.entryPoints[2] = 0;
    room17.entryPoints[3] = 1;
    room17.content = Empty;
    maze->rooms[3][1] = room17;
    // Room 18
    T_Room room18;
    room18.entryPoints[0] = 0;
    room18.entryPoints[1] = 1;
    room18.entryPoints[2] = 1;
    room18.entryPoints[3] = 1;
    room18.content = Monster;
    maze->rooms[3][2] = room18;
    // Room 19
    T_Room room19;
    room19.entryPoints[0] = 1;
    room19.entryPoints[1] = 0;
    room19.entryPoints[2] = 0;
    room19.entryPoints[3] = 1;
    room19.content = Empty;
    maze->rooms[3][3] = room19;
    // Room 20
    T_Room room20;
    room20.entryPoints[0] = 1;
    room20.entryPoints[1] = 0;
    room20.entryPoints[2] = 0;
    room20.entryPoints[3] = 0;
    room20.content = Empty;
    maze->rooms[3][4] = room20;
    // Room 21
    T_Room room21;
    room21.entryPoints[0] = 1;
    room21.entryPoints[1] = 1;
    room21.entryPoints[2] = 0;
    room21.entryPoints[3] = 0;
    room21.content = Empty;
    maze->rooms[4][0] = room21;
    // Room 22
    T_Room room22;
    room22.entryPoints[0] = 0;
    room22.entryPoints[1] = 0;
    room22.entryPoints[2] = 0;
    room22.entryPoints[3] = 1;
    room22.content = Treasure;
    maze->rooms[4][1] = room22;
    // Room 23
    T_Room room23;
    room23.entryPoints[0] = 1;
    room23.entryPoints[1] = 1;
    room23.entryPoints[2] = 0;
    room23.entryPoints[3] = 0;
    room23.content = Empty;
    maze->rooms[4][2] = room23;
    // Room 24
    T_Room room24;
    room24.entryPoints[0] = 0;
    room24.entryPoints[1] = 1;
    room24.entryPoints[2] = 0;
    room24.entryPoints[3] = 1;
    room24.content = Monster;
    maze->rooms[4][3] = room24;
    // Room 2
    T_Room room25;
    room25.entryPoints[0] = 0;
    room25.entryPoints[1] = 0;
    room25.entryPoints[2] = 0;
    room25.entryPoints[3] = 1;
    room25.content = End;
    maze->rooms[4][4] = room25;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            maze->rooms[i][j].id = i+j;
            maze->rooms[i][j].visited = 0;
            RoomInit(&maze->rooms[i][j]);
        }
    }

}

// Shop 
// ------------------ 
//|                  |
//|      ______      |
//|     | SHOP |     |
//|     |______|     |
//|     |  o/  |     |
//|     |------|     |
//|     |______|     |
//|                  |
//|                  |
// ------------------ 

// Treasure
// ------------------ 
//|                  |
//|                  |
//|                  |
//|      ______      |
//|     /______\     |
//|     |      |     |
//|     |______|     |
//|                  |
//|                  |
// ------------------ 

// Monster
// ------------------ 
//|                  |
//|                  |
//|                  |
//|     \_{ )        |
//|       ( )        |
//|       / |        |
//|                  |
//|                  |
//|                  |
// ------------------ 

// End
// ------------------ 
//|                  |
//|     ___Ω___      |
//|    /   |   \     |
//|    |   |   |     |
//|    |   |   |     |
//|    |   |   |     |
//|    |   |   |     |
//|    |___|___|     |
//|                  |
// ------------------ 