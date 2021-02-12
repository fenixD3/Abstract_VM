#include "Vm.h"

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
			ProcessPush(lexeme.Type, lexeme.Value);
		else if (lexeme.Instruction == "pop")
			ProcessPop();
		else if (lexeme.Instruction == "dump")
			ProcessDump();
		else if (lexeme.Instruction == "assert")
            ProcessAssert(lexeme.Type, lexeme.Value);
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
			ProcessArithmetic();
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
            ProcessPrint();
		else if (lexeme.Instruction == "exit")
			ProcessExit(); /// TODO may be check that lexemes no longer exist
	}
}

void Vm::ProcessPush(eOperandType aType, const std::string& aValue)
{
    mStore.push_front(std::unique_ptr<const IOperand>(Create::creator.createOperand(aType, aValue)));
}

void Vm::ProcessPop()
{
    mStore.pop_front();
}

void Vm::ProcessDump() const
{
    for (const auto& value : mStore)
        mStreamToOut << value->toString() << '\n';
}

void Vm::ProcessAssert(eOperandType aType, const std::string& aValue) const
{
    if (aType != mStore.front()->getType() || aValue != mStore.front()->toString())
        mError += "Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::AssertIsNotTrue;
}

void Vm::ProcessPrint() const
{
    if (mStore.front()->getType() != eOperandType::Int8)
        mError += "Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::PrintError;
    unsigned char number = std::stoi(mStore.front()->toString());
    if (isprint(number))
        mStreamToOut << number << '\n';
}

void Vm::ProcessExit() const
{

}

void Vm::ProcessArithmetic()
{
	auto rightOperand = std::move(mStore.front());
	mStore.pop_front();
	auto leftOperand = std::move(mStore.front());
	if (leftOperand->toString() == "0")
		mError += "Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::DivisionZero;
	mStore.pop_front();
	ProcessArithmeticImpl(&Operand<int>::operator/, leftOperand.get(), *rightOperand);
}
