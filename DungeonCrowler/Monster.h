#include "Libraries.h"

typedef struct Monster
{
    int hp;
    int damage;
    int damegeReduction;
    char name[50];
}T_Monster;

void InitMonsters(T_Monster* monsters)
{
    T_Monster Skelt;
    for (int i = 0; i < 50; i++)
    {
        Skelt.name[i] = '\0';
    }
    Skelt.name[0] = 'S';
    Skelt.name[1] = 'k';
    Skelt.name[2] = 'e';
    Skelt.name[3] = 'l';
    Skelt.name[4] = 'e';
    Skelt.name[5] = 't';
    Skelt.name[6] = 'o';
    Skelt.name[7] = 'n';
    Skelt.damage = 4;
    Skelt.damegeReduction = 1;
    Skelt.hp = 10;
    monsters[0] = Skelt;

    T_Monster VampBat;
    for (int i = 0; i < 50; i++)
    {
        VampBat.name[i] = '\0';
    }
    VampBat.name[0] = 'V';
    VampBat.name[1] = 'a';
    VampBat.name[2] = 'm';
    VampBat.name[3] = 'p';
    VampBat.name[4] = 'i';
    VampBat.name[5] = 'r';
    VampBat.name[6] = 'e';
    VampBat.name[7] = ' ';
    VampBat.name[8] = 'B';
    VampBat.name[9] = 'a';
    VampBat.name[10] = 't';
    VampBat.hp = 5;
    VampBat.damage = 2;
    VampBat.damegeReduction = 0;
    monsters[1] = VampBat;
}