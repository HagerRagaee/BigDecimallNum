#include <iostream>
#include "BigdecimalIng.h"
int main()
{
    BigdecimalIng k,d, r;
    k.getBigDec();
    d.getBigDec();
    k > d;
    k == d;
    k.size();
    k.sign();
    k = d;
    cout << k;
}
