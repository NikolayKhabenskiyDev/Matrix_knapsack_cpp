#ifndef SAFEINPUT_H
#define SAFEINPUT_H

#include <iostream>

int get_int()
{
    int num=0;
    int minus=0;
    char letter=getchar();
    while(!isdigit(letter))
    {
        if (letter=='\n')
        {
            std::cout<<"Print number"<<std::endl;
        }
        if (letter=='-')
        {
            minus=1;
        }
        else
        {
            minus=0;
        }
        letter=getchar();
    }
    num=letter-48;
    letter=getchar();
    while(isdigit(letter))
    {
        num*=10;
        num+=letter-48;
        letter=getchar();
    }
    if (minus==1)
    {
        num*=-1;
    }
    while(letter!='\n')
    {
        letter=getchar();
    }
    return num;
}

#endif
