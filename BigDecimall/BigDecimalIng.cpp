
#include "BigdecimalIng.h"
#include "iostream"
#include "string"
void BigdecimalIng::removeleadingzeros() {
    int startpos=0;
    if (decstr[0]=='-')
    {
        startpos=1;
    }
    int len=decstr.length();

    for (int i=startpos;i<len;i++)
    {
        if ((decstr[i]=='0')||(decstr[i]=='+'))
        {
            decstr.erase(i,1);
            len=len-1;
            i=startpos-1;
        }
        else
        {
            break;
        }
    }
    if (len==0)
    {
        decstr.append("0");
    }
}

int BigdecimalIng::compare(const BigdecimalIng& c1)
{
    string num1=decstr;
    string num2=c1.decstr;

    bool isnum1positive=true;
    bool isnum2positive=true;

    if ((num1[0]=='-'))
    {
        isnum1positive=false;
    }
    if ((num2[0]=='-'))
    {
        isnum2positive=false;
    }

    if ((isnum1positive==true) && (isnum2positive==false))
    {
        return 1;
    }
    if ((isnum1positive==false) && (isnum2positive==true))
    {
        return -1;
    }

    BigdecimalIng op1=*this;
    op1.removeleadingzeros();
    BigdecimalIng op2=c1;
    op2.removeleadingzeros();

    int num1len=op1.decstr.length();
    int num2len=op2.decstr.length();

    num1=op1.decstr;
    num2=op2.decstr;

    int num1start=0;
    int num2start=0;

    if ((num1[0]=='+') || (num1[0]=='-'))
    {
        num1start=1;
    }
    if ((num2[0]=='+') || (num2[0]=='-'))
    {
        num2start=1;
    }


    if ((num1len-num1start)>(num2len-num2start))
        return 1;
    else if ((num1len-num1start)<(num2len-num2start))
        return -1;
    else if ((num1len-num1start)==(num2len-num2start))
    {
        for(int i=num1start,j=num2start;i<num1len&&j<num2len;i++,j++)
        {
            if (num1[i]==num2[j])
                continue;
            else if (num1[i]>num2[j])
                return 1;
            else if (num1[i]<num2[j])
                return -1;
        }
        return 0;
    }
}
int BigdecimalIng:: borrow(string &c1, int pos)
{
    int prev = c1[pos-1]-'0';
    if (prev > 0)
    {
        prev--;
        c1[pos-1]=prev+'0';
        return 1;
    }
    else if (prev==0)
    {
        int carry=borrow(c1,pos-1);
        c1[pos-1]='9';
        return 1;
    }
}
bool BigdecimalIng::isaddition(const string& num1, const string& num2)
{
    if(
            ((num1[0]=='+') && (num2[0]=='+')) ||
            ((num1[0]=='-') && (num2[0]=='-')) ||
            ((num1[0]=='+') && (num2[0]!='-')) ||
            ((num1[0]!='-') && (num2[0]=='+')) ||
            ((num1[0]!='-') && (num2[0]!='-'))
            )
        return true;
    else
        return false;

}
bool BigdecimalIng::issubtraction(const string& num1, const string& num2)
{

    if(
            ((num1[0]=='+') && (num2[0]=='+')) ||
            ((num1[0]=='-') && (num2[0]=='-')) ||
            ((num1[0]!='-') && (num2[0]=='+')) ||
            ((num1[0]=='+') && (num2[0]!='-')) ||
            ((num1[0]!='-') && (num2[0]!='-'))
            )
        return true;
    else
        return false;
}
string BigdecimalIng::getdecstr()
{
    return decstr;
}
BigdecimalIng::BigdecimalIng() {}
BigdecimalIng::BigdecimalIng(string n){
    decstr = n;
}
BigdecimalIng::BigdecimalIng(const BigdecimalIng& c1)
{
    decstr=c1.decstr;
}
BigdecimalIng::BigdecimalIng( BigdecimalIng& c1)
{
    decint=c1.decint;
    decstr=c1.decstr;

}
BigdecimalIng BigdecimalIng:: abs()const
{
    string operand = decstr;
    if ((operand[0]=='+')||(operand[0]=='-'))
    {
        operand.erase(0,1);
    }
    return BigdecimalIng(operand);
}
BigdecimalIng::BigdecimalIng(long long int i)
{
    decint = i;
    stringstream ss;
    string r;
    ss<<i;
    ss>>r;
    decstr=r;
}
BigdecimalIng BigdecimalIng:: operator-()const
{
    string result;
    if (decstr[0]=='-')
    {
        result.append(decstr,1,string::npos);

    }
    else if (decstr[0]=='+')
    {
        result.append(string("-"));
        result.append(decstr,1,string::npos);
    }
    else
    {
        result.append(string("-"));
        result.append(decstr);
    }
    return BigdecimalIng(result);
}
BigdecimalIng BigdecimalIng:: operator+ (const BigdecimalIng &c1)
{
    string num1=decstr;
    string num2=c1.decstr;

    bool toadd=isaddition(num1, num2);

    if (!toadd)
    {
        return this->operator-(-c1);
    }

    int num1len=decstr.length();
    int num2len=c1.decstr.length();
    num1len--; num2len--;

    bool done=false;

    string result;
    int pos=0;

    int carry=0;

    int num1start=0;
    int num2start=0;

    if ((num1[0]=='+') || (num1[0]=='-'))
    {
        num1start=1;
    }

    if ((num2[0]=='+') || (num2[0]=='-'))
    {
        num2start=1;
    }

    while (((num1len>=num1start) || (num2len>=num2start)))
    {
        if ((num1len>=num1start) && (num2len>=num2start))
        {
            int op1 = num1[num1len]-'0';
            int op2 = num2[num2len]-'0';

            int res = op1+op2+carry;
            int sum;

            if (res>=10)
            {
                sum = res-10;
                carry = 1;
            }
            else
            {
                sum=res;
                carry=0;
            }

            result.push_back(sum+'0');

            num1len--;
            num2len--;
        }
        else if ((num1len>=num1start) && (num2len<num2start))
        {
            int op1 = num1[num1len]-'0';

            int res = op1+carry;
            int sum;

            if (res>=10)
            {
                sum = res-10;
                carry = 1;
            }
            else
            {
                sum=res;
                carry=0;
            }



            result.push_back(sum+'0');

            num1len--;
        }
        else if ((num1len<num1start) && (num2len>=num2start))
        {
            int op2 = num2[num2len]-'0';

            int res = op2+carry;
            int sum;

            if (res>=10)
            {
                sum = res-10;
                carry = 1;
            }
            else
            {
                sum=res;
                carry=0;
            }



            result.push_back(sum+'0');

            num2len--;
        }
    }
    if (carry==1)
    {
        result.push_back(carry+'0');
    }


    if ((num1[0]=='-'))
    {
        result.push_back('-');
    }

    reverse(result.begin(),result.end());

    BigdecimalIng res(result);
    res.removeleadingzeros();
    return res;

}
BigdecimalIng BigdecimalIng:: operator-(const BigdecimalIng& c1)
{
    string num1=decstr;
    string num2=c1.decstr;

    bool tosub=issubtraction(num1, num2);

    if (!tosub)
    {
        return this->operator+(-c1);
    }


    int num1len=decstr.length();
    int num2len=c1.decstr.length();

    string result;
    bool isnegative=false;



    BigdecimalIng absop1=this->abs();
    BigdecimalIng absop2=c1.abs();

    int comparison=absop1.compare(absop2);
    if (comparison<0)
    {

        {
            isnegative=true;
        }
        num1=c1.decstr;
        num2=decstr;
        int temp;
        temp=num1len;
        num1len=num2len;
        num2len=temp;
    }
    else if (comparison >0)
    {
        if (num1[0]=='-')
        {
            isnegative=true;
        }
    }


    num1len--;num2len--;

    int num1start=0;
    int num2start=0;

    if ((num1[0]=='+') || (num1[0]=='-'))
    {
        num1start=1;
    }

    if ((num2[0]=='+') || (num2[0]=='-'))
    {
        num2start=1;
    }


    for (int i=num2len,j=num1len;i>=num2start;i--,j--)
    {
        int op1=num1[j]-'0';
        int op2=num2[i]-'0';

        int diff;

        if (op1>=op2)
        {
            diff=op1-op2;
        }
        else
        {
            int br = borrow(num1, j);
            diff = ((br*10)+op1)-op2;
        }

        result.push_back(diff+'0');
    }
    for(int i=(num1len-(num2len-num2start))-1;i>=num1start;i--)
    {
        result.push_back(num1[i]);
    }
    if (isnegative)
        result.push_back('-');

    reverse(result.begin(),result.end());

    BigdecimalIng res(result);
    res.removeleadingzeros();
    return res;

}
ostream& operator<<(ostream &out, BigdecimalIng &obj)
{
    out << obj.decstr;
    return out;
}
void BigdecimalIng:: getBigDec()
{
    cout << "Enter BigDec \n";
    cin >> decstr;
}
bool BigdecimalIng:: operator > (BigdecimalIng anotherBigInger)
{
    int l = decstr.size();
    if(decstr[0] == '-')
    {
        l--;
    }
    if(l == anotherBigInger.mx_size()) {
        if(decstr[0] == '-' && anotherBigInger.decstr[0] != '-')
        {
            cout << "false \n";
        }
        else if (decstr[0] != '-' && anotherBigInger.decstr[0] != '-' ) {
            int compare = decstr.compare(anotherBigInger.decstr);
            if (compare == 1)
                cout << "true " << endl;
            else
                cout << "false " << endl;
        }
        else if (decstr[0] == '-' && anotherBigInger.decstr[0] == '-')
        {
            decstr.erase(decstr.begin());
            anotherBigInger.decstr.erase(anotherBigInger.decstr.begin());
            int compare = decstr.compare(anotherBigInger.decstr);
            if (compare == 1)
                cout << "false " << endl;
            else
                cout << "true " << endl;
        }
        else if (decstr[0] != '-' && anotherBigInger.decstr[0] == '-')
        {
            cout << "true \n";
        }
    }
    else if (l > anotherBigInger.mx_size())
    {
        if(decstr[0] == '-' && anotherBigInger.decstr[0] != '-')
            cout << "false\n";
        else if(decstr[0] != '-' && anotherBigInger.decstr[0] == '-')
            cout << "true \n";
        else if(decstr[0] == '-' && anotherBigInger.decstr[0] == '-')
            cout << "false\n";
        else if(decstr[0] != '-' && anotherBigInger.decstr[0] != '-')
            cout << "true \n";
    }
    else
    {
        if(decstr[0] != '-' && anotherBigInger.decstr[0] != '-')
            cout << "false \n";
        else if(decstr[0] == '-' && anotherBigInger.decstr[0] == '-')
            cout << "true \n";
        else if (decstr[0] == '-' && anotherBigInger.decstr[0] != '-')
            cout << "false\n";
        else if(decstr[0] != '-' && anotherBigInger.decstr[0] == '-')
            cout << "true \n";
    }
}
bool BigdecimalIng:: operator == (BigdecimalIng anotherDec){
    int compare = decstr.compare(anotherDec.decstr);
    if (compare == 0)
        cout << "true " << endl;
    else
        cout << "false " << endl;
}
void BigdecimalIng:: operator= (BigdecimalIng anotherDec)
{
    decstr = anotherDec.decstr;
}
bool BigdecimalIng:: ant_sign()
{
    if(decstr[0] == '-')
        return false;
    else
        return true;
}
int BigdecimalIng::mx_size()
{
    int x;
    if(!isdigit(decstr[0]) && isdigit(decstr[1]))
        x = (decstr.size()) - 1;
    else
        x = decstr.size();
}
int BigdecimalIng::size()
{
    if(!isdigit(decstr[0]) && isdigit(decstr[1]))
        cout << (decstr.size()) - 1 << endl;
    else
        cout << decstr.size() << endl;
}
int BigdecimalIng::sign()
{
    if(!isdigit(decstr[0]) && isdigit(decstr[1]))
    {
        if(decstr[0] == '-')
            cout <<"Negative "<< endl;
    }
    else
        cout << "Positive\n";
}
bool BigdecimalIng:: operator < (BigdecimalIng b)
{
    int c = decstr.compare(b.decstr);
    if(c==-1){
        return true;
    }
    else
        return false;
}

