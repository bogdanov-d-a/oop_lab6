#include "stdafx.h"
#include "Triangle.h"

using namespace std;

CTriangle::CTriangle(double side1, double side2, double side3)
	:m_side1(side1)
	,m_side2(side2)
	,m_side3(side3)
{
	ThrowOnBadSideLength(1, m_side1);
	ThrowOnBadSideLength(2, m_side2);
	ThrowOnBadSideLength(3, m_side3);

	if (IsDegenerate())
	{
		throw domain_error("Can't create degenerate triangle");
	}
}

double CTriangle::GetSide1() const
{
	return m_side1;
}

double CTriangle::GetSide2() const
{
	return m_side2;
}

double CTriangle::GetSide3() const
{
	return m_side3;
}

double CTriangle::GetPerimeter() const
{
	return (m_side1 + m_side2 + m_side3);
}

double CTriangle::GetArea() const
{
	double const halfPerimeter = GetPerimeter() / 2;
	return sqrt(
		halfPerimeter *
		(halfPerimeter - m_side1) *
		(halfPerimeter - m_side2) *
		(halfPerimeter - m_side3)
	);
}

void CTriangle::ThrowOnBadSideLength(unsigned number, double value)
{
	if (value < 0)
	{
		throw invalid_argument("Side " + to_string(number) + " length can't be negative");
	}
}

bool CTriangle::SideIsTooBig(double testSide, double side1, double side2)
{
	return (testSide > side1 + side2);
}

bool CTriangle::IsDegenerate() const
{
	return (
		SideIsTooBig(m_side1, m_side2, m_side3) ||
		SideIsTooBig(m_side2, m_side3, m_side1) ||
		SideIsTooBig(m_side3, m_side1, m_side2)
	);
}
