#pragma once

#include "Operand.h"
#include "Lexer.h"

#include <deque>
#include <memory>
#include <sstream>

class Vm
{
public:
	void Process(const std::vector<Lexer::Lexeme>& aLexemesList);

private:
	size_t mLineCount = 0;
	std::deque<std::unique_ptr<const IOperand>> mStore;
	std::string mError;
	std::stringstream mStreamToOut;

};
