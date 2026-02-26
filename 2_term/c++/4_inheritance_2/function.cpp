#include "function.hpp"

#include <exception>
#include <random>

static std::mt19937 s_RandomEngine;

using Distribution = std::uniform_real_distribution<>;

Function_Const::Function_Const(double offset) : offset(offset)
{
	
}

double Function_Const::value(double) const
{
	return offset;
}

IFunction* Function_Const::derivative() const
{
	return new Function_Const(0.0);
}

void Function_Const::print(std::ostream& os) const
{
	os << "[Const] Offset: " << offset;
}

void Function_Const::input(std::istream& is)
{
	std::cout << "[Const] Enter an offset: ";
	is >> offset;
}

void Function_Const::fill_randomly()
{
	double min, max;

	std::cout << "Enter min and max values for const: ";
	std::cin >> min >> max;

	Distribution dist(min, max);
	offset = dist(s_RandomEngine);
}

Function_Linear::Function_Linear(double slope, double offset)
	: slope(slope), offset(offset)
{
}

double Function_Linear::value(double param) const
{
	return slope * param + offset;
}

IFunction* Function_Linear::derivative() const
{
	return new Function_Const(slope);
}

void Function_Linear::print(std::ostream& os) const
{
	os << "[Linear Function] Slope: " << slope << ", offset: " << offset;
}

void Function_Linear::input(std::istream& is)
{
	std::cout << "[Linear Function] Enter a slope and an offset: ";
	is >> slope >> offset;
}

void Function_Linear::fill_randomly()
{
	double min_slope, max_slope, min_offset, max_offset;

	std::cout << "Enter min and max values for slope: ";
	std::cin >> min_slope >> max_slope;

	std::cout << "Enter min and max values for offset: ";
	std::cin >> min_offset >> max_offset;

	Distribution slope_dist(min_slope, max_slope);
	Distribution slope_offset(min_offset, max_offset);
	
	slope = slope_dist(s_RandomEngine);
	offset = slope_offset(s_RandomEngine);
}

Function_Quadratic::Function_Quadratic(double offset_x, double offset_y, double curvature)
	: offset_x(offset_x), offset_y(offset_y), curvature(curvature)
{
}

double Function_Quadratic::value(double param) const
{
	double x = param - offset_x;
	return curvature * x * x + offset_y;
}

IFunction* Function_Quadratic::derivative() const
{
	double slope = 2.0 * curvature;
	return new Function_Linear(slope, -2.0 * curvature * offset_x);
}

void Function_Quadratic::print(std::ostream& os) const
{
	os << "[Quadratic Function] Offset: (" << offset_x << ", " << offset_y << "), curvature: " << curvature;
}

void Function_Quadratic::input(std::istream& is)
{
	std::cout << "[Quadratic Function] Enter offset x, y coordinates and a curvature: ";
	is >> offset_x >> offset_y >> curvature;
}

void Function_Quadratic::fill_randomly()
{
	double min_x, max_x, min_y, max_y, min_curvature, max_curvature;

	std::cout << "Enter min and max values for vertex x coord: ";
	std::cin >> min_x >> max_x;

	std::cout << "Enter min and max values for vertex y coord: ";
	std::cin >> min_y >> max_y;

	std::cout << "Enter min and max values for curvature: ";
	std::cin >> min_curvature >> max_curvature;

	Distribution x_dist(min_x, max_x);
	Distribution y_dist(min_y, max_y);
	Distribution curvature_dist(min_curvature, max_curvature);
	
	offset_x = x_dist(s_RandomEngine);
	offset_y = y_dist(s_RandomEngine);
	curvature = curvature_dist(s_RandomEngine);
}

std::ostream& operator<<(std::ostream& os, const IFunction* func) { func->print(os); return os; }
std::istream& operator>>(std::istream& is, IFunction* func) { func->input(is); return is; }
