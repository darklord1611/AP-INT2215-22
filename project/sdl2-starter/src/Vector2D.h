#include<math.h>

#ifndef __Vector2D__
#define __Vector2D__

class Vector2D 
{
private:
    double m_x;
    double m_y;
public:
	Vector2D() {}
    Vector2D(double x, double y) : m_x(x), m_y(y) {}
    double getX() { return m_x; }
    double getY() { return m_y; }
    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }
    double length();

    //addition of two Vectors using + or +=
	Vector2D operator + (const Vector2D& v2) const;
	friend Vector2D& operator += (Vector2D& v1, const Vector2D& v2);
	
	//multiplication of a vector with a scalar number using * or *=
	Vector2D operator * (double scalar);
	Vector2D& operator *= (double scalar);

	//subtraction of two vector using - or -=
	Vector2D operator - (const Vector2D& v2) const;
	friend Vector2D& operator -= (Vector2D& v1, const Vector2D& v2);

	//division of a vector by a scalar number using / or /=
	Vector2D operator / (double scalar);
	Vector2D& operator /= (double scalar);

	//normalizing a vector
	void normalize();
};

#endif // define __Vector2D__