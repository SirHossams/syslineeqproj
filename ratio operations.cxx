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


int main()
{
	rat x,y;
	x.int_insert();
	y.int_insert();
	rat z=x+y;
	z.display();
	return 0;
}