#pragma once

#include "IOperand.h"

template <typename TType>
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
	eOperandType mType;
};

template <typename TType>
int Operand<TType>::getPrecision() const
{

}

template <typename TType>
eOperandType Operand<TType>::getType() const
{
	return mType;
}

/// TODO write crate new IOperand in operator functions and call getPrecision() as first
template <typename TType>
const IOperand* Operand<TType>::operator+(const IOperand& rhs) const
{
	std::string newNumber = std::to_string(mNumber + rhs);
}

template <typename TType>
const IOperand* Operand<TType>::operator-(const IOperand& rhs) const
{
	std::string newNumber = std::to_string(mNumber - rhs);
}

template <typename TType>
const IOperand* Operand<TType>::operator*(const IOperand& rhs) const
{
	std::string newNumber = std::to_string(mNumber * rhs);
}

template <typename TType>
const IOperand* Operand<TType>::operator/(const IOperand& rhs) const
{
	std::string newNumber = std::to_string(mNumber / rhs);
}

template <typename TType>
const IOperand* Operand<TType>::operator%(const IOperand& rhs) const
{
	std::string newNumber = std::to_string(mNumber % rhs);
}

template <typename TType>
const std::string& Operand<TType>::toString() const
{
	return std::to_string(mNumber);
}
