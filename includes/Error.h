#pragma once

namespace Error
{

constexpr char UnknownCommand[] = "Unknown command\n";
constexpr char UnknownType[] = "Unknown type\n";
constexpr char WrongDiapason[] = "Wrong value diapason\n";
constexpr char PopEmptyStack[] = "Pop on empty stack\n";
constexpr char DivisionZero[] = "Division by zero\n";
constexpr char ModuloZero[] = "Modulo by zero\n";
constexpr char NotExit[] = "Do not exit command\n";
constexpr char AssertIsNotTrue[] = "Assert is not true\n";
constexpr char PrintError[] = "Top value is not Int8\n";
constexpr char StackHasFewValues[] = "Stack does not have two values\n";
constexpr char PrintStackError[] = "Stack does not have any values for printing\n";

constexpr char WrongCommandOrder[] = "Wrong command order\n";
constexpr char InvalidOperandsForModulo[] = "Invalid operands types for binary operator%";

}
