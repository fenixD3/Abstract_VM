#include "Lexer.h"
#include "Error.h"

#include <algorithm>
#include <tuple>

namespace Lexer
{

Lexer::Lexer(std::string aFileName)
        : mFileName(std::move(aFileName))
{
    mFileStream = std::ifstream(mFileName);
}

LexerInfo Lexer::Lexer::GetLexemes()
{
    LexerInfo resultInfo;
    for (std::string line; std::getline(mFileStream, line);)
    {
        ++mLineCount;
        if (line.empty())
            continue;
        auto lexeme = Tokenize(line, resultInfo.Error);
        if (lexeme.has_value())
            resultInfo.LexemesList.push_back(std::move(lexeme.value()));
    }
    return resultInfo;
}

std::optional<Lexeme> Lexer::Tokenize(std::string_view aCommand, std::string& outError) const
{
    Lexeme lexeme;
    auto instruction = ReadToken(aCommand, ' ');
    if (instruction.empty())
    {
        lexeme.isComment = true;
        return lexeme;
    }

    if (auto commandIt = std::find(Commands.begin(), Commands.end(), instruction);
            commandIt == Commands.end())
    {
        outError += "Line " + std::to_string(mLineCount) + ": Lexical Error : " + Error::UnknownCommand;
        return std::nullopt;
    }
    lexeme.Instruction = std::string(instruction);

    if (auto commandIt = std::find(CommandsWithValue.begin(), CommandsWithValue.end(), instruction);
            commandIt != CommandsWithValue.end())
    {
        auto type = ReadToken(aCommand, '(');
        if (type.empty())
        {
            outError += "Line " + std::to_string(mLineCount) + ": Lexical Error : " + Error::WrongCommandOrder;
            return std::nullopt;
        }
        auto operandType = ConvertTypeToEnum(type);
        if (operandType == eOperandType::Unknown)
        {
            outError = "Line " + std::to_string(mLineCount) + ": Lexical Error : " + Error::UnknownType;
            return std::nullopt;
        }
        lexeme.Type = operandType;

        auto value = ReadToken(aCommand, ')');
        if (value.empty())
        {
            outError += "Line " + std::to_string(mLineCount) + ": Lexical Error : " + Error::WrongCommandOrder;
            return std::nullopt;
        }
        lexeme.Value = std::string(value);
    }
    return lexeme;
}

std::string_view Lexer::ReadToken(std::string_view& aCommand, char aDelimiter) const
{
    auto[token, secondPartCommand] = SplitTwo(aCommand, aDelimiter);
    aCommand = secondPartCommand;
    if (token == ";" || token == ";;")
        return "";
    return token;
}

std::pair<std::string_view, std::string_view> Lexer::SplitTwo(
        std::string_view aCommand,
        char aDelimiter) const
{
    auto[lhs, rhs] = SplitTwoStrict(aCommand, aDelimiter);
    return {lhs, rhs.value_or("")};
}

std::pair<std::string_view, std::optional<std::string_view>>
Lexer::SplitTwoStrict(std::string_view aCommand, char aDelimiter) const
{
    size_t position = aCommand.find(aDelimiter);
    if (position == std::string::npos)
        return {aCommand.substr(0, position), std::nullopt};
    return {aCommand.substr(0, position), aCommand.substr(position + 1)};
}

eOperandType Lexer::ConvertTypeToEnum(const std::string_view& aType) const
{
    if (aType == "int8")
        return eOperandType::Int8;
    if (aType == "int16")
        return eOperandType::Int16;
    if (aType == "int32")
        return eOperandType::Int32;
    if (aType == "float")
        return eOperandType::Float;
    if (aType == "double")
        return eOperandType::Double;
    return eOperandType::Unknown;
}

}
