#ifndef BIGDECIMALING2_BIGDECIMALING_H
#define BIGDECIMALING2_BIGDECIMALING_H

#include <bits/stdc++.h>
using namespace std;
class BigdecimalIng {
private:
    long long int decint;
    string decstr;
public:
    string getdecstr();
    BigdecimalIng() ;
    BigdecimalIng(string n);
    BigdecimalIng(const BigdecimalIng& c1);
    BigdecimalIng abs()const ;
    BigdecimalIng(long long int i);
    BigdecimalIng( BigdecimalIng& c1);
    BigdecimalIng operator-()const;
    BigdecimalIng operator+ (const BigdecimalIng &c1);
    BigdecimalIng operator-(const BigdecimalIng& c1);
    friend ostream& operator<<(ostream &out,BigdecimalIng &obj);
    void getBigDec();
    bool operator > (BigdecimalIng anotherBigInger);
    bool operator == (BigdecimalIng anotherDec);
    void operator= (BigdecimalIng anotherDec);
    bool ant_sign();
    int mx_size();
    int size();
    int sign();
    bool operator < (BigdecimalIng b);
    void removeleadingzeros();
    int compare(const BigdecimalIng& c1);
    int borrow(string &c1, int pos);
    bool isaddition(const string& num1, const string& num2);
    bool issubtraction(const string& num1, const string& num2);

};

#endif //BIGDECIMALING2_BIGDECIMALING_H
