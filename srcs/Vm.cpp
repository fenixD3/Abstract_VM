#include "../includes/Vm.h"

#include <cctype>

Vm::Vm(std::string aFileName)
    : mCodeAnalyzer(std::make_unique<CodeAnalyzer>(std::move(aFileName)))
    , mErrorManager(std::make_unique<ErrorManager>())
{}

void Vm::Process()
{
    try
    {
        auto lexemesList = ProcessCompilingCodeAnalyzing();
        for (const auto& lexeme : lexemesList)
        {
            ++mLineCount;

            if (lexeme.isComment)
                continue;
            try
            {
                if (lexeme.Instruction == "push")
                    ProcessPush(lexeme.Type, lexeme.Value);
                else if (lexeme.Instruction == "pop")
                    ProcessPop();
                else if (lexeme.Instruction == "dump")
                    ProcessDump();
                else if (lexeme.Instruction == "assert")
                    ProcessAssert(lexeme.Type, lexeme.Value);
                else if (lexeme.Instruction == "print")
                    ProcessPrint();
                else if (lexeme.Instruction == "exit")
                    return;
                else
                    ProcessArithmetic(lexeme.Instruction);
            }
            catch (const std::exception& aError)
            {
                mErrorManager->AddError(aError.what());
            }
        }
        if (!mErrorManager->IsEmptyError())
            throw std::system_error();
    }
    catch (const std::system_error&)
    {
        WriteError(std::cerr);
        exit(1);
    }
}

std::vector<Lexer::Lexeme> Vm::ProcessCompilingCodeAnalyzing()
{
    std::vector<Lexer::Lexeme> lexemesList = mCodeAnalyzer->ProcessLexicographicAnalyzing(mErrorManager.get());
    mCodeAnalyzer->ProcessCodeParsing(lexemesList, mErrorManager.get());
    return lexemesList;
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
        throw std::runtime_error("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::AssertIsNotTrue);
}

void Vm::ProcessPrint() const
{
    if (mStore.front()->getType() != eOperandType::Int8)
        throw std::runtime_error("Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::PrintError);
    unsigned char number = std::stoi(mStore.front()->toString());
    if (isprint(number))
        mStreamToOut << number << '\n';
}

void Vm::ProcessArithmetic(const std::string& aOperation)
{
	auto rightOperand = std::move(mStore.front());
	mStore.pop_front();
	auto leftOperand = std::move(mStore.front());
    mStore.pop_front();

    if (aOperation == "add")
        mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand + *rightOperand));
    else if (aOperation == "sub")
        mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand - *rightOperand));
    else if (aOperation == "mul")
        mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand * *rightOperand));
    else if (aOperation == "div")
    {
        if (leftOperand->toString() == "0.000000")
            throw std::runtime_error("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::DivisionZero);
        mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand / *rightOperand));
    }
    else if (aOperation == "mod")
    {
        if (leftOperand->toString() == "0")
            throw std::runtime_error("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::ModuloZero);
        mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand % *rightOperand));
    }
//	ProcessArithmeticImpl(&Operand<int>::operator/, leftOperand.get(), *rightOperand);
}

std::stringstream& Vm::GetOutput()
{
    return mStreamToOut;
}

std::ostream& Vm::WriteError(std::ostream& outErrorStream)
{
    outErrorStream << *mErrorManager;
    return outErrorStream;
}