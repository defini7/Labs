#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>

class Function
{
public:
	Function() = default;
	
	double GetValue(double param) const;
	Function GetDerivative() const;
	
};

class Function_Const : public Function
{
public:
	Function_Const() = default;
	Function_Const(double offset);

	double GetValue(double param) const;
	Function_Const GetDerivative() const;
	
public:
	double OffsetY;
	
};

class Function_Linear : public Function
{
public:
	Function_Linear() = default;
	Function_Linear(double slope, double offset);

	double GetValue(double param) const;
	Function_Const GetDerivative() const;
	
public:
	double Slope;
	double OffsetY;

};

class Function_Quadratic : public Function
{
public:
	Function_Quadratic() = default;
	Function_Quadratic(double offsetX, double offsetY, double curvature);

	double GetValue(double param) const;
	Function_Linear GetDerivative() const;
	
public:
	double OffsetX;
	double OffsetY;
	double Curvature;
	
};

std::ostream& operator<<(std::ostream& os, const Function& func);
std::istream& operator>>(std::istream& is, Function& func);

std::ostream& operator<<(std::ostream& os, const Function_Const& func);
std::istream& operator>>(std::istream& is, Function_Const& func);

std::ostream& operator<<(std::ostream& os, const Function_Linear& func);
std::istream& operator>>(std::istream& is, Function_Linear& func);

std::ostream& operator<<(std::ostream& os, const Function_Quadratic& func);
std::istream& operator>>(std::istream& is, Function_Quadratic& func);

void FillRandomly(Function& func);
void FillRandomly(Function_Const& func, double min, double max);
void FillRandomly(Function_Linear& func, double minSlope, double maxSlope, double minOffset, double maxOffset);
void FillRandomly(Function_Quadratic& func, double minVertexX, double maxVertexX, double minVertexY, double maxVertexY, double minCurvature, double maxCurvature);

#endif

