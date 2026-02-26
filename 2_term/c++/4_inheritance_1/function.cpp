#include "function.hpp"

#include <exception>
#include <random>

static std::mt19937 s_RandomEngine;

double Function::GetValue(double param) const
{
	return +INFINITY;
}

Function Function::GetDerivative() const
{
	std::cerr << "Can't calculate a derivative for the undefined function" << std::endl;
	exit(1);
}

Function_Const::Function_Const(double offset) : OffsetY(offset)
{
	
}

double Function_Const::GetValue(double) const
{
	return OffsetY;
}

Function_Const Function_Const::GetDerivative() const
{
	return Function_Const(0.0);
}

Function_Linear::Function_Linear(double slope, double offset)
	: Slope(slope), OffsetY(offset)
{
}

double Function_Linear::GetValue(double param) const
{
	return Slope * param + OffsetY;
}

Function_Const Function_Linear::GetDerivative() const
{
	return Function_Const(Slope);
}

Function_Quadratic::Function_Quadratic(double offsetX, double offsetY, double curvature)
	: OffsetX(offsetX), OffsetY(offsetY), Curvature(curvature)
{
}

double Function_Quadratic::GetValue(double param) const
{
	double offsetX = param - OffsetX;
	return Curvature * offsetX * offsetX + OffsetY;
}

Function_Linear Function_Quadratic::GetDerivative() const
{
	double slope = 2.0 * Curvature;
	return Function_Linear(slope, -2.0 * Curvature * OffsetX);
}

std::ostream& operator<<(std::ostream& os, const Function& func) { return os; }
std::istream& operator>>(std::istream& is, Function& func) { return is; }

std::ostream& operator<<(std::ostream& os, const Function_Const& func)
{
	os << "[Const] Offset: " << func.OffsetY;
	return os;
}

std::istream& operator>>(std::istream& is, Function_Const& func)
{
	std::cout << "[Const] Enter an offset: ";
	is >> func.OffsetY;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Function_Linear& func)
{
	os << "[Linear Function] Slope: " << func.Slope << ", offset: " << func.OffsetY;
	return os;
}

std::istream& operator>>(std::istream& is, Function_Linear& func)
{
	std::cout << "[Linear Function] Enter a slope and an offset: ";
	is >> func.Slope >> func.OffsetY;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Function_Quadratic& func)
{
	os << "[Quadratic Function] Offset: (" << func.OffsetX << ", " << func.OffsetY << "), curvature: " << func.Curvature;
	return os;
}

std::istream& operator>>(std::istream& is, Function_Quadratic& func)
{
	std::cout << "[Quadratic Function] Enter offset x, y coordinates and a curvature: ";
	is >> func.OffsetX >> func.OffsetY >> func.Curvature;
	return is;
}

void FillRandomly(Function& func) {}

void FillRandomly(Function_Const& func, double min, double max)
{
	std::uniform_real_distribution<> dist(min, max);
	func.OffsetY = dist(s_RandomEngine);
}

void FillRandomly(Function_Linear& func, double minSlope, double maxSlope, double minOffset, double maxOffset)
{
	std::uniform_real_distribution<> slopeDist(minSlope, maxSlope);
	std::uniform_real_distribution<> slopeOffset(minOffset, maxOffset);
	
	func.Slope = slopeDist(s_RandomEngine);
	func.OffsetY = slopeOffset(s_RandomEngine);
}

void FillRandomly(Function_Quadratic& func, double minOffsetX, double maxOffsetX, double minOffsetY, double maxOffsetY, double minCurvature, double maxCurvature)
{
	std::uniform_real_distribution<> slopeOffsetX(minOffsetX, maxOffsetX);
	std::uniform_real_distribution<> slopeOffsetY(minOffsetY, maxOffsetY);
	std::uniform_real_distribution<> slopeCurvature(minCurvature, maxCurvature);
	
	func.OffsetX = slopeOffsetX(s_RandomEngine);
	func.OffsetY = slopeOffsetY(s_RandomEngine);
	func.Curvature = slopeCurvature(s_RandomEngine);
}


