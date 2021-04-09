#include "Parser.h"
#include "Error.h"
#include "utils.h"

#include <limits>

namespace Parser
{

void Parser::ParseLexemes(const std::vector<Lexer::Lexeme>& aLexemesList, ErrorManager* aErrorManager)
{
    bool isExitInstruction = false;
    try
    {
        for (const auto& lexeme : aLexemesList)
        {
            ++mLineCount;
            ProcessParsing(lexeme, isExitInstruction);
        }
        if (!isExitInstruction)
            throw ParserException("Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::NotExit);
    }
    catch (const ParserException& aError)
    {
        aErrorManager->AddError(aError.what());
    }
}

void Parser::ProcessParsing(const Lexer::Lexeme& aLexeme, bool& aIsExitInstruction)
{
    if (aLexeme.isComment)
        return;
    if (aLexeme.Instruction == "push")
        ++mStackSize;
    else if (aLexeme.Instruction == "pop" && !mStackSize)
        throw ParserException("Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::PopEmptyStack);
    else if (aLexeme.Instruction == "exit")
        aIsExitInstruction = true;

    if (auto commandIt = std::find(
                Lexer::CommandsWithValue.begin(),
                Lexer::CommandsWithValue.end(),
                aLexeme.Instruction);
            commandIt != Lexer::CommandsWithValue.end())
    {
        try
        {
            if (!CheckValueDiapason(aLexeme.Value, aLexeme.Type))
                throw ParserException("Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::WrongDiapason);
        }
        catch (const std::logic_error& aException)
        {
            const ParserException* isParserException = dynamic_cast<const ParserException*>(&aException);
            if (isParserException)
                throw *isParserException;
            throw ParserException("Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::WrongDiapason);
        }
    }
    else if (auto commandIt = std::find(
                ArithmeticCommands.begin(),
                ArithmeticCommands.end(),
                aLexeme.Instruction);
            commandIt != ArithmeticCommands.end())
    {
        if (mStackSize < 2)
            throw ParserException("Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::StackHasFewValues);
        --mStackSize;
    }
}

bool Parser::CheckValueDiapason(const std::string& aValue, eOperandType aType) const
{
    switch (aType)
    {

    case eOperandType::Int8:
    {
        auto number = ConvertNumberFromString<eOperandType::Int8>(aValue);
        if (number > std::numeric_limits<int8_t>::min() && number < std::numeric_limits<int8_t>::max())
            return true;
        return false;
    }
    case eOperandType::Int16:
    {
        auto number = ConvertNumberFromString<eOperandType::Int16>(aValue);
        if (number > std::numeric_limits<int16_t>::min() && number < std::numeric_limits<int16_t>::max())
            return true;
        return false;
    }
    case eOperandType::Int32:
    {
        auto number = ConvertNumberFromString<eOperandType::Int32>(aValue);
        if (number > std::numeric_limits<int32_t>::min() && number < std::numeric_limits<int32_t>::max())
            return true;
        return false;
    }
    case eOperandType::Float:
    {
        auto number = ConvertNumberFromString<eOperandType::Float>(aValue);
        if (IsLessOrEqualFirstFloating(std::numeric_limits<float>::lowest(), number)
        	&& IsLessOrEqualFirstFloating(number, std::numeric_limits<float>::max()))
            return true;
        return false;
    }
    case eOperandType::Double:
    {
        auto number = ConvertNumberFromString<eOperandType::Double>(aValue);
		if (IsLessOrEqualFirstFloating(std::numeric_limits<double>::lowest(), number)
			&& IsLessOrEqualFirstFloating(number, std::numeric_limits<double>::max()))
            return true;
        return false;
    }
    default:
        return false;

    }
}

ParserException::ParserException(std::string&& aError)
    : std::logic_error(aError)
{}

}