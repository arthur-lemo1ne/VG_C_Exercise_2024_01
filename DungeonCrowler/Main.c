#include "Libraries.h"
#include "Player.h"
#include "Maze.h"

void Save(T_Player p, int x, int y)
{
    FILE* Svf;
    Svf = fopen("/Users/arthur_lemoine/Documents/GitHub/VG_C_Exercise_2024_01/DungeonCrowler/save.txt", "w");
    if(Svf == NULL)
    {
        printf("ISSUE");
    }
    else
    {
        fputc(p.weapon.id+60, Svf);
        fputc(p.armor.id+60, Svf);
        fputc(p.hp+60, Svf);
        fputc(p.gold+60, Svf);
        fputc(p.things+60, Svf);
        for(int i = 0; i < p.things; i++)
        {
            fputc(p.inventory[i].id+60,Svf);
        }
        fputc(x+60, Svf);
        fputc(y+60, Svf);
        fflush(Svf);

        fclose(Svf);
    }
}

void Load(T_Player* p, int* x, int* y, T_Armor* armors, T_Weapon* weapons, T_Object* objects)
{
    FILE* Svf;
    Svf = fopen("/Users/arthur_lemoine/Documents/GitHub/VG_C_Exercise_2024_01/DungeonCrowler/save.txt", "r");
    if(Svf == NULL)
    {
        printf("ISSUE");
    }
    else
    {
        char ch;
        ch = fgetc(Svf)-60;
        for (int i = 0; i < 10; i++)
        {
            if(weapons[i].id == ch)
            {
                p->weapon = weapons[i];
                break;
            }
        }
        ch = fgetc(Svf)-60;
        for (int i = 0; i < 10; i++)
        {
            if(armors[i].id == ch)
            {
                p->armor = armors[i];
                break;
            }
        }
        ch = fgetc(Svf)-60;
        p->hp = ch;
        ch = fgetc(Svf)-60;
        p->gold = ch;
        ch = fgetc(Svf)-60;
        p->things = ch;
        for (int i = 0; i < p->things; i++)
        {
            ch = fgetc(Svf)-60;
            for (int j = 0; j < 10; j++)
            {
                if(objects[j].id==ch)
                {
                    p->inventory[i] = objects[j];
                }
            } 
        }
        ch = fgetc(Svf)-60;
        x = ch;
        ch = fgetc(Svf)-60;
        y = ch;

        fclose(Svf);
    }
}

int StartFight(T_Player player,T_Monster monster)
{
    while(player.hp > 0 && monster.hp > 0)
    {
        int defFlag = 0;
        printf("========== Your Turn ==========\n");
        //print menu
        printf("1: Atack\n2: Defensive Position\n3: Analyse Enemy\n4: Flee\n");
        int i;
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            DealDamage(&monster, player);
            break;
        case 2:
            DefensivePosition(&player);
            defFlag = 1;
            break;
        case 3:
            printf("You take the time to analyse your oponent\n");
            printf("=========\n");
            printf("%s\n", monster.name);
            printf("HP: %d\n", monster.hp);
            printf("Atack: %d\n", monster.damage);
            printf("Armor: %d\n", monster.damegeReduction);
            printf("=========\n");
            break;
        case 4:
            Flee();
            break;
        default:
            break;
        }
        printf("========== End Of Your Turn ==========\n");

        if(monster.hp > 0)
        {
            TakeDamage(monster, &player);
        }
        if(defFlag)
        {
            EndOfDefensicePosition(&player);
        }
    }
    if (player.hp <=0)
        return 0;
    if(monster.hp <= 0)
        return 1;
    return 0;
}

int main(void)
{
    // Random initialisation
    srand(time(0));

    // Maze initialisation
    T_Maze maze;
    Initialisation(&maze);
    T_Room currentRoom;
    int x = 0;
    int y = 0;

    // player initialisation
    T_Player player;
    T_Armor armors[10];
    T_Weapon weapons[10];
    T_Object objects[10];
    InitWeapons(weapons);
    InitArmors(armors);
    InitInventory(&player);
    InitObject(&objects);
    player.hp = 20;
    player.weapon = weapons[0];
    player.armor = armors[0];
    player.dodge = 10;
    player.gold = 0;
    player.things = 0;
    int Win = 0;

    // monster initialisation
    T_Monster monsters[10];
    InitMonsters(monsters);
    int currentMonster;
    system("clear");
    printf("Before you start playing, be sure to change the path for the save file in main.c line 8 & 35\n");
    char* enter;
    scanf("%s",&enter);




    system("clear");
    printf("\n\nYou are lost in a long forgotten dungeon...\nWill you be able to escape ?\n\n");


    // Gameplay Loop
    while(Win == 0 && player.hp > 0)
    {
        maze.rooms[x][y].visited = 1;
        currentRoom = maze.rooms[x][y];
        DisplayRoom(currentRoom);
        switch (currentRoom.content)
        {
        case Empty:
            printf("You enter a dark empty room\n");
            break;
        case End:
            Win = 1;
            break;
        case Monster:
            currentMonster = rand()% 2;
            printf("You encounter the %s\n", monsters[currentMonster].name); // needs choice of monster
            int result = StartFight(player, monsters[currentMonster]);
            if(!result)
            {
                player.hp = 0;
            }
            else
            {
                maze.rooms[x][y].content = Empty;
                RoomInit(&maze.rooms[x][y]);
                int g = rand()%50;
                player.gold += g;
                printf("You found %d gold on %s\n",g,monsters[currentMonster].name);
            }
            DisplayRoom(currentRoom);
            break;
        case Shop:
            printf("You found a small shop lost in the dungeon\n");
            //StartShop(); // needs implementation
            break;
        case Treasure:
            printf("You found a chest, alone, sitting there in the room\n");
            //RandomTreasure(); // Needs implementation
        default:
            break;
        }
        if(player.hp < 1)
        {
            break;
        }
        printf("========== MENU =========\n");
        int dir = 1;
        
        if(currentRoom.entryPoints[0] == 1)
        {
            printf("%d Go North\n", dir);
            dir++;
        }
        if(currentRoom.entryPoints[1] == 1)
        {
            printf("%d Go East\n", dir);
            dir++;
        }
        if(currentRoom.entryPoints[2] == 1)
        {
            printf("%d Go South\n", dir);
            dir++;
        }
        if(currentRoom.entryPoints[3] == 1)
        {
            printf("%d Go West\n", dir);
            dir++;
        }
        printf("%d Display Map\n", dir);
        printf("%d Display player's Stats\n", dir+1);
        printf("%d Display player's Inventory\n", dir+2);
        printf("%d Save\n", dir+3);
        printf("%d Load\n", dir+4);
        printf("=========================\n");
        int choice;
        scanf("%d", &choice);
        system("clear");
        if(choice < dir)
        {
            int flag = 0;
            for(int i = 0; i < 4; i++)
            {
                if(currentRoom.entryPoints[i] == 1)
                {
                    flag ++;
                }
                if(flag == choice)
                {
                    if(i == 0)
                    {
                        printf("You go North\n");
                        if(x>0) {x --;}
                        break;
                    }
                    if(i == 1)
                    {
                        printf("You go East\n");
                        if(y<19) {y ++;}
                        break;
                    }
                    if(i == 2)
                    {
                        printf("You go South\n");
                        if(x<9) {x ++;}
                        break;
                    }
                    if(i == 3)
                    {
                        printf("You go West\n");
                        if(y>0) {y --;}
                        break;
                    }
                }
            }
        }
        if(choice == dir)
        {
            DisplayMaze(&maze);
        }
        if(choice == dir+1)
        {
            DisplayPlayer(player);
        }
        if(choice == dir+2)
        {
            DisplayInvetory(player);
        }
        if(choice == dir+3)
        {
            Save(player, x, y);
        }
        if(choice == dir+4)
        {
            Load(&player,&x,&y,armors,weapons,objects);
        }
        
    }
    
    
    

    
    return 0;
}