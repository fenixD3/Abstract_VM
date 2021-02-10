#pragma once

#include "Operand.h"
#include "Lexer.h"
#include "Error.h"

#include <deque>
#include <memory>
#include <sstream>
#include <functional>
#include <type_traits>

class Vm
{
public:
	void Process(const std::vector<Lexer::Lexeme>& aLexemesList);

private:
	size_t mLineCount = 0;
	std::deque<std::unique_ptr<const IOperand>> mStore;
	mutable std::string mError;
	mutable std::stringstream mStreamToOut;

private:
    void ProcessPush(eOperandType aType, const std::string& aValue);
    void ProcessPop();
    void ProcessDump() const;
    void ProcessAssert(eOperandType aType, const std::string& aValue) const;
    void ProcessPrint() const;
    void ProcessExit() const;

    template <typename TCallable, typename ... TArgs>
    void ProcessArithmetic(TCallable aOperation, const TArgs ... aArgs);

};

template <typename TCallable, typename ... TArgs>
void Vm::ProcessArithmetic(TCallable aOperation, const TArgs ... aArgs)
{
    auto rightOperand = std::move(mStore.front());
    mStore.pop_front();
    auto leftOperand = std::move(mStore.front());
    if (leftOperand->toString() == "0")
        mError += "Line " + std::to_string(mLineCount) + ": Runtime Error :" + Error::DivisionZero;
    mStore.pop_front();
//    mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand / *rightOperand));
    decltype(auto) operand = std::invoke(aOperation, aArgs..., *leftOperand);
//    const IOperand* newNumber = aOperation(*leftOperand, *rightOperand);
//    mStore.push_front(std::unique_ptr<const IOperand>(newNumber));
}
