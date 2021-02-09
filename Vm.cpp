#include "Vm.h"
#include "Error.h"

#include <cctype>

void Vm::Process(const std::vector<Lexer::Lexeme>& aLexemesList)
{
	for (const auto& lexeme : aLexemesList)
	{
		if (!mError.empty())
			return;
		++mLineCount;
		if (lexeme.isComment)
			continue;
		if (lexeme.Instruction == "push")
			mStore.push_front(std::unique_ptr<const IOperand>(Create::creator.createOperand(lexeme.Type, lexeme.Value)));
		else if (lexeme.Instruction == "pop")
			mStore.pop_front();
		else if (lexeme.Instruction == "dump")
			for (const auto& value : mStore)
				mStreamToOut << value->toString() << '\n';
		else if (lexeme.Instruction == "assert")
		{
			if (lexeme.Type != mStore.front()->getType() || lexeme.Value != mStore.front()->toString())
				mError += "Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::AssertIsNotTrue;
		}
		else if (lexeme.Instruction == "add")
		{
			auto rightOperand = std::move(mStore.front());
			mStore.pop_front();
			auto leftOperand = std::move(mStore.front());
			mStore.pop_front();
			mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand + *rightOperand));
		}
		else if (lexeme.Instruction == "sub")
		{
			auto rightOperand = std::move(mStore.front());
			mStore.pop_front();
			auto leftOperand = std::move(mStore.front());
			mStore.pop_front();
			mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand - *rightOperand));
		}
		else if (lexeme.Instruction == "mul")
		{
			auto rightOperand = std::move(mStore.front());
			mStore.pop_front();
			auto leftOperand = std::move(mStore.front());
			mStore.pop_front();
			mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand * *rightOperand));
		}
		else if (lexeme.Instruction == "div")
		{
			auto rightOperand = std::move(mStore.front());
			mStore.pop_front();
			auto leftOperand = std::move(mStore.front());
			if (leftOperand->toString() == "0")
			{
				mError += "Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::DivisionZero;
				continue;
			}
			mStore.pop_front();
			mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand / *rightOperand));
		}
		else if (lexeme.Instruction == "mod")
		{
			auto rightOperand = std::move(mStore.front());
			mStore.pop_front();
			auto leftOperand = std::move(mStore.front());
			if (leftOperand->toString() == "0") /// TODO Check to_string in floating point as 0., 0.0 etc
			{
				mError += "Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::ModuloZero;
				continue;
			}
			mStore.pop_front();
			mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand % *rightOperand));
		}
		else if (lexeme.Instruction == "print")
		{
			if (mStore.front()->getType() != eOperandType::Int8)
			{
				mError += "Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::PrintError;
				continue;
			}
			unsigned char number = std::stoi(mStore.front()->toString());
			if (isprint(number))
				mStreamToOut << number << '\n';
		}
		else if (lexeme.Instruction == "exit")
			return; /// TODO may be check that lexemes no longer exist
	}
}
