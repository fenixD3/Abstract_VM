#pragma once

#include "Operand.h"
#include "Error.h"
#include "CodeAnalyzer.h"
#include "ErrorManager.h"

#include <deque>
#include <memory>
#include <sstream>
#include <functional>
#include <type_traits>

class Vm
{
public:
	void Process(const std::vector<Lexer::Lexeme>& aLexemesList);
	const std::string& GetError() const;
    std::stringstream& GetOutput();

private:
	size_t mLineCount = 0;
	std::deque<std::unique_ptr<const IOperand>> mStore;
	mutable std::string mError;
	mutable std::stringstream mStreamToOut;

	std::unique_ptr<CodeAnalyzer> mCodeAnalyzer;
	std::unique_ptr<ErrorManager> mErrorManager;

private:
    void ProcessPush(eOperandType aType, const std::string& aValue);
    void ProcessPop();
    void ProcessDump() const;
    void ProcessAssert(eOperandType aType, const std::string& aValue) const;
    void ProcessPrint() const;
    void ProcessArithmetic(const std::string& aOperation);

    /*template <typename TCallable, typename TLeft, typename TRight>
    void ProcessArithmeticImpl(TCallable aOperation, TLeft aLeftOperand, TRight& aRightOperand);*/

};

/*template <typename TCallable, typename TLeft, typename TRight>
void Vm::ProcessArithmeticImpl(TCallable aOperation, TLeft aLeftOperand, TRight& aRightOperand)
{
//    mStore.push_front(std::unique_ptr<const IOperand>(*leftOperand / *rightOperand));
//	aLeftOperand->aOperation(aRightOperand);
	std::invoke(std::forward<TCallable>(aOperation), std::forward<TLeft>(aLeftOperand), aRightOperand);
//    const IOperand* newNumber = aOperation(*leftOperand, *rightOperand);
//    mStore.push_front(std::unique_ptr<const IOperand>(newNumber));
}*/
