#pragma once

#include "OperandCreator.h"

template <typename TType>
class Operand : public IOperand
{
public:
	Operand(TType aNumber, eOperandType aType);

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

private:

};

template <typename TType>
Operand<TType>::Operand(TType aNumber, eOperandType aType)
	: mNumber(aNumber)
	, mType(aType)
{}

template <typename TType>
int Operand<TType>::getPrecision() const
{
	return static_cast<int>(mType);
}

template <typename TType>
eOperandType Operand<TType>::getType() const
{
	return mType;
}

template <typename TType>
const IOperand* Operand<TType>::operator+(const IOperand& rhs) const
{
	eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
	int32_t rightNum = std::stol(rhs.toString());
	std::string newNumber = std::to_string(mNumber + rightNum);
	return Create::creator.createOperand(resultType, newNumber);
}

template <typename TType>
const IOperand* Operand<TType>::operator-(const IOperand& rhs) const
{
	eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
	int32_t rightNum = std::stol(rhs.toString());
	std::string newNumber = std::to_string(mNumber - rightNum);
	return Create::creator.createOperand(resultType, newNumber);
}

template <typename TType>
const IOperand* Operand<TType>::operator*(const IOperand& rhs) const
{
	eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
	int32_t rightNum = std::stol(rhs.toString());
	std::string newNumber = std::to_string(mNumber * rightNum);
	return Create::creator.createOperand(resultType, newNumber);
}

template <typename TType>
const IOperand* Operand<TType>::operator/(const IOperand& rhs) const
{
	eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
	int32_t rightNum = std::stol(rhs.toString());
	std::string newNumber = std::to_string(mNumber / rightNum);
	return Create::creator.createOperand(resultType, newNumber);
}

template <typename TType>
const IOperand* Operand<TType>::operator%(const IOperand& rhs) const
{
	if constexpr (std::is_same_v<TType, float>
				|| std::is_same_v<TType, double>)
		return nullptr;
	else
	{
		eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
		int32_t rightNum = std::stol(rhs.toString());
		std::string newNumber = std::to_string(mNumber % rightNum);
		return Create::creator.createOperand(resultType, newNumber);
	}
}

template <typename TType>
const std::string& Operand<TType>::toString() const
{
	std::string&& res = std::to_string(mNumber);
	return res;
}
