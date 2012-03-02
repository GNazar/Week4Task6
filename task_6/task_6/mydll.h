#include <iostream>
using namespace std;
struct Segment
{
	double a,b;
	bool empty;
};
__declspec(dllexport) void makeEmpty(Segment&);
__declspec(dllexport) bool isEmpty(Segment&);
__declspec(dllexport) void setSegment(Segment &p,double a,double b);
__declspec(dllexport) void setSegment(Segment& p,const Segment&,const Segment&);
