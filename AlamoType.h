
#ifndef _ALAMO_TYPE_H_
#define _ALAMO_TYPE_H_
//////////////////////////////////////////////////////////////////////////
//Finished!
#include "Alamo.h"
namespace Alamo
{

	typedef std::string alaString;

	typedef std::string GString;

	template<typename T>
	struct GPoint2D
	{
		T xCom, yCom;
		GPoint2D(const T & x = T(), const T & y = T());
	};


	struct alaPoint2D
	{
		int x, y;
		alaPoint2D()
		{
			x = y = 0;
		}
		alaPoint2D(int _x, int _y)
		{
			x = _x; y = _y;
		}
	};

	struct alaPointf2D
	{
		float x, y;
		alaPointf2D()
		{
			x = y = 0.0f;
		}
		alaPointf2D(float _x, float _y)
		{
			x = _x; y = _y;
		}
	};

	struct alaBitmapRegion
	{
		int top, left, bottom, right;
		alaBitmapRegion()
		{
			top = left = bottom = right = 0;
		}
	};

	struct alaColorRGB
	{
		float R, G, B;

		alaColorRGB(float rval = 0.0f,
			float gval = 0.0f,
			float bval = 0.0f) :R(rval), G(gval), B(bval) {}

		alaColorRGB(int rval,
			int gval,
			int bval) :R((float)rval / 255.0f), G((float)gval / 255.0f), B((float)bval / 255.0f) {}

		bool operator !=(const alaColorRGB & rhOp)const
		{
			if ((R != rhOp.R) ||
				(G != rhOp.G) ||
				(B != rhOp.G))return (false);
			else return (true);
		}

		bool operator ==(const alaColorRGB & rhOp)const
		{
			if ((R == rhOp.R) &&
				(G == rhOp.G) &&
				(B == rhOp.G))return (true);
			else return (false);
		}
	};


	struct alaColorRGBA
	{
		float R, G, B, A;

		alaColorRGBA(float rval = 0.0f,
			float gval = 0.0f,
			float bval = 0.0f,
			float aval = 0.0f) :R(rval), G(gval), B(bval), A(aval) {}

		alaColorRGBA(int rval,
			int gval,
			int bval,
			int aval) :R((float)rval / 255.0f), G((float)gval / 255.0f), B((float)bval / 255.0f), A((float)aval / 255.0f) {}

		bool operator !=(const alaColorRGBA & rhOp)const
		{
			if ((R != rhOp.R) ||
				(G != rhOp.G) ||
				(B != rhOp.B) ||
				(A != rhOp.A))return (false);
			else return (true);
		}

		bool operator ==(const alaColorRGBA & rhOp)const
		{
			if ((R == rhOp.R) &&
				(G == rhOp.G) &&
				(B == rhOp.B) &&
				(A == rhOp.A))return (true);
			else return (false);
		}
	};

	class alaVector2D
	{
	private:
		int x, y;
	public:

		alaVector2D();
		alaVector2D(int _x, int _y);
		void X(int _x);
		void Y(int _y);

		int Y();
		int X();

		alaVector2D
			operator+(const alaVector2D & rhOp)const;

		alaVector2D
			operator-(const alaVector2D & rhOp)const;

		alaVector2D
			operator*(int rhOp)const;

		alaVector2D
			operator/(int rhOp)const;

		friend alaVector2D
			operator*(int lhOp, const alaVector2D & rhOp);

		alaVector2D &
			operator+=(const alaVector2D & rhOp);

		alaVector2D &
			operator-=(const alaVector2D & rhOp);

		alaVector2D &
			operator*=(int rhOp);

		alaVector2D &
			operator/=(int rhOp);

		int Dot(const alaVector2D & rhOp)const;

		int Magnitude()const;
		alaVector2D Normalize()const;
	};


	class alaVectorf2D
	{
	private:
		float x, y;
	public:

		alaVectorf2D();
		alaVectorf2D(float _x, float _y);
		void X(float _x);
		void Y(float _y);

		float Y();
		float X();

		alaVectorf2D
			operator+(const alaVectorf2D & rhOp)const;

		alaVectorf2D
			operator-(const alaVectorf2D & rhOp)const;

		alaVectorf2D
			operator*(float rhOp)const;

		alaVectorf2D
			operator/(float rhOp)const;

		friend alaVectorf2D
			operator*(float lhOp, const alaVectorf2D & rhOp);

		alaVectorf2D &
			operator+=(const alaVectorf2D & rhOp);

		alaVectorf2D &
			operator-=(const alaVectorf2D & rhOp);

		alaVectorf2D &
			operator*=(float rhOp);

		alaVectorf2D &
			operator/=(float rhOp);

		float Dot(const alaVectorf2D & rhOp)const;

		float Magnitude()const;
		alaVectorf2D Normalize()const;
	};


	template <typename T>
	class GVector2D{
	private:
		int xCom, yCom;
	public:
		GVector2D(const T & x = T(), const T & y = T()) :xCom(x), tCom(y) {}
		int X();
		int Y();
		void X(const T & x);
		void Y(const T & y);
		GVector2D<T> operator+(const GVector2D<T> & rhs)const;
		GVector2D<T> operator-(const GVector2D<T> & rhs)const;
		GVector2D<T> operator*(const T & scale)const;
		GVector2D<T> operator*(const GVector2D<T> & rhs)const;
		friend GVector2D<T> operator*(const T & scale, const GVector2D<T> & rhs);
		GVector2D<T> & operator+=(const GVector2D<T> & rhs);
		GVector2D<T> & operator-=(const GVector2D<T> & rhs);
		GVector2D<T> & operator*=(const T & scale);
		GVector2D<T> & operator*=(const GVector2D<T> & rhs);
		T Magnitude()const;
		GVector2D<T> Normalize()const;
	};

}

#endif // !_ALAMO_TYPE_H_
