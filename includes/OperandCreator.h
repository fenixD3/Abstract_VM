#pragma once

#include "IOperand.h"

class OperandCreator
{
public:
	OperandCreator() = default;
	~OperandCreator() = default;

	OperandCreator(const OperandCreator& aOther) = default;
	OperandCreator& operator=(const OperandCreator& aOther) = default;

	const IOperand* createOperand(eOperandType type, const std::string& value) const;

private:
	const IOperand* createInt8(const std::string& value) const;
	const IOperand* createInt16(const std::string& value) const;
	const IOperand* createInt32(const std::string& value) const;
	const IOperand* createFloat(const std::string& value) const;
	const IOperand* createDouble(const std::string& value) const;

};

namespace Create
{
constexpr OperandCreator creator;
}
