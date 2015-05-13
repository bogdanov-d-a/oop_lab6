#pragma once

class CTriangle
{
public:
	CTriangle(double side1, double side2, double side3);

	double GetSide1() const;
	double GetSide2() const;
	double GetSide3() const;

	double GetPerimeter() const;
	double GetArea() const;

private:
	double m_side1, m_side2, m_side3;

	static void ThrowOnBadSideLength(unsigned number, double value);
	static bool SideIsTooBig(double testSide, double side1, double side2);
	bool IsDegenerate() const;
};
