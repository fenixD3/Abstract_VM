#include "Vm.h"
#include "utils.h"

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
                    break;
                else if (lexeme.Instruction == "swap")
                    ProcessSwap();
                else if (lexeme.Instruction == "clear")
                    ProcessClear();
                else
                    ProcessArithmetic(lexeme.Instruction);
            }
            catch (const VmException& aError)
            {
                mErrorManager->AddError(aError.what());
				throw ErrorManagerException("");
            }
        }
        if (!mErrorManager->IsEmptyError())
            throw ErrorManagerException("");
    }
    catch (const ErrorManagerException&)
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
	if (mStore.empty())
		std::cout << std::string("\e[93m") << "Warning: Dump on empty stack" << std::string("\e[39m") << '\n';
    for (const auto& value : mStore)
        mStreamToOut << value->toString() << '\n';
}

void Vm::ProcessAssert(eOperandType aType, const std::string& aValue) const
{
    if (aType != mStore.front()->getType()
    	|| (aType < eOperandType::Float && std::stoi(aValue) == 0)
		|| (aType == eOperandType::Float && !IsEqualTwoFloating(std::stof(aValue), std::stof(mStore.front()->toString()), MaxULPS))
		|| ((aType == eOperandType::Double && !IsEqualTwoFloating(std::stod(aValue), std::stod(mStore.front()->toString()), MaxULPS))))
		throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::AssertIsNotTrue);
}

void Vm::ProcessPrint() const
{
    if (mStore.front()->getType() != eOperandType::Int8)
        throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::PrintError);
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
		if (CheckDivisionByZero(rightOperand.get()))
            throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::DivisionZero);
        mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand / *rightOperand));
    }
    else if (aOperation == "mod")
    {
    	if (CheckDivisionByZero(rightOperand.get()))
            throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::ModuloZero);
        auto result = std::unique_ptr<const IOperand>(*leftOperand % *rightOperand);
        if (!result)
            throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::InvalidOperandsForModulo);
        mStore.push_front(std::move(result));
    }
    else if (aOperation == "max")
        mStore.push_front(std::unique_ptr<const IOperand>(leftOperand->max(*rightOperand)));
    else if (aOperation == "min")
        mStore.push_front(std::unique_ptr<const IOperand>(leftOperand->min(*rightOperand)));
    else if (aOperation == "avg")
        mStore.push_front(std::unique_ptr<const IOperand>(leftOperand->avg(*rightOperand)));
    else if (aOperation == "pow")
    {
        auto result = std::unique_ptr<const IOperand>(leftOperand->pow(*rightOperand));
        if (!result)
            throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::PowError);
        mStore.push_front(std::move(result));
    }
    else if (aOperation == "xor")
    {
        auto result = std::unique_ptr<const IOperand>(*leftOperand ^ *rightOperand);
        if (!result)
            throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::InvalidOperandsForXor);
        mStore.push_front(std::move(result));
    }
    else if (aOperation == "or")
    {
        auto result = std::unique_ptr<const IOperand>(*leftOperand | *rightOperand);
        if (!result)
            throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::InvalidOperandsForOr);
        mStore.push_front(std::move(result));
    }
    else if (aOperation == "and")
    {
        auto result = std::unique_ptr<const IOperand>(*leftOperand & *rightOperand);
        if (!result)
            throw VmException("Line " + std::to_string(mLineCount) + ": Runtime Error : " + Error::InvalidOperandsForAnd);
        mStore.push_front(std::move(result));
    }
}

void Vm::ProcessSwap()
{
    auto upValue = std::move(mStore.front());
    mStore.pop_front();
    auto downValue = std::move(mStore.front());
    mStore.pop_front();

    mStore.push_front(std::move(upValue));
    mStore.push_front(std::move(downValue));
}

void Vm::ProcessClear()
{
    mStore.clear();
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

bool Vm::CheckDivisionByZero(const IOperand* aOperand) const
{
	if ((aOperand->getType() < eOperandType::Float && std::stoi(aOperand->toString()) == 0)
		|| (aOperand->getType() == eOperandType::Float && IsEqualTwoFloating(std::stof(aOperand->toString()), 0.0f, MaxULPS))
		|| ((aOperand->getType() == eOperandType::Double && IsEqualTwoFloating(std::stod(aOperand->toString()), 0.0, MaxULPS))))
		return true;
	return false;
}

VmException::VmException(std::string&& aError)
    : std::runtime_error(aError)
{}
