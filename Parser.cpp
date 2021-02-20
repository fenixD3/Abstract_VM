#include "Parser.h"
#include "Error.h"

#include <limits>

namespace Parser
{

std::string_view Parser::GetError() const
{
    return mError;
}

void Parser::ParseLexemes(const std::vector<Lexer::Lexeme>& aLexemesList)
{
    bool isExitInstruction = false;
    for (const auto& lexeme : aLexemesList)
    {
        ++mLineCount;
        if (lexeme.isComment)
            continue;
		if (lexeme.Instruction == "push")
			++mStackSize;
		else if (lexeme.Instruction == "pop" && !mStackSize)
		{
			mError += "Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::PopEmptyStack;
			continue;
		}
		else if (lexeme.Instruction == "exit")
			isExitInstruction = true;

        if (auto commandIt = std::find(
                    Lexer::CommandsWithValue.begin(),
                    Lexer::CommandsWithValue.end(),
                    lexeme.Instruction);
                commandIt == Lexer::CommandsWithValue.end())
            continue;
        if (!CheckValueDiapason(lexeme.Value, lexeme.Type))
		{
			mError += "Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::WrongDiapason;
			continue;
		}
        if (auto commandIt = std::find(
                    ArithmeticCommands.begin(),
                    ArithmeticCommands.end(),
                    lexeme.Instruction);
            commandIt != ArithmeticCommands.end())
        {
            if (mStackSize < 2)
            {
                mError += "Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::StackHasFewValues;
                continue;
            }
            --mStackSize;
        }
    }
    if (!isExitInstruction)
        mError += "Line " + std::to_string(mLineCount) + ": Critical Error : " + Error::NotExit;
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
    }
    case eOperandType::Int16:
    {
        auto number = ConvertNumberFromString<eOperandType::Int16>(aValue);
        if (number > std::numeric_limits<int16_t>::min() && number < std::numeric_limits<int16_t>::max())
            return true;
    }
    case eOperandType::Int32:
    {
        auto number = ConvertNumberFromString<eOperandType::Int32>(aValue);
        if (number > std::numeric_limits<int32_t>::min() && number < std::numeric_limits<int32_t>::max())
            return true;
    }
    case eOperandType::Float:
    {
        auto number = ConvertNumberFromString<eOperandType::Float>(aValue);
        if (number > std::numeric_limits<float>::lowest() && number < std::numeric_limits<float>::max())
            return true;
    }
    case eOperandType::Double:
    {
        auto number = ConvertNumberFromString<eOperandType::Double>(aValue);
        if (number > std::numeric_limits<double>::lowest() && number < std::numeric_limits<double>::max())
            return true;
    }
    default:
        return false;

    }
}

}