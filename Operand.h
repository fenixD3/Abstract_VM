#pragma once

#include "IOperand.h"

template<typename TType>
class Operand : public IOperand
{
public:
	int getPrecision() const override;
	eOperandType getType() const override;

	const IOperand* operator+(const IOperand& rhs) const override;
	const IOperand* operator-(const IOperand& rhs) const override;
	const IOperand* operator*(const IOperand& rhs) const override;
	const IOperand* operator/(const IOperand& rhs) const override;
	const IOperand* operator%(const IOperand& rhs) const override;

	const std::string& toString() const override;

private:
	TType mNumber;

};
