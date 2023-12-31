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
Exception riv_e203(const TokenPosition& pos) noexcept; // expect variable name after "var" statement
Exception riv_e204(const TokenPosition& pos) noexcept; // expect "}" to close block statement
Exception riv_e205(const TokenPosition& pos) noexcept; // expect "(" after "if" statement
Exception riv_e206(const TokenPosition& pos) noexcept; // expect ")" after "if" condition
Exception riv_e207(const TokenPosition& pos) noexcept; // expect "(" after "while" statement
Exception riv_e208(const TokenPosition& pos) noexcept; // expect ")" after "while" condition
Exception riv_e209(const TokenPosition& pos) noexcept; // expect "(" after "for" statement
Exception riv_e210(const TokenPosition& pos) noexcept; // expect ";" after "for" condition
Exception riv_e211(const TokenPosition& pos) noexcept; // expect ")" after "for" increment
Exception riv_e212(const TokenPosition& pos) noexcept; // cannot use "break" statement outside a loop
Exception riv_e213(const TokenPosition& pos) noexcept; // cannot use "continue" statement outside a loop
Exception riv_e214(const TokenPosition& pos) noexcept; // expect function name after "function" statement
Exception riv_e215(const TokenPosition& pos) noexcept; // expect "(" after function name
Exception riv_e216(const TokenPosition& pos) noexcept; // expect ")" after function parameter list
Exception riv_e217(const TokenPosition& pos) noexcept; // expect parameter after ","
Exception riv_e218(const TokenPosition& pos) noexcept; // expect function body
Exception riv_e219(const TokenPosition& pos) noexcept; // expect ")" after function arguments
Exception riv_e220(const TokenPosition& pos) noexcept; // cannot use "return" statement outside a function
Exception riv_e221(const TokenPosition& pos, const std::string& after) noexcept; // expect symbol to import after ...
Exception riv_e222(const TokenPosition& pos) noexcept; // expect declaration statement
Exception riv_e223(const TokenPosition& pos) noexcept; // expect package name
Exception riv_e224(const TokenPosition& pos) noexcept; // expect package body
Exception riv_e225(const TokenPosition& pos) noexcept; // expect package member identifier
Exception riv_e226(const TokenPosition& pos) noexcept; // expect "else" after left expression of ternary expression
Exception riv_e227(const TokenPosition& pos) noexcept; // expect "]" to close array
Exception riv_e228(const TokenPosition& pos) noexcept; // expect "]" to close indexing
Exception riv_e229(const TokenPosition& pos) noexcept; // expect call expression after ":"




// 300 - 399: runtime errors

Exception riv_e300(const std::initializer_list<Type>& operands, const Token& op) noexcept; // Operator "..." doesn't support operands of type: type1, type2, ...
Exception riv_e301(const TokenPosition& pos) noexcept; // undefined identifier
Exception riv_e302(const TokenPosition& pos) noexcept; // only functions can be called
Exception riv_e303(int expect, int got, const TokenPosition& pos) noexcept; // expect ... arguments, got ...
Exception riv_e304(const TokenPosition& pos) noexcept; // invalid import symbol
Exception riv_e305(const std::string& identifier, const TokenPosition& pos, const TokenPosition& already_declared, const std::string& file_path = "") noexcept; // identifier ... already declared at ...
Exception riv_e306() noexcept; // function "main" not declared
Exception riv_e307(const TokenPosition& pos) noexcept; // expect package at left of "::"
Exception riv_e308(const TokenPosition& pos, const std::string& type_name) noexcept; // invalid non-assignable type "..."
Exception riv_e309(const TokenPosition& pos) noexcept; // only variables can be assigned
Exception riv_e310(const TokenPosition& pos) noexcept; // cannot modify the value of an immutable variable
Exception riv_e311(const TokenPosition& pos, size_t limit) noexcept; // recursion limit of ... exceeded
Exception riv_e312(const TokenPosition& pos) noexcept; // only arrays can be indexed
Exception riv_e313(const TokenPosition& pos) noexcept; // expect number as array index
Exception riv_e314(const TokenPosition& pos) noexcept; // index out of range