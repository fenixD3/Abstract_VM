#pragma once

#include "Lexer.h"

namespace Parser
{

class Parser
{
public:
    void ParseLexemes(const std::vector<Lexer::Lexeme>& aLexemesList, ErrorManager* aErrorManager);

private:
    size_t mLineCount = 0;
    size_t mStackSize = 0;

private:
    void ProcessParsing(const Lexer::Lexeme& aLexeme, bool& aIsExitInstruction);
    bool CheckValueDiapason(const std::string& aValue, eOperandType aType) const;

    template<eOperandType TEnumType>
    auto ConvertNumberFromString(const std::string& aValue) const
    {
        if constexpr (TEnumType == eOperandType::Float || TEnumType == eOperandType::Double)
            return std::stold(aValue);
        else
            return std::stoll(aValue);
    }

};

constexpr std::array<std::string_view, 12> ArithmeticCommands = {
    "add",
    "sub",
    "mul",
    "div",
    "mod",
    "max",
    "min",
    "avg",
    "pow",
    "xor",
    "or",
    "and"
};

class ParserException : public std::logic_error
{
public:
    ParserException() = default;
    ParserException(std::string&& aError);
    ~ParserException() = default;

    ParserException(const ParserException& aOther) = default;
    ParserException& operator=(const ParserException& aOther) = default;

};

}