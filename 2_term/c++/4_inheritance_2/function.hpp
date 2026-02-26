#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>

class IFunction
{
public:
	IFunction() = default;
	virtual ~IFunction() = default;
	
	virtual double value(double param) const = 0;
	virtual IFunction* derivative() const = 0;

	virtual void print(std::ostream&) const = 0;
	virtual void input(std::istream&) = 0;

	virtual void fill_randomly() = 0;
	
};

class Function_Const final : public IFunction
{
public:
	Function_Const() = default;
	Function_Const(double offset);

	double value(double param) const override;
	IFunction* derivative() const override;

	void print(std::ostream&) const override;
	void input(std::istream&) override;

	void fill_randomly() override;
	
public:
	double offset;
	
};

class Function_Linear final : public IFunction
{
public:
	Function_Linear() = default;
	Function_Linear(double slope, double offset);

	double value(double param) const override;
	IFunction* derivative() const override;

	void print(std::ostream&) const override;
	void input(std::istream&) override;

	void fill_randomly() override;
	
public:
	double slope;
	double offset;

};

class Function_Quadratic final : public IFunction
{
public:
	Function_Quadratic() = default;
	Function_Quadratic(double offset_x, double offset_y, double curvature);

	double value(double param) const override;
	IFunction* derivative() const override;

	void print(std::ostream&) const override;
	void input(std::istream&) override;

	void fill_randomly() override;
	
public:
	double offset_x;
	double offset_y;
	double curvature;
	
};

std::ostream& operator<<(std::ostream& os, const IFunction* func);
std::istream& operator>>(std::istream& is, IFunction* func);

#endif

