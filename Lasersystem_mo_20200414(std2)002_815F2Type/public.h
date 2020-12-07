#ifndef __PUBLIC_H
#define __PUBLIC_H

#include <vector>

#define AXISNUM		12
#define APTNUM      18
#define NOLINK      -1
#define M_PI		3.1415926535897

#if 0
#ifdef CRD_DOUBLE
	typedef double CRD;
	#define URECT URect
#else
	typedef long CRD;
	#define URECT CRect
#endif
#else
	typedef long CRD;
	#define URECT CRect
#endif

struct Coord
{
	CRD x;
	CRD y;

	Coord():x(0),y(0){}
	Coord(CRD cx, CRD cy) : x(cx), y(cy){}
	
	bool operator==(const Coord& rht) const
	{
		return x==rht.x && y==rht.y;
	}

	bool operator!=(const Coord& rht) const
	{
		return x!=rht.x || y!=rht.y;
	}
	
	Coord& operator=(const Coord& rht)
	{
		this->x = rht.x;
		this->y = rht.y;
		return *this;
	}

	Coord& operator+=(const Coord& rht)
	{
		x += rht.x, y += rht.y;
		return *this;
	}

	Coord& operator-=(const Coord& rht)
	{
		x -= rht.x,	y -= rht.y;
		return *this;
	}

	Coord operator+(const Coord& rht) const
	{
		return Coord(this->x+rht.x,this->y+rht.y);
	}

	Coord operator-(const Coord& rht) const
	{
		return Coord(this->x-rht.x,this->y-rht.y);
	}

	Coord& operator/=(int iScale)
	{
		if(iScale==0)
			return Coord(0,0);
		this->x = (CRD)( this->x/iScale ); 
		this->y = (CRD)( this->y/iScale );
		return *this;
	}

	Coord operator/(int iScale) const
	{
		if(iScale==0)
			return Coord(0,0);

		return Coord(this->x/iScale,this->y/iScale);
	}

	friend int operator<(const Coord& left, const Coord& right)
	{
		if(left.x != right.x)
			return left.x < right.x;
		else
			return left.y < right.y;
	}

	int operator<(const Coord& right) 
	{
		if(this->x != right.x)
			return this->x < right.x;
		else
			return this->y < right.y;
	}

	friend int operator>(const Coord& left,const Coord& right) 
	{
		if(left.x != right.x)
			return left.x > right.x;
		else
			return left.y > right.y;
	}

	friend int operator<=(const Coord& left,const Coord& right) 
	{
		if(left.x != right.x)
			return left.x <= right.x;
		else
			return left.y <= right.y;
	}

	friend int operator>=(const Coord& left,const Coord& right) 
	{
		if(left.x >= right.x)
			return left.x >= right.x;
		else
			return left.y >= right.y;
	}	
};

typedef std::vector<Coord> HoleCoordV;

struct Coord3D:public Coord
{
	Coord3D(CRD cx=0, CRD cy=0, CRD cz=0):Coord(cx,cy),z(cz){};
	CRD z;

	Coord3D& operator=(const Coord3D& rht)
	{
		this->x = rht.x;
		this->y = rht.y;
		this->z = rht.z;
		return *this;
	}

	bool operator!=(const Coord3D& rht) const
	{
		return x!=rht.x || y!=rht.y||z!=rht.z;
	}
};

struct HoleData:public Coord
{
	int iToolNo;

	HoleData(CRD cx=0,CRD cy=0,int nToolNo=0 ):Coord(cx,cy),iToolNo(nToolNo){};
	HoleData(const Coord& crd):Coord(crd),iToolNo(0){};

    HoleData& operator=(const HoleData& rht)
	{
		if(this==&rht)
			return *this;

		this->x = rht.x;
		this->y = rht.y;
		this->iToolNo = rht.iToolNo;
		return *this;
	}

	HoleData operator-(const HoleData& rht) const
	{
		return HoleData(this->x-rht.x,this->y-rht.y,this->iToolNo);
	}
}; 

typedef std::vector<HoleData> HolePositionV; 

struct AreaHoleData:public HoleData
{
	bool bSubarea;

	AreaHoleData(CRD cx=0,CRD cy=0,int nToolNo=0,bool bSA=false):HoleData(cx,cy,nToolNo),bSubarea(bSA){};
	AreaHoleData(const Coord& crd):HoleData(crd),bSubarea(false){};

    AreaHoleData& operator=(const AreaHoleData& aht)
	{
		if(this==&aht)
			return *this;

		this->x = aht.x;
		this->y = aht.y;
		this->iToolNo = aht.iToolNo;
		this->bSubarea = aht.bSubarea;
		return *this;
	}
}; 

typedef std::vector<AreaHoleData> AreaHoleV; 

struct TransformParam								//重构加工流程：20161123
{
	double ScalingX;
	double ScalingY;
	double Rotation;
	double TranslationX;
	double TranslationY;
};

#endif
