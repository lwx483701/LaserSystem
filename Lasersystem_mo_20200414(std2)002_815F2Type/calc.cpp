// calc.cpp: implementation of the calc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lasersystem.h"
#include "calc.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Coord calc::center(const Coord& c1, const Coord& c2)
{
	return Coord((c1.x+c2.x)/2, (c1.y+c2.y)/2);
}

double calc::distance(const Coord& c1, const Coord& c2)
{
	return double(sqrt(pow(c2.x-c1.x,2)+pow(c2.y-c1.y,2)));
}

angle_t calc::angle(const Coord &crdStd1, const Coord &crdStd2, const Coord &crdRef1, const Coord &crdRef2)
{
	return atan2(crdRef2.y-crdRef1.y, crdRef2.x-crdRef1.x)
		  -atan2(crdStd2.y-crdStd1.y, crdStd2.x-crdStd1.x);
}

angle_t calc::angle(const Coord&crd1,const Coord& crd2)
{
	return atan2( crd2.y-crd1.y, crd2.x - crd1.x);
}

angle_t calc::angle(const Coord &crdStd1, const Coord &crdStd2, const Coord &crdRef1, const Coord &crdRef2,double dbScaleX,double dbScaleY)
{
	return atan2((crdRef2.y-crdRef1.y)*dbScaleY,(crdRef2.x-crdRef1.x)*dbScaleX)
		  -atan2(crdStd2.y-crdStd1.y, crdStd2.x-crdStd1.x);
}

Coord calc::ToMove(const Coord &cenCrd, long lMx, long lMy)
{
  return Coord( cenCrd.x+lMx, cenCrd.y+lMy);	
}

Coord calc::ToScale(const Coord &cenCrd, double dbSx, double dbSy, const Coord &refCrd)
{
  return Coord( (long)((refCrd.x-cenCrd.x)*dbSx + cenCrd.x),
	            (long)((refCrd.y-cenCrd.y)*dbSy + cenCrd.y));
}

//counterclockwise +
Coord calc::ToRotate(const Coord& cenCrd, angle_t angle, const Coord& crd)
{
    return Coord( (long)(cenCrd.x + (crd.x - cenCrd.x) * cos(angle) - (crd.y - cenCrd.y) * sin(angle)),
				  (long)(cenCrd.y + (crd.x - cenCrd.x) * sin(angle) + (crd.y - cenCrd.y) * cos(angle)) );
}

