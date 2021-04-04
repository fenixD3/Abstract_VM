#pragma once

#include <string>

enum class eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double,
	Unknown
};

class IOperand
{
public:
	virtual int getPrecision() const = 0;
	virtual eOperandType getType() const = 0;

	virtual const IOperand* operator+(const IOperand& rhs) const = 0;
	virtual const IOperand* operator-(const IOperand& rhs) const = 0;
	virtual const IOperand* operator*(const IOperand& rhs) const = 0;
	virtual const IOperand* operator/(const IOperand& rhs) const = 0;
	virtual const IOperand* operator%(const IOperand& rhs) const = 0;

	virtual const std::string& toString() const = 0; // String representation of the instance

	virtual ~IOperand() = default;
};
