
#include "stdafx.h"
#include "mydll.h"
int sort( double& a, double& b )
{
	double temp;
	if(a>b)
	{
		temp=a;
		a=b;
		b=temp;
		return 1;
	}
	return 0;
}

void bothEmpty(Segment& p,const Segment& p1,const Segment& p2)
{
	double t1, t2;

	t1=p1.a;
	t2=p2.a;
	sort(t1,t2);
	p.a=t1;
	
	t1=p1.b;
	t2=p2.b;
	sort(t1,t2);
	p.b=t2;
	p.empty=true;

}

int oneEmpty(Segment& p,const Segment& p1,const Segment& p2)
{
	Segment ts1, ts2;//ts1-empty segment

	if ( p1.empty )
	{
		ts1=p1;
		ts2=p2;
	}
	else
	{
		ts1=p2;
		ts2=p1;
	}
	if( ts1.a>ts2.a )	//segment from -infinity to ts1.a;
	{
		
		if( ts2.b<ts1.a )
			setSegment( p,ts2.a,ts2.b );
		else
			setSegment( p,ts2.a,ts1.a );

		return 1;
	}

	if( ts1.b<ts2.b )	//segment from ts1.b to infinity;
	{
		
		cout<<"if( ts1.b<ts2.b )222"<<endl;
		if( ts1.b<ts2.a)
			setSegment( p,ts2.a,ts2.b );
		else
			setSegment( p,ts1.b,ts2.b );

		return 1;
	} 
	//cout<<"No common segment!"<<endl;
	return 0;
	
}

int noEmpty(Segment& p,const Segment& p1,const Segment& p2)
{
	double a,b;
	double temp1,temp2;
	
	a=p1.a;
	b=p2.a;
	sort(a,b);
	temp1=b;	//bedinning of segment;

	a=p1.b;
	b=p2.b;
	sort(a,b);
	temp2=a;	//end of segment;

	if(temp1>temp2) return 0;	//no common segment;
	
	setSegment(p,temp1,temp2);
	return 1;
}

extern "C++" __declspec(dllexport) void makeEmpty(Segment& p)
{
	double temp;
	if(!p.empty)
	{
		temp=p.a;
		p.a=p.b;
		p.b=temp;
		p.empty=true;
	}
}

extern "C++" __declspec(dllexport) bool isEmpty(Segment& p)
{
	return p.empty;
}

extern "C++"  __declspec(dllexport) void setSegment(Segment &p,double a,double b)
{
	if(a>b)	
	{
		p.a=b;
		p.b=a;
		p.empty=true;
		return;
	}
	p.a=a;
	p.b=b;
	p.empty=false;
}

extern "C++" __declspec(dllexport) int setCommonSegment(Segment& p,const Segment& p1,const Segment& p2)
{
	
	if( p1.empty && p2.empty )
	{
		bothEmpty(p,p1,p2);
		return 1;
	}

	if ( p1.empty||p2.empty )
	{
		return oneEmpty(p,p1,p2);
	}
	
	return noEmpty(p,p1,p2);
	
}