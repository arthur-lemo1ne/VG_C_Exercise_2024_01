#include "Libraries.h"
#include "Monster.h"

enum BuffType
{
    NONE,
    HP,
    DODGE,
    ARMOR,
    DAMAGE
};

typedef struct Weapon
{
    int damage;
    int critChance;
    char name[50];
    int id;
}T_Weapon;

typedef struct Armor
{
    int damageReduction;
    char name[50];
    int id;
}T_Armor;

typedef struct Object
{
    char name[50];
    int value;
    int buffValue;
    enum BuffType bt;
    int id;
}T_Object;

typedef struct Player
{
    int hp;
    int gold;
    int dodge;
    T_Weapon weapon;
    T_Armor armor;
    T_Object inventory[10];
    int things;
}T_Player;

void DealDamage(T_Monster* target, T_Player player)
{
    //printf("%d", rand()% 100+1);
    int crit = rand()% 100+1;

    if(crit < player.weapon.critChance)
    {
        target->hp -= 2*player.weapon.damage;
        if(target->hp <= 0)
        {
            printf("you killed %s\n", target->name);
        }
        else
        {
            printf("you deal critical damage (%d) to %s\n", 2*player.weapon.damage, target->name);
            printf("%s has now %d HP\n", target->name, target->hp);
        }      
    }
    else
    {
        target->hp -= player.weapon.damage;
        if(target->hp <= 0)
        {
            printf("you killed %s\n", target->name);
        }
        else
        {
            printf("you deal %d damage to %s\n", player.weapon.damage, target->name);
            printf("%s has now %d HP\n", target->name, target->hp);
        }
    }
}

void TakeDamage(T_Monster From, T_Player* player)
{
    int dodged = rand()% 100+1;
    if(dodged > player->dodge)
    {
        player->hp -= (From.damage - player->armor.damageReduction);
        printf("You take %d damage\nYou have now %d HP\n", From.damage - player->armor.damageReduction, player->hp);
    }
    else
    {
        printf("you dodged that strike\n");
    }
}

void DefensivePosition(T_Player* player)
{
    printf("You take a defensive position\n");
    player->armor.damageReduction *= 2;
}

void EndOfDefensicePosition(T_Player* player)
{
    player->armor.damageReduction /= 2;
}

void Flee()
{
    printf("Be a man, face you fate, fleeing isn't an option\n");
}

void InitWeapons(T_Weapon* weapons)
{
    T_Weapon RS;
    for (int i = 0; i < 50; i++)
    {
        RS.name[i] = '\0';
    }
    
    RS.name[0] = 'R';
    RS.name[1] = 'u';
    RS.name[2] = 's';
    RS.name[3] = 't';
    RS.name[4] = 'y';
    RS.name[5] = ' ';
    RS.name[6] = 'S';
    RS.name[7] = 'w';
    RS.name[8] = 'o';
    RS.name[9] = 'r';
    RS.name[10] = 'd';
    RS.damage = 3;
    RS.critChance = 5;
    RS.id = 1;
    weapons[0] = RS;
}

void InitArmors(T_Armor* armors)
{
    T_Armor AdvSh;
    for (int i = 0; i < 50; i++)
    {
        AdvSh.name[i] = '\0';
    }
    AdvSh.name[0] = 'A';
    AdvSh.name[1] = 'd';
    AdvSh.name[2] = 'v';
    AdvSh.name[3] = 'e';
    AdvSh.name[4] = 'n';
    AdvSh.name[5] = 't';
    AdvSh.name[6] = 'u';
    AdvSh.name[7] = 'r';
    AdvSh.name[8] = 'e';
    AdvSh.name[9] = 'r';
    AdvSh.name[10] = '\'';
    AdvSh.name[11] = 's';
    AdvSh.name[12] = ' ';
    AdvSh.name[13] = 'S';
    AdvSh.name[14] = 'h';
    AdvSh.name[15] = 'e';
    AdvSh.name[16] = 'e';
    AdvSh.name[17] = 't';
    AdvSh.name[18] = 's';

    AdvSh.id = 6;
    
    
    AdvSh.damageReduction = 2;
    armors[0] = AdvSh;
}

void DestroyObject(T_Object* obj)
{
    for (size_t i = 0; i < 50; i++)
    {
        obj->name[i] = '\0';
    }
    obj->name[0] = 'N';
    obj->name[1] = 'O';
    obj->name[2] = 'N';
    obj->name[3] = 'E';
    obj->bt = NONE;
    obj->buffValue = 0;
    obj->value = 0;
    obj->id = 100;
}

void InitInventory(T_Player* player)
{
    for(int i = 0; i < 10; i++)
    {
        DestroyObject(&player->inventory[i]);
    }
}

void DisplayPlayer(T_Player player)
{
    printf("========== YOUR STATS ==========\nHP: %d\nWeapon: %s\nWeapon damage: %d\nWeapon Crit Chance: %d %%\nArmor: %s\nArmor Protection: %d\nDodge Chance: %d %%\n================================\n",player.hp, player.weapon.name, player.weapon.damage, player.weapon.critChance, player.armor.name, player.armor.damageReduction, player.dodge);
}

void DisplayObject(T_Object obj)
{
    printf("%s\n", obj.name);
    printf("Value %d\n", obj.value);
    switch (obj.bt)
    {
        case NONE:
            break;
        case HP:
            printf("+%d on Health\n", obj.buffValue);
            break;
        case DODGE:
            printf("+%d on Dodge\n", obj.buffValue);
            break;
        case ARMOR:
            printf("+%d on Armor\n", obj.buffValue);
            break;
        case DAMAGE:
            printf("+%d on Damage\n", obj.buffValue);
            break;
        default:
            break;
    }
    
}

void DisplayInvetory(T_Player player)
{
    printf("======== YOUR INVENTORY ========\n");
    printf("Gold: %d\n", player.gold);
    for(int i = 0; i < 10; i++)
    {
        printf("%d:",i);
        DisplayObject(player.inventory[i]);
    }
}

void GetObject(T_Object obj)
{

}

void InitObject(T_Object* objects)
{
    
}