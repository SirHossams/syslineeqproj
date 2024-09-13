#include <iostream>

using namespace std;

struct rat
{
        int u,o;
        rat(){u=0;o=1;}
        rat(rat &r){u=r.u;o=r.o;}
        void insert(){cin >> u >> o;}
        void int_insert()
        {
                cin >> u;
                o=1;
        }
        void display(){
                if (u%o==0)
                cout << u/o;
                else
                cout << u << "/" << o;
        }
        void optimise()
        {
                int q=0,r=0;
                int r1=u,r2=o;
                do {
                        q=r1/r2;
                        r=r1%r2;
                        r1=r2;
                        r2=r;
                }while(r!=0);
                u/=r1;o/=r1;
        }
        rat frac(double d)
        {
        rat s;
        int c=0;double rem;
        do {
                rem=d-(int)d;
                d*=10;
                c++;
        }while(rem!=0);
        s.u=d;s.o=pow(10.0,c);
        s.optimise();
        return s;
        }
        rat operator+(rat a)
        {
                rat s;
                s.u=a.u*o+a.o*u;
                s.o=a.o*o;
                s.optimise();
                return s;
        }
        rat operator+(double d)
        {
                rat t=frac(d);
                rat result;
                result=*this+t;
                result.optimise();
                return result;
        }
        rat operator+=(rat a)
        {
                *this=*this+a;
                return *this;
        }
        rat operator+=(double d)
        {
                *this=*this+d;
                return *this;
        }
        rat operator-(rat a)
        {
                rat s;
                s.u=-a.u*o+a.o*u;
                s.o=a.o*o;
                s.optimise();
                return s;
        }
        rat operator-(double d)
        {
                rat t=frac(d);
                rat result;
                result=*this-t;
                result.optimise();
                return result;
        }
        rat operator-=(rat a)
        {
                *this=*this-a;
                return *this;
        }
        rat operator-=(double d)
        {
                *this=*this-d;
                return *this;
        }
        rat operator*(rat a)
        {
                rat result;
                result.u=a.u*u;
                result.o=a.o*o;
                result.optimise();
                return result;
        }
        rat operator*(double d)
        {
                rat t=frac(d);
                rat result;
                result=*this*t;
                result.optimise();
                return result;
        }
        rat operator*=(rat a)
        {
                *this=*this*a;
                return *this;
        }
        rat operator*=(double d)
        {
                *this=*this*d;
                return *this;
        }
        rat operator/(rat a)
        {
                rat result;
                result.u=a.o*u;
                result.o=a.u*o;
                result.optimise();
                return result;
        }
        rat operator/(double d)
        {
                rat t=frac(d);
                rat result;
                result=*this/t;
                result.optimise();
                return result;
        }
        rat operator/=(rat a)
        {
                *this=*this/a;
                return *this;
        }
        rat operator/=(double d)
        {
                *this=*this/d;
                return *this;
        }
        bool operator==(rat a)
        {
                this->optimise();
                a.optimise();
                return (a.u==u && a.o==o);
        }
        bool operator!=(rat a)
        {
                return !(a==*this);
        }
};

void int_arrinsert(rat A[][10],int n,int m)
{
        for (int i=0;i<n;i++)
                for (int j=0;j<m;j++)
                A[i][j].int_insert();
}

namespace elementary_row_oper {
void row_reduce(rat A[][10],int row,int col,rat dividend_no)
{
        for (int i=col-1;i<10;i++)
                A[row-1][i]/=dividend_no;
}
void zero_adding(rat A[][10],int row_addend_no,int row_augend_no,int start_col)
{
        row_augend_no--;row_addend_no--;start_col--;
        rat first_val=A[row_addend_no][start_col];
        for (int i=start_col;i<10;i++) {
                A[row_addend_no][i]+=first_val*A[row_augend_no][i]*-1;
        }
}
void row_exchange(rat A[][10],int row1,int row2)//useful in robotics
{
        row1--;row2--;
        //how to swap two numbers by a temp variable
        rat swap_tar;
        for (int i=0;i<10;i++) {
                swap_tar=A[row1][i];
                A[row1][i]=A[row2][i];
                A[row2][i]=swap_tar;
        }
}
};



void convert_row_echelon(rat A[][10],int ni,int nj)
{
        using namespace elementary_row_oper;
        if (ni>nj) {
                cout << "Infinite number of solutions!!" << endl;
                return;
        }

        for (int i=0;i<ni;i++) {
                int ii=i+1;
                row_reduce(A,ii,ii,A[i][i]);
                for (int j=i+1;j<nj;j++) {
                        int jj=j+1;
                        zero_adding(A,jj,ii,ii);
                }
        }
}
void display(rat A[][10],int n,int m)
{
        for (int i=0;i<n;i++) {
                for (int j=0;j<m;j++) {
                A[i][j].display();
                cout << " ";
                }
        cout << endl;
        }
}

int main()
{
   using namespace elementary_row_oper;
   rat A[10][10];
   int n,m;
   cin >> n >> m;
   int_arrinsert(A,n,m);
   convert_row_echelon(A,n,m);
   display(A,n,m);
   return 0;
}