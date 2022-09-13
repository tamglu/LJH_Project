#include "bar.h"

Bar::Bar()
{
    direction=0;
    bar_mv=175;
    bar_select=2;
    HP=3;
}
void Bar::movement(int d)
{
    bar_mv+=d*2;
    if(bar_mv>=450-(50*bar_select))
    {
        bar_mv=450-(50*bar_select);
    }
    else if(bar_mv<=0)
    {
        bar_mv=0;
    }
}
