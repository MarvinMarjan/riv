#pragma once

#include <string>



struct Exception;
struct Token;

class TokenPosition;
class Type;


// riv's error codes



// 001 - 099: interpreter errors

Exception riv_e001(const std::string& path) noexcept; // invalid source file



// 100 - 199: scanner errors

Exception riv_e100(const TokenPosition& pos) noexcept; // invalid token
Exception riv_e101(const TokenPosition& pos) noexcept; // unterminated string
Exception riv_e102(const TokenPosition& pos) noexcept; // multi-line string not supported



// 200 - 299: parser errors

Exception riv_e200(const TokenPosition& pos) noexcept; // expression expected
Exception riv_e201(const TokenPosition& pos) noexcept; // expect ")" to close grouping expression
Exception riv_e202(const TokenPosition& pos) noexcept; // expect ";" after statement
Exception riv_e203(const TokenPosition& pos) noexcept; // expect variable name after "var" keyword
Exception riv_e204(const TokenPosition& pos) noexcept; // only variables can be assigned.
Exception riv_e205(const TokenPosition& pos) noexcept; // expect "}" to close block statement
Exception riv_e206(const TokenPosition& pos) noexcept; // expect "(" after "if" statement
Exception riv_e207(const TokenPosition& pos) noexcept; // expect ")" after "if" condition
Exception riv_e208(const TokenPosition& pos) noexcept; // expect "(" after "while" statement
Exception riv_e209(const TokenPosition& pos) noexcept; // expect ")" after "while" condition
Exception riv_e210(const TokenPosition& pos) noexcept; // expect "(" after "for" statement
Exception riv_e211(const TokenPosition& pos) noexcept; // expect ";" after "for" condition
Exception riv_e212(const TokenPosition& pos) noexcept; // expect ")" after "for" increment




// 300 - 399: runtime errors

Exception riv_e300(const std::initializer_list<Type>& operands, const Token& op) noexcept; // Operator "..." doesn't support operands of type: type1, type2, ...
Exception riv_e301(const Token& identifier) noexcept; // undefined indentifier "..."