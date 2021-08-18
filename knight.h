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

//excalibur
int getExcalibur(bool excalibur, bool tiny, bool frog, knight theKnight)
{
    int levelTemp;
    if (tiny == false && frog == false)
    {
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
int getExcalipoor(bool excalipoor, bool excalibur, bool tiny, bool frog, knight theKnight)
{
    int levelTemp;
    if (excalipoor == true)
    {
        std::cout << "use excalipoor to fight monster" << endl;
        levelTemp = 0;
    }
    else
    {
        levelTemp = getExcalibur(excalibur, tiny, frog, theKnight);
    }
    return levelTemp;
}

//mushFib
int getmushFibonacci(knight theKnigth)
{
    int arr[1000];
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 1;
    int n = 2;
    do
    {
        arr[n] = arr[n - 1] + arr[n - 2];
        if ((arr[n] - theKnigth.HP) > 0)
        {
            theKnigth.HP = arr[n];
            break;
        }
        n++;
    } while (arr[n - 1] < 999);

    return theKnigth.HP;
}

//remedy or phoenixdown
int getRemedyOrPhoenixdown(int item)
{
    item += 1;
    item > 99 ? 99 : item;
    return item;
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

int startJourney(knight theKnight, int nEvent, int *arrEvent)
{
    int result;
    int MaxHP = theKnight.HP;

    //variables from 1 to 5
    int levelTemp;

    //variable for vajsh and shaman
    int count_SHA_VAJSH = -1, levelbefore;
    bool tiny = false, frog = false;

    //variable for items
    bool excalibur = false;
    bool mythrill = false;
    int count_mythrill = -1;
    bool excalipoor = false;

    //variable for nina_the_ring
    double abundancy_HP;
    double abundancy_gold;
    bool free_nina = false;

    std::cout << "nEvent: " << nEvent << endl;

    for (int i = 0; i < nEvent; i++)
    {
        std::cout << "i: " << i << endl;
        int theEvent = arrEvent[i];

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
            levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b;

            levelTemp = getExcalipoor(excalipoor, excalibur, tiny, frog, theKnight);

            if (levelTemp > levelO)
            {
                std::cout << "won Madbear" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }

                if (theKnight.level < 20)
                {
                    theKnight.DF += 1;
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
            levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b;

            levelTemp = getExcalipoor(excalipoor, excalibur, tiny, frog, theKnight);

            if (levelTemp > levelO)
            {
                std::cout << "won Bandit" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
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
            levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b;

            levelTemp = getExcalipoor(excalipoor, excalibur, tiny, frog, theKnight);

            if (levelTemp > levelO)
            {
                std::cout << "won Lupin" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
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
            levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b;

            levelTemp = getExcalipoor(excalipoor, excalibur, tiny, frog, theKnight);

            if (levelTemp > levelO)
            {
                std::cout << "won elf" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
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
            levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b;

            levelTemp = getExcalipoor(excalipoor, excalibur, tiny, frog, theKnight);

            if (levelTemp > levelO)
            {
                std::cout << "won troll" << endl;
                if (theKnight.level < 10)
                {
                    theKnight.level += 1;
                }

                if (theKnight.DF < 20)
                {
                    theKnight.DF += 1;
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
            levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b;
            if (count_SHA_VAJSH <= 0) //If the knight don't have the effect
            {
                std::cout << "fight shaman" << endl;
                if (theKnight.level > levelO) //Knight won
                {
                    std::cout << "win Shaman" << endl;
                    if (theKnight.level < 9)
                    {
                        theKnight.level += 2;
                    }

                    if (theKnight.level < 19)
                    {
                        theKnight.DF += 2;
                    }
                }
                else if (theKnight.level < levelO) //Knight lost
                {
                    std::cout << "lost shaman" << endl;
                    tiny = true;
                    count_SHA_VAJSH = 3;
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
            levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b;

            if (count_SHA_VAJSH <= 0) //If the knight don't have the effect
            {
                if (theKnight.level > levelO) //Knight won
                {
                    std::cout << "win Vajsh" << endl;
                    if (theKnight.level < 9)
                    {
                        theKnight.level += 2;
                    }

                    if (theKnight.level < 19)
                    {
                        theKnight.DF += 2;
                    }
                }
                else if (theKnight.level < levelO) //Knight lost
                {
                    std::cout << "lost Vajsh" << endl;
                    frog = true;
                    count_SHA_VAJSH = 3;
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
            break;
        }

        case MYTHRIL:
        {
            std::cout << "get mythrill" << endl;
            mythrill = true;
            count_mythrill = 5;
            break;
        }

        case EXCALIPOOR:
        {
            if (theKnight.level >= 5)
            {
                std::cout << "pass excalipoor" << endl;
                excalipoor = false;
            }
            else
            {
                std::cout << "get excalipoor" << endl;
                excalipoor = true;
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
            theKnight.remedy = getRemedyOrPhoenixdown(theKnight.remedy);
            break;
        }

        case PHOENIXDOWN:
        {
            std::cout << "get phoenixdown" << endl;
            theKnight.phoenixdown = getRemedyOrPhoenixdown(theKnight.phoenixdown);
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

            std::cout<<abundancy_gold<<endl;
            std::cout<<abundancy_HP<<endl;

            if (abs(abundancy_HP - abundancy_gold)<epsilon)
            {
                std::cout<<"friendly number"<<endl;
                free_nina = true;
            }

            std::cout<<free_nina<<endl;
            
            if (free_nina)
            {
                std::cout << "remove tiny or frog" << endl;
                count_SHA_VAJSH = -1;

                if (tiny == true) //delete tiny effect
                {
                    tiny = false;
                    theKnight.HP *= 5;
                    if (theKnight.HP > MaxHP)
                    {
                        theKnight.HP = MaxHP;
                    }
                }

                if (frog == true) //delete frog effect
                {
                    frog = false;
                    theKnight.level = levelbefore;
                }
            }
            else
            {
                if (theKnight.gold >= 50)
                {
                    if (count_SHA_VAJSH > 0)
                    {
                        std::cout << "remove tiny or frog" << endl;
                        count_SHA_VAJSH = -1;

                        if (tiny == true) //delete tiny effect
                        {
                            tiny = false;
                            theKnight.HP *= 5;
                            if (theKnight.HP > MaxHP)
                            {
                                theKnight.HP = MaxHP;
                            }
                        }

                        if (frog == true) //delete frog effect
                        {
                            frog = false;
                            theKnight.level = levelbefore;
                        }

                        theKnight.gold -= 50;
                    }
                    
                    //check if still have gold
                    if (theKnight.gold > 0)
                    {
                        std::cout << "still have money" << endl;
                        theKnight = GoldChangeToHP(theKnight, MaxHP, free_nina);
                    }
                }
            }
            break;
        }

        } //end switch

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
                    tiny = false;
                    theKnight.HP *= 5;
                    if (theKnight.HP > MaxHP)
                    {
                        theKnight.HP = MaxHP;
                    }
                }

                if (frog == true) //delete frog effect
                {
                    frog = false;
                    theKnight.level = levelbefore;
                }
            }
        }

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

        std::cout << theKnight.HP << " " << theKnight.DF << " " << theKnight.level << " " << theKnight.remedy << " " << theKnight.gold << " " << theKnight.phoenixdown << endl;
    }

    //check again if tiny or frog just end or not
    {
        if (count_SHA_VAJSH != 0) // count down turn
        {
            count_SHA_VAJSH -= 1;
        }
        else
        {
            if (tiny == true) //delete tiny effect
            {
                tiny = false;
                theKnight.HP *= 5;
                if (theKnight.HP > MaxHP)
                {
                    theKnight.HP = MaxHP;
                }
            }

            if (frog == true) //delete frog effect
            {
                frog = false;
                theKnight.level = levelbefore;
            }
        }
    }

    //compute result
    result = theKnight.HP + theKnight.DF + theKnight.level + theKnight.remedy + theKnight.gold + theKnight.phoenixdown;

    return result;
}
