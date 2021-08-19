#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int BOWSER_SURRENDER = 0;
const int MADBEAR = 1;
const int BANDIT = 2;
const int LORDLUPIN = 3;
const int ELF = 4;
const int TROLL = 5;
const int SHAMAN = 6;
const int VAJSH = 7;
const int EXCALIBUR = 8;
const int MYTHRIL = 9;
const int EXCALIPOOR = 10;
const int MUSHMARIO = 11;
const int MUSHFIB = 12;
const int MUSHGHOST = 13;
const int MUSHKNIGHT = 14;
const int REMEDY = 15;
const int PHOENIXDOWN = 16;
const int MERLIN = 17;
const int NINA_THE_RING = 18;
const int ABYSS = 19;
const int TIME_GATE = 20;
const int GUINEVERE_PRINCESS = 21;
const int LIGHTWING = 22;
const int ODIN = 23;
const int DRAGON_SWORD = 24;
const int BOWSER = 99;
const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;

#define epsilon 0.000000001

struct knight
{
    int HP;
    int DF;
    int level;
    int remedy;
    int gold;
    int phoenixdown;
};

// read data from input file to corresponding variables
// return 1 if successfully done, otherwise return 0

//-------------------------------------------------------------------------------------
//delete effect shaman_vajsh
void delete_SHA_VAJSH_ODIN(knight &theKnight, bool &tiny, bool &frog, int &count_SHA_VAJSH, int levelbefore, int MaxHP, int &count_meet_odin, bool &odin)
{
    //count down for Shaman and Vajsh effect
    {
        std::cout << "tiny: " << tiny << ", frog: " << frog << " ,count_SHA_VAJSH: " << count_SHA_VAJSH << endl;
        if (count_SHA_VAJSH != 0) // count down turn
        {
            count_SHA_VAJSH -= 1;
        }
        else
        {
            if (tiny == true) //delete tiny effect
            {
                count_SHA_VAJSH = -1;
                tiny = false;
                theKnight.HP *= 5;
                if (theKnight.HP > MaxHP)
                {
                    theKnight.HP = MaxHP;
                }
            }

            if (frog == true) //delete frog effect
            {
                count_SHA_VAJSH = -1;
                frog = false;
                theKnight.level = levelbefore;
            }
        }

        if (count_meet_odin != 0) // count down turn
        {
            count_meet_odin -= 1;
        }
        else
        {
            if (odin == true)
            {
                odin = false;
                count_meet_odin = -1;
            }
        }
    }
}

//excalibur
int getExcalibur(bool excalibur, bool tiny, bool frog, knight theKnight, int theEvent)
{
    int levelTemp;
    if (tiny == false && frog == false)
    {
        if (theEvent == 6 or theEvent == 7)
        {
            excalibur = false;
        }

        if (excalibur == true)
        {
            std::cout << "use excalibur to beat monster" << endl;
            levelTemp = 20;
        }
        else
        {
            std::cout << "use normal sword to fight monster" << endl;
            levelTemp = theKnight.level;
        }
    }
    else
    {
        std::cout << "use normal sword to fight monster" << endl;
        levelTemp = theKnight.level;
    }
    return levelTemp;
}

//excalipoor
int getExcalipoor(bool excalipoor, bool excalibur, bool tiny, bool frog, knight theKnight, int theEvent)
{
    int levelTemp;
    if (excalipoor == true)
    {
        std::cout << "use excalipoor to fight monster" << endl;
        levelTemp = 0;
    }
    else
    {
        levelTemp = getExcalibur(excalibur, tiny, frog, theKnight, theEvent);
    }
    return levelTemp;
}

//mushFib
int getmushFibonacci(knight &theKnight)
{
    int arr[1000];
    arr[0] = 0;
    arr[1] = 1;
    int n = 1;
    int a, b;
    do
    {
        arr[n + 1] = arr[n] + arr[n - 1];
        a = arr[n + 1] - theKnight.HP;
        b = theKnight.HP - arr[n];
        if (theKnight.HP < arr[n + 1])
        {
            theKnight.HP += arr[n];
            break;
        }
        else if (theKnight.HP == arr[n + 1])
        {
            theKnight.HP += arr[n + 1];
            break;
        }
        n++;
    } while (arr[n] < 999);

    return theKnight.HP;
}

//remedy or phoenixdown
void getRemedyOrPhoenixdown(int item, knight &theKnight, bool &tiny, bool &frog, int &count_SHA_VAJSH, int levelbefore, int MaxHP, int count_meet_odin, bool odin)
{
    item += 1;
    if (item > 99)
    {
        delete_SHA_VAJSH_ODIN(theKnight, tiny, frog, count_SHA_VAJSH, levelbefore, MaxHP, count_meet_odin, odin);
        item = 99;
    }
    else
    {
        delete_SHA_VAJSH_ODIN(theKnight, tiny, frog, count_SHA_VAJSH, levelbefore, MaxHP, count_meet_odin, odin);
        item -= 1;
    }
}

//nina the ring(HP)
knight GoldChangeToHP(knight &theKnight, int MaxHP, bool free_nina)
{
    int HPchange;
    HPchange = MaxHP - theKnight.HP;
    std::cout << "HPchange: " << HPchange << endl;
    if (theKnight.gold >= HPchange)
    {
        theKnight.HP += HPchange;
        if (free_nina == false)
        {
            theKnight.gold -= HPchange;
        }
    }
    else
    {
        theKnight.HP += theKnight.gold;
        if (free_nina == false)
        {
            theKnight.gold = 0;
        }
    }
    return theKnight;
}

double getabundancy(int number)
{
    double abundancy = 0;
    int numerator, denominator;
    numerator = 0;
    denominator = number;
    for (int i = 1; i <= number; i++)
    {
        if (number % i == 0)
        {
            numerator += i;
        }
    }
    abundancy = 1.0f * numerator / denominator;
    return abundancy;
}

//nguoilaido abyss
string getString(int i, int *arrEvent, knight theKnight)
{
    string part_1 = "";
    string part_2 = "";
    string code_nguoilaido = "";

    for (int j = 0; j < i; j++)
    {
        part_1 += to_string(arrEvent[j]);
    }

    part_2 = to_string(theKnight.HP) + to_string(theKnight.DF) + to_string(theKnight.level) + to_string(theKnight.remedy) + to_string(theKnight.gold) + to_string(theKnight.phoenixdown);

    code_nguoilaido = part_1 + part_2;
    return code_nguoilaido;
}

int checkSingleOrNot(string code_nguoilaido, int j)
{
    int count = 0;
    for (int i = 0; i < code_nguoilaido.length(); i++)
    {
        if (code_nguoilaido[i] == code_nguoilaido[j])
        {
            count += 1;
        }
    }
    return count;
}

string DeleteDuplicatedCharacter(string code_nguoilaido)
{
    int j;
    int new_count;
    string codefinal_nguoilaido = "";
    for (int j = 0; j < code_nguoilaido.length(); j++)
    {
        new_count = checkSingleOrNot(code_nguoilaido, j);
        if (new_count == 1)
        {
            codefinal_nguoilaido += code_nguoilaido[j];
        }
    }
    return codefinal_nguoilaido;
}

//timegate
void check_Time_gate(int &i, bool timegate, int return_when_dead)
{
    if (timegate = true)
    {
        i = return_when_dead;
    }
}

//meet guinevere
void check_meet_guinevere(bool meet_guinevere, int &i, int &alternate, int i_at_meetguinevere, int nEvent)
{
    if (meet_guinevere == false)
    {
        i = 0;
        alternate = nEvent;
    }
    else
    {
        i = -3;
        alternate = i_at_meetguinevere;
    }
}

void Make_whileloop_finite(bool meetguinevere, int &i, int &alternate, int &count_at_guinevere)
{
    if (meetguinevere == false)
    {
        i++;
    }
    else
    {
        count_at_guinevere++;
        alternate--;
    }
}

int get_levelO(int i, int count_at_guinevere, bool meet_guinevere, int i_at_meetguinevere)
{
    int b;
    int levelO;
    if (meet_guinevere == false)
    {
        b = (i + 1) % 10;
        levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b;
    }
    else
    {
        b = (i_at_meetguinevere + count_at_guinevere + 1) % 10;
        levelO = (i_at_meetguinevere + count_at_guinevere + 1) > 6 ? (b > 5 ? b : 5) : b;
    }
    return levelO;
}

//check SuperLancelot
void Check_SuperLancelot(bool &SuperLancelot, bool Lancelot, knight theKnight)
{
    if (theKnight.level % 2 == 0 and Lancelot == true)
    {
        SuperLancelot = true;
    }
}

//odin
int get_LevelTemp(bool odin, bool excalipoor, bool excalibur, bool tiny, bool frog, knight theKnight, int theEvent, bool ultimate_kamenrider, bool Paladin, bool Athur, bool SuperLancelot, bool Lancelot)
{
    int levelTemp;
    Check_SuperLancelot(SuperLancelot, Lancelot, theKnight);
    if (odin == true or ultimate_kamenrider == true or Paladin == true or Athur == true or SuperLancelot == true)
    {
        levelTemp = 20;
    }
    else
    {
        levelTemp = getExcalipoor(excalipoor, excalibur, tiny, frog, theKnight, theEvent);
    }
    return levelTemp;
}

//check kamenrider (câu y)
bool Check_KamenRider(knight theKnight)
{
    int z;
    for (int x = 3; x < theKnight.HP / 3; x++)
    {
        for (int y = x + 1; y < theKnight.HP / 2; y++)
        {
            z = theKnight.HP - x - y;
            if (pow(x, 2) + pow(y, 2) == pow(z, 2))
            {
                return true;
            }
        }
    }
    return false;
}

//check all the knights
void Check_Knight(int MaxHP, bool &Arthur, bool &Lancelot, bool &Paladin)
{
    switch (MaxHP)
    {
    case 999:
    {
        Arthur = true;
        break;
    }
    case 888:
    {
        Lancelot = true;
    }
    }

    if (MaxHP > 1)
    {
        for (int i = 2; i < MaxHP / 2; i++)
        {
            if (MaxHP % i == 0)
            {
                Paladin = false;
            }
        }
    }
    else if (MaxHP == 1)
    {
        Paladin = false;
    }
}
//start journey
int startJourney(knight theKnight, int nEvent, int *arrEvent)
{
    //variable for big startjourney
    int result;
    int MaxHP = theKnight.HP;
    int alternate;
    int i;

    //variables from 1 to 5
    int levelTemp;

    //variable for vajsh and shaman
    int count_SHA_VAJSH = -1, levelbefore;
    bool tiny = false, frog = false;

    //variable for items
    bool excalibur = false;
    bool mythrill = false;
    int count_for_reuse_mythrill = -1;
    int count_mythrill = -1;
    bool excalipoor = false;

    //variable for nina_the_ring
    double abundancy_HP;
    double abundancy_gold;
    bool free_nina = false;

    //variable for nguoi_lai_do_song_abyss
    string code_nguoilaido;
    string codefinal_nguoilaido;
    int sum_code = 0;

    //variable for timegate
    bool timegate = false;
    int return_when_dead;

    //variable for guinevere
    bool meet_guinevere = false;
    int i_at_meetguinevere;
    int count_at_meetguinevere = 0;

    //variable for odin
    bool odin = false, meet_odin = false;
    int count_meet_odin = -1;

    //variable for kamenrider
    bool kamenrider = false;
    bool ultimate_kamenrider = false;

    //variable for knight
    bool Arthur = false;
    bool Lancelot = false;
    bool SuperLancelot = false;
    bool Paladin = true;

    //-------------------------------------------------------------------
    //check knight
    Check_Knight(MaxHP, Arthur, Lancelot, Paladin);

    //check Kamenrider
    kamenrider = Check_KamenRider(theKnight);

    //set condition for while loop
    check_meet_guinevere(meet_guinevere, i, alternate, i_at_meetguinevere, nEvent);

    while (i < alternate)
    {

        int theEvent;

        if (meet_guinevere == false)
        {
            std::cout << "i: " << i << endl;
            std::cout << "alternate: " << alternate << endl;
            theEvent = arrEvent[i];
        }
        else
        {
            std::cout << "i: " << i << endl;
            std::cout << "alternate: " << alternate << endl;
            theEvent = arrEvent[alternate];
        }
        std::cout << "the event: " << theEvent << endl;
        //cases
        switch (theEvent)
        {
        case BOWSER_SURRENDER:
        {
            int result;
            result = theKnight.HP + theKnight.DF + theKnight.level + theKnight.remedy + theKnight.gold + theKnight.phoenixdown;
            return result;
            break;
        }

        case MADBEAR:
        {
            //deal with MadBear here
            int b, levelO, damage;
            b = (i + 1) % 10;
            levelO = get_levelO(i, count_at_meetguinevere, meet_guinevere, i_at_meetguinevere);

            levelTemp = get_LevelTemp(odin, excalipoor, excalibur, tiny, frog, theKnight, theEvent, ultimate_kamenrider, Paladin, Arthur, SuperLancelot, Lancelot);

            if (levelTemp > levelO)
            {
                std::cout << "won Madbear" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }
                else
                {
                    theKnight.level = 10;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
                }
                else
                {
                    theKnight.DF = 20;
                }

                if (theKnight.gold >= 490)
                {
                    theKnight.gold = 500;
                }
                else
                {
                    theKnight.gold += 10;
                }
            }
            else if (levelTemp < levelO)
            {
                std::cout << "lost to Madbear" << endl;
                damage = 1 * levelO * 10;

                //check mythrill
                if (mythrill == false)
                {
                    theKnight.HP = theKnight.HP + theKnight.DF - damage;
                }

                if (theKnight.HP <= 0)
                {
                    if (theKnight.phoenixdown > 0)
                    {
                        theKnight.phoenixdown--;
                        theKnight.HP = MaxHP;
                        tiny = false;
                        frog = false;
                        check_Time_gate(i, timegate, return_when_dead);
                    }
                    else if (theKnight.phoenixdown == 0)
                    {
                        return -1;
                    }
                }
            }
            else
            {
                std::cout << "draw Madbear" << endl;
            }
            break;
        }

        case BANDIT:
        {
            //deal with Bandit here
            int b, levelO, damage;
            b = (i + 1) % 10;
            levelO = get_levelO(i, count_at_meetguinevere, meet_guinevere, i_at_meetguinevere);
            std::cout << "levelO: " << levelO << endl;
            levelTemp = get_LevelTemp(odin, excalipoor, excalibur, tiny, frog, theKnight, theEvent, ultimate_kamenrider, Paladin, Arthur, SuperLancelot, Lancelot);

            if (levelTemp > levelO)
            {
                std::cout << "won Bandit" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }
                else
                {
                    theKnight.level = 10;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
                }
                else
                {
                    theKnight.DF = 20;
                }

                if (theKnight.gold >= 480)
                {
                    theKnight.gold = 500;
                }
                else
                {
                    theKnight.gold += 20;
                }
            }
            else if (levelTemp < levelO)
            {
                std::cout << "lost to Bandit" << endl;
                damage = 2.5 * levelO * 10;

                //check mythrill
                if (mythrill == false)
                {
                    theKnight.HP = theKnight.HP + theKnight.DF - damage;
                }

                if (theKnight.HP <= 0)
                {
                    if (theKnight.phoenixdown > 0)
                    {
                        theKnight.phoenixdown--;
                        theKnight.HP = MaxHP;
                        tiny = false;
                        frog = false;
                        check_Time_gate(i, timegate, return_when_dead);
                    }
                    else if (theKnight.phoenixdown == 0)
                    {
                        return -1;
                    }
                }
            }
            else
            {
                std::cout << "draw Bandit" << endl;
            }
            break;
        }

        case LORDLUPIN:
        {
            int b, levelO, damage;
            b = (i + 1) % 10;
            levelO = get_levelO(i, count_at_meetguinevere, meet_guinevere, i_at_meetguinevere);

            levelTemp = get_LevelTemp(odin, excalipoor, excalibur, tiny, frog, theKnight, theEvent, ultimate_kamenrider, Paladin, Arthur, SuperLancelot, Lancelot);
            if (levelTemp > levelO)
            {
                std::cout << "won Lupin" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }
                else
                {
                    theKnight.level = 10;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
                }
                else
                {
                    theKnight.DF = 20;
                }

                if (theKnight.gold >= 470)
                {
                    theKnight.gold = 500;
                }
                else
                {
                    theKnight.gold += 30;
                }
            }
            else if (levelTemp < levelO)
            {
                std::cout << "lost Lupin" << endl;
                damage = 5.5 * levelO * 10;

                //check mythrill
                if (mythrill == false)
                {
                    theKnight.HP = theKnight.HP + theKnight.DF - damage;
                }

                if (theKnight.HP <= 0)
                {
                    if (theKnight.phoenixdown > 0)
                    {
                        theKnight.phoenixdown--;
                        theKnight.HP = MaxHP;
                        tiny = false;
                        frog = false;
                        check_Time_gate(i, timegate, return_when_dead);
                    }
                    else if (theKnight.phoenixdown == 0)
                    {
                        return -1;
                    }
                }
            }
            else
            {
                std::cout << "draw Lupin" << endl;
            }
            break;
        }

        case ELF:
        {
            int b, levelO, damage;
            b = (i + 1) % 10;
            levelO = get_levelO(i, count_at_meetguinevere, meet_guinevere, i_at_meetguinevere);

            levelTemp = get_LevelTemp(odin, excalipoor, excalibur, tiny, frog, theKnight, theEvent, ultimate_kamenrider, Paladin, Arthur, SuperLancelot, Lancelot);

            if (levelTemp > levelO)
            {
                std::cout << "won elf" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }
                else
                {
                    theKnight.level = 10;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
                }
                else
                {
                    theKnight.DF = 20;
                }

                if (theKnight.gold >= 460)
                {
                    theKnight.gold = 500;
                }
                else
                {
                    theKnight.gold += 40;
                }
            }
            else if (levelTemp < levelO)
            {
                std::cout << "lost elf" << endl;
                damage = 7.5 * levelO * 10;

                //check mythrill
                if (mythrill == false)
                {
                    theKnight.HP = theKnight.HP + theKnight.DF - damage;
                }

                if (theKnight.HP <= 0)
                {
                    if (theKnight.phoenixdown > 0)
                    {
                        theKnight.phoenixdown--;
                        theKnight.HP = MaxHP;
                        tiny = false;
                        frog = false;
                        check_Time_gate(i, timegate, return_when_dead);
                    }
                    else if (theKnight.phoenixdown == 0)
                    {
                        return -1;
                    }
                }
            }
            else
            {
                std::cout << "draw elf" << endl;
            }
            break;
        }

        case TROLL:
        {
            int b, levelO, damage;
            b = (i + 1) % 10;
            levelO = get_levelO(i, count_at_meetguinevere, meet_guinevere, i_at_meetguinevere);

            levelTemp = get_LevelTemp(odin, excalipoor, excalibur, tiny, frog, theKnight, theEvent, ultimate_kamenrider, Paladin, Arthur, SuperLancelot, Lancelot);

            if (levelTemp > levelO)
            {
                std::cout << "won troll" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }
                else
                {
                    theKnight.level = 10;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
                }
                else
                {
                    theKnight.DF = 20;
                }

                if (theKnight.gold >= 450)
                {
                    theKnight.gold = 500;
                }
                else
                {
                    theKnight.gold += 50;
                }
            }
            else if (levelTemp < levelO)
            {
                std::cout << "lost troll" << endl;
                damage = 9.5 * levelO * 10;

                //check mythrill
                if (mythrill == false)
                {
                    theKnight.HP = theKnight.HP + theKnight.DF - damage;
                }

                //knight knocked out
                if (theKnight.HP <= 0)
                {
                    if (theKnight.phoenixdown > 0)
                    {
                        theKnight.phoenixdown--;
                        theKnight.HP = MaxHP;
                        tiny = false;
                        frog = false;
                        check_Time_gate(i, timegate, return_when_dead);
                    }
                    else if (theKnight.phoenixdown == 0)
                    {
                        return -1;
                    }
                }
            }
            else
            {
                std::cout << "draw troll" << endl;
            }
            break;
        }

        case SHAMAN:
        {
            int b, levelO, damage;
            b = (i + 1) % 10;
            levelO = get_levelO(i, count_at_meetguinevere, meet_guinevere, i_at_meetguinevere);
            if (count_SHA_VAJSH <= 0) //If the knight don't have the effect
            {
                std::cout << "fight shaman" << endl;
                levelTemp = get_LevelTemp(odin, excalipoor, excalibur, tiny, frog, theKnight, theEvent, ultimate_kamenrider, Paladin, Arthur, SuperLancelot, Lancelot);

                if (levelTemp > levelO) //Knight won
                {
                    std::cout << "win Shaman" << endl;

                    if (theKnight.level < 9)
                    {
                        theKnight.level += 2;
                    }
                    else
                    {
                        theKnight.level = 10;
                    }

                    if (theKnight.level < 19)
                    {
                        theKnight.DF += 2;
                    }
                    else
                    {
                        theKnight.DF = 20;
                    }
                }
                else if (levelTemp < levelO) //Knight lost
                {
                    std::cout << "lost shaman" << endl;
                    tiny = true;
                    count_SHA_VAJSH = 4;
                    if (theKnight.HP < 5)
                    {
                        theKnight.HP = 1;
                    }
                    else
                    {
                        theKnight.HP = theKnight.HP / 5;
                    }
                    //knight use remedy
                    if (theKnight.remedy > 0)
                    {
                        theKnight.remedy -= 1;
                        tiny = false;
                        count_SHA_VAJSH = 0;
                        //theKnight.HP = theKnight.HP * 5;
                    }
                }
            }
            break;
        }

        case VAJSH:
        {
            int b, levelO, damage;
            b = (i + 1) % 10;
            levelO = get_levelO(i, count_at_meetguinevere, meet_guinevere, i_at_meetguinevere);

            if (count_SHA_VAJSH <= 0) //If the knight don't have the effect
            {
                std::cout << "fight Vajsh" << endl;
                levelTemp = get_LevelTemp(odin, excalipoor, excalibur, tiny, frog, theKnight, theEvent, ultimate_kamenrider, Paladin, Arthur, SuperLancelot, Lancelot);

                if (levelTemp > levelO) //Knight won
                {
                    std::cout << "win Vajsh" << endl;

                    if (theKnight.level < 9)
                    {
                        theKnight.level += 2;
                    }
                    else
                    {
                        theKnight.level = 10;
                    }

                    if (theKnight.DF < 19)
                    {
                        theKnight.DF += 2;
                    }
                    else
                    {
                        theKnight.DF = 20;
                    }
                }
                else if (levelTemp < levelO) //Knight lost
                {
                    std::cout << "lost Vajsh" << endl;
                    frog = true;
                    count_SHA_VAJSH = 4;
                    levelbefore = theKnight.level;
                    theKnight.level = 1;

                    if (theKnight.remedy > 0)
                    {
                        theKnight.remedy -= 1;
                        frog = false;
                        count_SHA_VAJSH = 0;
                        // theKnight.level = levelbefore;
                    }
                }
            }
            break;
        }

        case EXCALIBUR:
        {
            std::cout << "get excalibur" << endl;
            excalibur = true;
            excalipoor = false;
            break;
        }

        case MYTHRIL:
        {
            if (count_for_reuse_mythrill <= 0)
            {
                std::cout << "get mythrill" << endl;
                if (mythrill == false)
                {
                    mythrill = true;
                    count_mythrill = 5;
                    count_for_reuse_mythrill = 7;
                }
            }
            else
            {
                std::cout << "not get mythrill" << endl;
            }
            break;
        }

        case EXCALIPOOR:
        {
            Check_SuperLancelot(SuperLancelot, Lancelot, theKnight);
            if (theKnight.level >= 5 or odin == true or kamenrider == true or Paladin == true or Arthur == true or SuperLancelot == true)
            {
                std::cout << "pass excalipoor" << endl;
                excalipoor = false;
            }
            else
            {
                std::cout << "get excalipoor" << endl;
                excalipoor = true;
                excalibur = false;
            }
            break;
        }

        case MUSHMARIO:
        {
            std::cout << "get mush mario" << endl;
            if (theKnight.HP >= (MaxHP - 50))
            {
                theKnight.HP = MaxHP;
            }
            else
            {
                theKnight.HP += 50;
            }

            break;
        }

        case MUSHFIB:
        {
            std::cout << "get mush fibonacci" << endl;
            theKnight.HP = getmushFibonacci(theKnight);
            break;
        }

        case MUSHGHOST:
        {
            if (odin == false or ultimate_kamenrider == false or Paladin == true)
            {
                std::cout << "get mush ghost" << endl;
                //lost HP
                if (theKnight.HP < 51)
                {
                    theKnight.HP = 1;
                }
                else
                {

                    theKnight.HP -= 50;
                }

                //lost DF
                if (theKnight.DF < 6)
                {
                    theKnight.DF = 1;
                }
                else
                {
                    theKnight.DF -= 5;
                }
            }

            break;
        }

        case MUSHKNIGHT:
        {
            std::cout << "get mush knight" << endl;
            MaxHP += 50;
            if (MaxHP > 999)
            {
                MaxHP = 999;
            }
            theKnight.HP = MaxHP;

            break;
        }

        case REMEDY:
        {
            std::cout << "get remedy" << endl;
            getRemedyOrPhoenixdown(theKnight.remedy, theKnight, tiny, frog, count_SHA_VAJSH, levelbefore, MaxHP, count_meet_odin, odin);
        }

        case PHOENIXDOWN:
        {
            std::cout << "get phoenixdown" << endl;
            getRemedyOrPhoenixdown(theKnight.remedy, theKnight, tiny, frog, count_SHA_VAJSH, levelbefore, MaxHP, count_meet_odin, odin);
            break;
        }

        case MERLIN:
        {
            std::cout << "meet merlin" << endl;
            //delete sha-vajsh effect
            if (count_SHA_VAJSH > 0)
            {
                tiny = false;
                frog = false;
                count_SHA_VAJSH = -1;
            }

            //levelup
            theKnight.level += 1;
            theKnight.level > 10 ? 10 : theKnight.level;

            //MaxHP
            theKnight.HP = MaxHP;

            break;
        }

        case NINA_THE_RING:
        {
            std::cout << "meet nina" << endl;

            abundancy_HP = getabundancy(theKnight.HP);
            abundancy_gold = getabundancy(theKnight.gold);

            if (abs(abundancy_HP - abundancy_gold) < epsilon)
            {
                std::cout << "friendly number" << endl;
                free_nina = true;
            }

            if (free_nina)
            {
                std::cout << "free nina" << endl;
                std::cout << "remove tiny or frog" << endl;

                if (tiny == true) //delete tiny effect
                {
                    count_SHA_VAJSH = -1;
                    tiny = false;
                    theKnight.HP *= 5;
                    if (theKnight.HP > MaxHP)
                    {
                        theKnight.HP = MaxHP;
                    }
                }

                if (frog == true) //delete frog effect
                {
                    count_SHA_VAJSH = -1;
                    frog = false;
                    theKnight.level = levelbefore;
                }

                //check if still have gold
                if (theKnight.gold > 0)
                {
                    std::cout << "still have money" << endl;
                    theKnight = GoldChangeToHP(theKnight, MaxHP, free_nina);
                    std::cout << theKnight.HP << " " << theKnight.DF << " " << theKnight.level << " " << theKnight.remedy << " " << theKnight.gold << " " << theKnight.phoenixdown << endl;
                }
            }
            else
            {
                std::cout << "normal nina" << endl;
                if (theKnight.gold >= 50)
                {
                    std::cout << "remove tiny or frog" << endl;
                    if (tiny == true) //delete tiny effect
                    {
                        count_SHA_VAJSH = -1;
                        tiny = false;
                        theKnight.HP *= 5;
                        if (theKnight.HP > MaxHP)
                        {
                            theKnight.HP = MaxHP;
                        }
                    }

                    if (frog == true) //delete frog effect
                    {
                        count_SHA_VAJSH = -1;
                        frog = false;
                        theKnight.level = levelbefore;
                    }

                    theKnight.gold -= 50;
                    std::cout << theKnight.HP << " " << theKnight.DF << " " << theKnight.level << " " << theKnight.remedy << " " << theKnight.gold << " " << theKnight.phoenixdown << endl;
                }

                //check if still have gold
                if (theKnight.gold > 0)
                {
                    std::cout << "still have money" << endl;
                    theKnight = GoldChangeToHP(theKnight, MaxHP, free_nina);
                }
            }

            break;
        }

        case ABYSS:
        {
            std::cout << "get to abyss" << endl;
            if (ultimate_kamenrider == true)
            {
                break;
            }

            if (theKnight.gold >= 50)
            {
                std::cout << "have money so get through" << endl;
                theKnight.gold -= 50;
                break;
            }
            else if (theKnight.level >= 7)
            {
                std::cout << "have level so get through " << endl;
                break;
            }

            //sovle the code for nguoilaidosongabyss
            std::cout << "solve the code for nguoilaido" << endl;
            code_nguoilaido = getString(i, arrEvent, theKnight);
            std::cout << code_nguoilaido << endl;

            codefinal_nguoilaido = DeleteDuplicatedCharacter(code_nguoilaido);
            std::cout << codefinal_nguoilaido << endl;

            //theknight live or die
            for (int i = 0; i < codefinal_nguoilaido.length(); i++)
            {
                sum_code += (codefinal_nguoilaido[i] - 48);
            }

            std::cout << "sum: " << sum_code << endl;
            if (sum_code <= 15)
            {
                return -1;
            }
            else
            {
                std::cout << "sovled code and get through abyss" << endl;
            }

            break;
        }

        case TIME_GATE:
        {
            timegate = true;
            return_when_dead = i;
        }

        case GUINEVERE_PRINCESS:
        {
            std::cout << "meet guinevere" << endl;
            meet_guinevere = true;
            i_at_meetguinevere = i;
            std::cout << "i at guinivere: " << i_at_meetguinevere << endl;
            check_meet_guinevere(meet_guinevere, i, alternate, i_at_meetguinevere, nEvent);
            break;
        }

        case LIGHTWING:
        {
            std::cout << "get wings" << endl;

            if ((nEvent - i + 1) < 0)
            {
                return result = theKnight.HP + theKnight.DF + theKnight.level + theKnight.remedy + theKnight.gold + theKnight.phoenixdown;
            }

            for (int j = i + 1; j < i + 4; j++)
            {
                if (arrEvent[j] == 0 or arrEvent[j] == 21)
                {
                    return result = theKnight.HP + theKnight.DF + theKnight.level + theKnight.remedy + theKnight.gold + theKnight.phoenixdown;
                }
            }
            i += 3;
            break;
        }

        case ODIN:
        {
            std::cout << "meet odin" << endl;
            if (meet_odin == false)
            {
                std::cout << "odin help" << endl;
                meet_odin = true;
                odin = true;
                count_meet_odin = 3;
            }
            else
            {
                std::cout << "odin don't help" << endl;
            }
            break;
        }

        case DRAGON_SWORD:
        {
            if (kamenrider == true)
            {
                ultimate_kamenrider = true;
                std::cout << "become ultimate kamenrider" << endl;
            }
            break;
        }

        case BOWSER:
        {
            if (Arthur == true or Paladin == true or Lancelot == true or ultimate_kamenrider == true)
            {
                theKnight.level = 10;
            }
            else
            {
                return -1;
            }
            break;
        }
        } //end switch

        //count down for Shaman and Vajsh effect
        std::cout << "count sha " << count_SHA_VAJSH << endl;
        delete_SHA_VAJSH_ODIN(theKnight, tiny, frog, count_SHA_VAJSH, levelbefore, MaxHP, count_meet_odin, odin);

        //count down for mythril item
        {
            if (count_mythrill != 0)
            {
                count_mythrill -= 1;
            }
            else
            {
                mythrill = false;
            }
        }
        count_for_reuse_mythrill--;

        //cout theKnight
        std::cout << theKnight.HP << " " << theKnight.DF << " " << theKnight.level << " " << theKnight.remedy << " " << theKnight.gold << " " << theKnight.phoenixdown << endl;

        Make_whileloop_finite(meet_guinevere, i, alternate, count_at_meetguinevere);
    } //end while loop

    //check again if tiny or frog just end or not
    if (count_SHA_VAJSH == 0)
    {
        if (tiny == true) //delete tiny effect
        {
            count_SHA_VAJSH = -1;
            tiny = false;
            theKnight.HP *= 5;
            if (theKnight.HP > MaxHP)
            {
                theKnight.HP = MaxHP;
            }
        }

        if (frog == true) //delete frog effect
        {
            count_SHA_VAJSH = -1;
            frog = false;
            theKnight.level = levelbefore;
        }
    }

    //compute result

    result = theKnight.HP + theKnight.DF + theKnight.level + theKnight.remedy + theKnight.gold + theKnight.phoenixdown;
    std::cout << "result: " << result << endl;
    return result;
}
