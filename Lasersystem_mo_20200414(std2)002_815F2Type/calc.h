// calc.h: interface for the calc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALC_H__05F42673_FDB7_468B_9035_1D8BE8996456__INCLUDED_)
#define AFX_CALC_H__05F42673_FDB7_468B_9035_1D8BE8996456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "public.h"

class calc  
{	
public:	
//中心点
	static Coord center(const Coord& c1, const Coord& c2);
//距离
	static double distance(const Coord& c1, const Coord& c2);
//计算角度
	static angle_t angle(const Coord& crdStd1,const Coord& crdStd2,const Coord& crdRef1, const Coord& crdRef2);
    static angle_t angle(const Coord &crdStd1, const Coord &crdStd2, const Coord &crdRef1, const Coord &crdRef2,double dbScaleX,double dbScaleY);
	static angle_t angle(const Coord& crd1, const Coord& crd2);
//移动坐标
	static Coord ToMove(const Coord& cenCrd, long lMx,long lMy);
//比例缩放
	static Coord ToScale(const Coord& cenCrd, double dbSx, double dbSy,const Coord& refCrd);
//旋转坐标
	static Coord ToRotate(const Coord& center, angle_t angle, const Coord& crd);
};

#endif // !defined(AFX_CALC_H__05F42673_FDB7_468B_9035_1D8BE8996456__INCLUDED_)
