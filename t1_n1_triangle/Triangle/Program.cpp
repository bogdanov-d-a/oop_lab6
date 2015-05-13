// Program.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Triangle.h"

using namespace std;

class InputEndException
{};

CTriangle PromptTriangleData()
{
	double side1, side2, side3;
	if (!(cin >> side1 >> side2 >> side3))
	{
		if (cin.eof())
		{
			throw InputEndException();
		}
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			throw runtime_error("Wrong data format");
		}
	}
	return CTriangle(side1, side2, side3);
}

int _tmain()
{
	try
	{
		for (;;)
		{
			try
			{
				CTriangle t(PromptTriangleData());
				cout << "Perimeter = " << t.GetPerimeter() << "; area = " << t.GetArea() << endl;
			}
			catch (exception const& e)
			{
				cout << e.what() << endl;
			}
		}
	}
	catch (InputEndException const&)
	{}

	return 0;
}
