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

void int_arrinsert(rat A[][1],int n)
{
	for (int i=0;i<n;i++)
		A[i][1].int_insert();
}

void duplicate(rat A[][10],rat B[][10])
{
	for (int i=0;i<10;i++)
		for (int j=0;j<10;j++)
			B[i][j]=A[i][j];
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

double deci(rat t){return (double)t.u/(double)t.o;}



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

int matrix_rank(rat A[][10],int n,int m)//soon in robotics
{
	int rank_no=0;
	convert_row_echelon(A,n,m);
	for (int i=0;i<n;i++) {
		for (int j=0;j<m;j++)
			if (A[i][j].u!=0) {
				rank_no++;
				break;
			}
	}
	return rank_no;			
}

void augment(rat A[][10],rat B[10][1],int n,int m)//n is max column of A
{
	for (int i=0;i<n;i++)
		A[i][m]=B[i][1];
}

rat solve(rat A[],int row_boundary,int coeff_unknwn)
{
	rat sol;
	for (int i=0;i<row_boundary-1;i++) {
		if (i==coeff_unknwn)continue;
		sol-=A[i];
	}
	sol+=A[row_boundary-1];
	return sol/A[coeff_unknwn];
}

bool check_homo(rat B[][1],int n)//soon in robotics
{
	for (int i=0;i<n;i++)
		if (B[i][1].u!=0)return false;
	return true;
}

bool check_dependency(rat A[][10],int n,int m)//soon in robotics
{
	//the function does not work
	bool conds=true;
	for (int j=0;j<n;j++) {
	rat check1=A[0][j]/A[0][j+1];
	for (int i=1;i<n;i++) {
	    if (check1!=A[i][j]/A[i][j+1]) {
			conds=false;
			break;
		}
		check1=A[i][j]/A[i][j+1];
	}
	if (conds==true)//the matrix is all dependent of two consecutive vectors are dependent
		return true;
	}
}

bool check_validity(rat A[][10],rat B[][1],int n,int m)//soon in robotics
{
	//the function does not work
	if (check_dependency(A,n,m))return false;
	rat D[10][10];
	duplicate(A,D);
	augment(A,B,n,m);
	int rank1=matrix_rank(A,n,m);
	int rank2=matrix_rank(D,n,m);
	if (check_homo(B,n))
	{
		if (rank1==rank2 && rank1<m+1)
			return false;
		else if (rank1==rank2 && rank1==m+1)
			return true;//indeed has a unique solution
	}
	else
	{
		if (rank1!=rank2)
			return false;
		else
			return true;
	}
}

void system_solve(rat S[],rat A[][10],int n,int m)
{
	for (int i=n-1;i>=0;i--) {
		for (int j=m-1;j>i;j--)
			A[i][j]*=S[j];
		S[i]=solve(A[i],m+1,i);
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
	rat A[10][10];rat B[10][1];
	int n,m;
	cout << "Insert the number of equations and the number of variables respectively.\n";
	cin >> n >> m;//putting the dimensions
	cout << "Insert the coefficients of every equation in the system.\n";
	int_arrinsert(A,n,m);
	cout << "Insert the constant values of the equations according to the first value in the system.\n";
	int_arrinsert(B,n);
	augment(A,B,n,m);
	convert_row_echelon(A,n,m);
	rat S[10];
	system_solve(S,A,n,m);
	cout << "The solution of the system is:-\n";
	for (int i=0;i<m;i++) {
	cout << "S[" << i+1 << "]= ";
	S[i].display();
	cout << endl;
	}
	system("pause");
	return 0;
}