// task_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mydll.h"

#include <windows.h>
#include <math.h>

#define isEmpty 1
#define makeEmpty 2
#define setCommonSegment 3
#define setSegment 4

//function pointers
typedef void(*TF1)(Segment&);
typedef void(*TF2)(Segment&);
typedef int(*TF3)(Segment&,Segment&,Segment&);
typedef void(*TF4)(Segment&,double,double);

int f1(double &p,double &q) //find roots of equation;
{
	double temp;
	double x1,x2;
	double D=p*p-4*q;
	
	if(D<0) return 0;
	
	x1=(-p+sqrt(D))/(double)2;
	x2=(-p-sqrt(D))/(double)2;
	p=x1;
	q=x2;

	cout<<"ROOTS-> "<<p<<"; "<<q<<endl;
	
	if(p>q)
	{
		temp=p;
		p=q;
		q=temp;
	}
	
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	TF1 pisEmpty;
	TF2 pmakeEmpty;
	TF3 psetCommonSegment;
	TF4 psetSegment;

	HINSTANCE h1;
	Segment s1,s2,s3;
	double n,p1,p2;
	double p,q;

	h1=LoadLibrary(TEXT("mydll"));
	
	if(h1)
	{
		cout<<"Library loaded"<<endl;

		pmakeEmpty=(TF2)GetProcAddress(h1,(LPCSTR)MAKEINTRESOURCE(makeEmpty));
		psetCommonSegment=(TF3)GetProcAddress(h1,(LPCSTR)MAKEINTRESOURCE(setCommonSegment));
		psetSegment=(TF4)GetProcAddress(h1,(LPCSTR)MAKEINTRESOURCE(setSegment));
		
		if(pmakeEmpty) 
			cout<<"Function loaded"<<endl;
		else cout<<"Function wasn't loaded"<<endl;

	}else
		cout<<"Library wasn't loaded"<<endl;

	cout<<"Enter number of equation->";
	cin>>n;

	for(int i=0;i<n;i++)
	{
		cout<<"Enter p->"<<endl;
		cin>>p;
		cout<<"Enter q->"<<endl;
		cin>>q;
		getchar();

		if(!f1(p,q)){
			cout<<"Equation hasn't rational roots"<<endl;
			getchar();
			return 0;
		}

		if(i==0)
			psetSegment(s1,p,q);
		else{
			psetSegment(s2,p,q);
			
		if(!psetCommonSegment(s1,s2,s1)) i=n;//no common segment;
			
		}	 
	}

	cout<<"Roots: "<<endl;
	cout<<"x1="<<s1.a<<endl;
	cout<<"x2="<<s1.b<<endl;
	cout<<"empty="<<s1.empty<<endl;

	FreeLibrary(h1);
	
	getchar();
	return 0;
}

