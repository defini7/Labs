// 20

#include "function.hpp"

void ReadByType(Function* func, int type)
{
	switch (type)
	{
	case 1: std::cin >> *(Function_Const*)func; break;
	case 2: std::cin >> *(Function_Linear*)func; break;
	case 3: std::cin >> *(Function_Quadratic*)func; break;
	};
}

void PrintByType(Function* func, int type)
{
	switch (type)
	{
	case 1: std::cout << *(Function_Const*)func << std::endl; break;
	case 2: std::cout << *(Function_Linear*)func << std::endl; break;
	case 3: std::cout << *(Function_Quadratic*)func << std::endl; break;
	};
}

void FillRandomlyByType(Function* func, int type)
{
	if (type == 1)
	{
		double minValue, maxValue;

		std::cout << "Enter min and max values for const: ";
		std::cin >> minValue >> maxValue;

		FillRandomly(*(Function_Const*)func, minValue, maxValue);
	}
	else if (type == 2)
	{
		double minSlope, maxSlope, minOffset, maxOffset;

		std::cout << "Enter min and max values for slope: ";
		std::cin >> minSlope >> maxSlope;

		std::cout << "Enter min and max values for offset: ";
		std::cin >> minOffset >> maxOffset;

		FillRandomly(
			*(Function_Linear*)func,
			minSlope, maxSlope,
			minOffset, maxOffset);
	}
	else
	{
		double minVertexX, maxVertexX, minVertexY, maxVertexY, minCurvature, maxCurvature;

		std::cout << "Enter min and max values for vertex x coord: ";
		std::cin >> minVertexX >> maxVertexX;

		std::cout << "Enter min and max values for vertex y coord: ";
		std::cin >> minVertexY >> maxVertexY;

		std::cout << "Enter min and max values for curvature: ";
		std::cin >> minCurvature >> maxCurvature;

		FillRandomly(
			*(Function_Quadratic*)func,
			minVertexX, maxVertexX,
			minVertexY, maxVertexY,
			minCurvature, maxCurvature);
	}
}

int main()
{
	std::cout << "Demo\n\n";
	std::cout << "Choose a function:\n\t1 - const\n\t2 - linear\n\t3 - quadratic\n";
	
	int funcType, method;
	
	/*Function_Quadratic func;
	func.Function::GetDerivative();
	func.Function_Quadratic::GetDerivative();*/

	do std::cin >> funcType;
	while (funcType < 1 || funcType > 3); 
	
	Function* func = nullptr;
	
	switch (funcType)
	{
	case 1: func = new Function_Const(); break;
	case 2: func = new Function_Linear(); break;
	case 3: func = new Function_Quadratic(); break;
	}
	
	do
	{
		std::cout << "Choose a method to enter data:\n\t1 - manualy\n\t2 - randomly\n";
		std::cin >> method;
	} while (method != 1 && method != 2);
	
	if (method == 1)
		ReadByType(func, funcType);
	else
		FillRandomlyByType(func, funcType);
	
	std::cout << "Function: ";
	PrintByType(func, funcType);

	#define PRINT_DERIVATIVE(DerType, FuncType) \
		do \
		{ \
			DerType deriv = ((FuncType*)func)->GetDerivative(); \
			std::cout << deriv << std::endl; \
		} while (0)

	std::cout << "Derivative: ";

	if (funcType == 1)
		PRINT_DERIVATIVE(Function_Const, Function_Const);
	else if (funcType == 2)
		PRINT_DERIVATIVE(Function_Const, Function_Linear);
	else
		PRINT_DERIVATIVE(Function_Linear, Function_Quadratic);
}
