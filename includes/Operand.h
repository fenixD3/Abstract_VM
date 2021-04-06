#pragma once

#include "OperandCreator.h"
#include <algorithm>
#include <cmath>

template <typename TType>
class Operand : public IOperand
{
public:
	Operand(TType aNumber, const std::string& aStrNumber, eOperandType aType);

	int getPrecision() const override;
	eOperandType getType() const override;

	const IOperand* operator+(const IOperand& rhs) const override;
	const IOperand* operator-(const IOperand& rhs) const override;
	const IOperand* operator*(const IOperand& rhs) const override;
	const IOperand* operator/(const IOperand& rhs) const override;
	const IOperand* operator%(const IOperand& rhs) const override;
    const IOperand* max(const IOperand& rhs) const override;
    const IOperand* min(const IOperand& rhs) const override;
    const IOperand* avg(const IOperand& rhs) const override;
    const IOperand* pow(const IOperand& rhs) const override;
    const IOperand* operator^(const IOperand& rhs) const override;
    const IOperand* operator|(const IOperand& rhs) const override;
    const IOperand* operator&(const IOperand& rhs) const override;

	const std::string& toString() const override;

private:
	TType mNumber;
	std::string mStrNumber;
	eOperandType mType;

};

template <typename TType>
Operand<TType>::Operand(TType aNumber, const std::string& aStrNumber, eOperandType aType)
	: mNumber(aNumber)
	, mStrNumber(aStrNumber)
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
	double rightNum = std::stod(rhs.toString());
	if (resultType == eOperandType::Float || resultType == eOperandType::Double)
        return Create::creator.createOperand(resultType, std::to_string(static_cast<double>(mNumber + rightNum)));
	else
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber + rightNum)));
}

template <typename TType>
const IOperand* Operand<TType>::operator-(const IOperand& rhs) const
{
	eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
    double rightNum = std::stod(rhs.toString());
    if (resultType == eOperandType::Float || resultType == eOperandType::Double)
        return Create::creator.createOperand(resultType, std::to_string(static_cast<double>(mNumber - rightNum)));
    else
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber - rightNum)));
}

template <typename TType>
const IOperand* Operand<TType>::operator*(const IOperand& rhs) const
{
	eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
    double rightNum = std::stod(rhs.toString());
    if (resultType == eOperandType::Float || resultType == eOperandType::Double)
        return Create::creator.createOperand(resultType, std::to_string(static_cast<double>(mNumber * rightNum)));
    else
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber * rightNum)));
}

template <typename TType>
const IOperand* Operand<TType>::operator/(const IOperand& rhs) const
{
	eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
    double rightNum = std::stod(rhs.toString());
    if (resultType == eOperandType::Float || resultType == eOperandType::Double)
        return Create::creator.createOperand(resultType, std::to_string(static_cast<double>(mNumber / rightNum)));
    else
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber / rightNum)));
}

template <typename TType>
const IOperand* Operand<TType>::operator%(const IOperand& rhs) const
{
	if constexpr (std::is_same_v<TType, float> || std::is_same_v<TType, double>)
		return nullptr;
	else
	{
	    if (rhs.getType() == eOperandType::Float || rhs.getType() == eOperandType::Double)
            return nullptr;
		eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
        int64_t rightNum = std::stoi(rhs.toString());
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber % rightNum)));
	}
}

template<typename TType>
const IOperand *Operand<TType>::max(const IOperand &rhs) const
{
    eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
    double rightNum = std::stod(rhs.toString());
    if (resultType == eOperandType::Float || resultType == eOperandType::Double)
        return Create::creator.createOperand(
            resultType,
            std::to_string(std::max(static_cast<double>(mNumber), static_cast<double>(rightNum))));
    else
        return Create::creator.createOperand(
            resultType,
            std::to_string(std::max(static_cast<int64_t>(mNumber), static_cast<int64_t>(rightNum))));
}

template<typename TType>
const IOperand *Operand<TType>::min(const IOperand &rhs) const
{
    eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
    double rightNum = std::stod(rhs.toString());
    if (resultType == eOperandType::Float || resultType == eOperandType::Double)
        return Create::creator.createOperand(
                resultType,
                std::to_string(std::min(static_cast<double>(mNumber), static_cast<double>(rightNum))));
    else
        return Create::creator.createOperand(
                resultType,
                std::to_string(std::min(static_cast<int64_t>(mNumber), static_cast<int64_t>(rightNum))));
}

template<typename TType>
const IOperand *Operand<TType>::avg(const IOperand &rhs) const
{
    eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
    double rightNum = std::stod(rhs.toString());
    if (resultType == eOperandType::Float || resultType == eOperandType::Double)
        return Create::creator.createOperand(resultType, std::to_string(static_cast<double>(mNumber + rightNum) / 2));
    else
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber + rightNum) / 2));
}

template<typename TType>
const IOperand *Operand<TType>::pow(const IOperand &rhs) const
{
    eOperandType resultType = mType;
    int64_t rightNum = std::stoi(rhs.toString());
    if (resultType == eOperandType::Float || resultType == eOperandType::Double)
        return Create::creator.createOperand(resultType, std::to_string(static_cast<double>(std::pow(mNumber, rightNum))));
    else
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(std::pow(mNumber, rightNum))));
}

template <typename TType>
const IOperand* Operand<TType>::operator^(const IOperand& rhs) const
{
    if constexpr (std::is_same_v<TType, float> || std::is_same_v<TType, double>)
        return nullptr;
    else
    {
        if (rhs.getType() == eOperandType::Float || rhs.getType() == eOperandType::Double)
            return nullptr;
        eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
        int64_t rightNum = std::stoi(rhs.toString());
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber ^ rightNum)));
    }
}

template <typename TType>
const IOperand* Operand<TType>::operator|(const IOperand& rhs) const
{
    if constexpr (std::is_same_v<TType, float> || std::is_same_v<TType, double>)
        return nullptr;
    else
    {
        if (rhs.getType() == eOperandType::Float || rhs.getType() == eOperandType::Double)
            return nullptr;
        eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
        int64_t rightNum = std::stoi(rhs.toString());
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber | rightNum)));
    }
}

template <typename TType>
const IOperand* Operand<TType>::operator&(const IOperand& rhs) const
{
    if constexpr (std::is_same_v<TType, float> || std::is_same_v<TType, double>)
        return nullptr;
    else
    {
        if (rhs.getType() == eOperandType::Float || rhs.getType() == eOperandType::Double)
            return nullptr;
        eOperandType resultType = (rhs.getType() > mType) ? rhs.getType() : mType;
        int64_t rightNum = std::stoi(rhs.toString());
        return Create::creator.createOperand(resultType, std::to_string(static_cast<int64_t>(mNumber & rightNum)));
    }
}

template <typename TType>
const std::string& Operand<TType>::toString() const
{
	return mStrNumber;
}
