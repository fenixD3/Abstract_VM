#include "OperandCreator.h"
#include "Operand.h"

const IOperand* OperandCreator::createOperand(eOperandType type, const std::string& value) const
{
	switch (type)
	{

	case eOperandType::Int8:
		return createInt8(value);
	case eOperandType::Int16:
		return createInt16(value);
	case eOperandType::Int32:
		return createInt32(value);
	case eOperandType::Float:
		return createFloat(value);
	case eOperandType::Double:
		return createDouble(value);
    default:
        return nullptr;

	}
}

const IOperand* OperandCreator::createInt8(const std::string& value) const
{
	return new Operand<int8_t>(std::stoi(value), eOperandType::Int8);
}

const IOperand* OperandCreator::createInt16(const std::string& value) const
{;
	return new Operand<int16_t>(std::stoi(value), eOperandType::Int16);
}

const IOperand* OperandCreator::createInt32(const std::string& value) const
{
	return new Operand<int32_t>(std::stoi(value), eOperandType::Int32);
}

const IOperand* OperandCreator::createFloat(const std::string& value) const
{
	return new Operand<float>(std::stod(value), eOperandType::Int8);
}

const IOperand* OperandCreator::createDouble(const std::string& value) const
{
	return new Operand<double>(std::stod(value), eOperandType::Int8);
}
