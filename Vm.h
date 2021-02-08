#pragma once

#include "IOperand.h"
#include <stack>
#include <memory>

class Vm
{
public:


private:
	std::stack<std::unique_ptr<IOperand>> mStore;

};
