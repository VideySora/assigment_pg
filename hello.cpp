#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>
using namespace std;

double getabundancy(int number)
{
    double abundancy = 0;
    int numerator, denominator;
    numerator = 0;
    denominator = number;
    cout << denominator<<endl;
    for (int i = 1; i <= number; i++)
    {
        cout<<i<<endl;
        if (number % i == 0)
        {
            numerator += i;
        }
    }
    abundancy = 1.0f * numerator / denominator;
    return abundancy;
}

int main()
{
    std::cout<<"hello world"<<endl;
    //char *b[3] = new char arr[6];
    //char arr[6]={'H', 'e', 'l', 'l', 'o', 'a'};

   // cout << b[3] << endl;
    //cout << *b[3] << endl;

    // printf("\nab");
    // printf("\bsi");
    // printf("\rha");
    int arr[3]={1,6,18};
    string chuoi_1="";
    
    for (int j = 0; j < 3; j++)
    {
        chuoi_1 += to_string(arr[j]); 
    }
    cout<<chuoi_1<<endl;

    //lấy chuỗi sự kiện;
    //lấy chuỗi chỉ số;

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

    //variable for the abyss
    string code_nguoilaido;

    case ABYSS:
        {
            if (theKnight.gold >= 50)
            {
                theKnight.gold -= 50;
                break;
            }
            else if (theKnight.level >= 7)
            {
                break;
            }

            //sovle the code for nguoilaidosongabyss
            code_nguoilaido = getString(i, arrEvent, theKnight);
            std::cout << code_nguoilaido << endl;
            break;
        }
}
}
