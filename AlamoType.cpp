#include "Alamo.h"
#include "AlamoType.h"
//////////////////////////////////////////////////////////////////////////
//Finished!


namespace Alamo
{

	//
	//alaVector2D implement
	//
	alaVector2D::alaVector2D()
	{
		x = y = 0;
	}

	alaVector2D::alaVector2D(int _x, int _y)
	{
		x = _x; y = _y;
	}

	
	void alaVector2D::X(int _x)
	{
		x = _x;
	}
	int alaVector2D::X()
	{
		return (x);
	}

	void alaVector2D::Y(int _y)
	{
		y = _y;
	}
	int alaVector2D::Y()
	{
		return (y);
	}

	alaVector2D 
		alaVector2D::operator+(const alaVector2D & rhOp)const
	{
		return alaVector2D(x + rhOp.x, y + rhOp.y);
	}

	alaVector2D
		alaVector2D::operator-(const alaVector2D & rhOp)const
	{
		return alaVector2D(x - rhOp.x, y - rhOp.y);
	}
 
	alaVector2D
		alaVector2D::operator*(int rhOp)const
	{
		return alaVector2D(x*rhOp, y*rhOp);
	}

	alaVector2D
		operator*(int lhOp,const alaVector2D & rhOp)
	{
		return alaVector2D(rhOp.x*lhOp, rhOp.y*lhOp);
	}

	alaVector2D alaVector2D::operator/(int rhOp)const
	{
		return alaVector2D(x / rhOp, y / rhOp);
	}

	alaVector2D &
		alaVector2D::operator+=(const alaVector2D & rhOp)
	{
		x += rhOp.x;
		y += rhOp.y;
		return (*this);
	}

	alaVector2D &
		alaVector2D::operator-=(const alaVector2D & rhOp)
	{
		x -= rhOp.x;
		y -= rhOp.y;
		return (*this);
	}

	alaVector2D &
		alaVector2D::operator*=(int rhOp)
	{
		x *= rhOp;
		y *= rhOp;
		return (*this);
	}

	alaVector2D &
		alaVector2D::operator/=(int rhOp)
	{
		x /= rhOp;
		y /= rhOp;
		return (*this);
	}

	int
		alaVector2D::Dot(const alaVector2D & rhOp)const
	{
		return (x*rhOp.x, y*rhOp.y);
	}

	int alaVector2D::Magnitude()const
	{
		return ((int)sqrt(x*x + y*y));
	}

	alaVector2D
		alaVector2D::Normalize()const
	{
		int lenth = Magnitude();
		alaVector2D temp;
		if (lenth != 0) {
			temp.x = x / lenth;
			temp.y = y / lenth;
		}
		return temp;
	}


	//
	// ------------ alaVectorf2D implement
	//


	alaVectorf2D::alaVectorf2D()
	{
		x = y = 0;
	}

	alaVectorf2D::alaVectorf2D(float _x, float _y)
	{
		x = _x; y = _y;
	}

	void alaVectorf2D::X(float _x)
	{
		x = _x;
	}
	float alaVectorf2D::X()
	{
		return (x);
	}

	void alaVectorf2D::Y(float _y)
	{
		y = _y;
	}
	float alaVectorf2D::Y()
	{
		return (y);
	}

	alaVectorf2D
		alaVectorf2D::operator+(const alaVectorf2D & rhOp)const
	{
		return alaVectorf2D(x + rhOp.x, y + rhOp.y);
	}

	alaVectorf2D
		alaVectorf2D::operator-(const alaVectorf2D & rhOp)const
	{
		return alaVectorf2D(x - rhOp.x, y - rhOp.y);
	}

	alaVectorf2D
		alaVectorf2D::operator*(float rhOp)const
	{
		return alaVectorf2D(x*rhOp, y*rhOp);
	}

	alaVectorf2D
		operator*(float lhOp, const alaVectorf2D & rhOp)
	{
		return alaVectorf2D(rhOp.x*lhOp, rhOp.y*lhOp);
	}

	alaVectorf2D 
		alaVectorf2D::operator/(float rhOp)const
	{
		return alaVectorf2D(x / rhOp, y / rhOp);
	}

	alaVectorf2D &
		alaVectorf2D::operator+=(const alaVectorf2D & rhOp)
	{
		x += rhOp.x;
		y += rhOp.y;
		return (*this);
	}

	alaVectorf2D &
		alaVectorf2D::operator-=(const alaVectorf2D & rhOp)
	{
		x -= rhOp.x;
		y -= rhOp.y;
		return (*this);
	}

	alaVectorf2D &
		alaVectorf2D::operator*=(float rhOp)
	{
		x *= rhOp;
		y *= rhOp;
		return (*this);
	}

	alaVectorf2D &
		alaVectorf2D::operator/=(float rhOp)
	{
		x /= rhOp;
		y /= rhOp;
		return (*this);
	}

	float
		alaVectorf2D::Dot(const alaVectorf2D & rhOp)const
	{
		return (x*rhOp.x, y*rhOp.y);
	}

	float alaVectorf2D::Magnitude()const
	{
		return ((float)sqrt(x*x + y*y));
	}

	alaVectorf2D
		alaVectorf2D::Normalize()const
	{
		float lenth = Magnitude();
		alaVectorf2D temp;
		if (lenth != 0) {
			temp.x = x / lenth;
			temp.y = y / lenth;
		}
		return temp;
	}
}
