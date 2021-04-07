#pragma once

#include <fstream>
#include <vector>
#include <optional>
#include <memory>
#include <unordered_set>
#include <array>
#include <utility>
#include <exception>

#include "IOperand.h"
#include "ErrorManager.h"

namespace Lexer
{

struct Lexeme
{
	std::string Instruction, Value;
	eOperandType Type;
	bool isComment = false;
};

struct LexerInfo
{
	std::vector<Lexeme> LexemesList;
};

class Lexer
{
public:
	Lexer(std::string aFileName);

	LexerInfo GetLexemes(ErrorManager* aErrorManager);

private:
	const std::string mFileName;
	std::ifstream mFileStream;
	size_t mLineCount = 0;

private:
	std::optional<Lexeme> Tokenize(std::string_view aCommand) const;
	std::string_view ReadToken(std::string_view& aCommand, char aDelimiter) const;
    std::pair<std::string_view, std::string_view> SplitTwo(
        std::string_view aCommand,
        char aDelimiter) const;
    eOperandType ConvertTypeToEnum(const std::string_view& aType) const;

};

constexpr std::array<std::string_view, 20> Commands = {
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit",
	"max",
	"min",
	"avg",
	"pow",
	"xor",
	"or",
	"and",
	"swap",
	"clear"
};

constexpr std::array<std::string_view, 2> CommandsWithValue = {
	"push", "assert"
};

class LexerException : public std::logic_error
{
public:
    LexerException() = default;
    LexerException(std::string&& aError);
    ~LexerException() = default;

    LexerException(const LexerException& aOther) = default;
    LexerException& operator=(const LexerException& aOther) = default;

};


}
