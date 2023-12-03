#pragma once

#include <string>



struct Exception;
struct Token;

class TokenPosition;
class Type;


// riv's error codes



// 001 - 100: interpreter errors

Exception riv_e001(const std::string& path) noexcept;



// 101 - 150: scanner errors

Exception riv_e101(const TokenPosition& pos) noexcept; // invalid token
Exception riv_e102(const TokenPosition& pos) noexcept; // unterminated string
Exception riv_e103(const TokenPosition& pos) noexcept; // multi-line string not supported



// 151 - 200: parser errors

Exception riv_e151(const TokenPosition& pos) noexcept; // expression expected
Exception riv_e152(const TokenPosition& pos) noexcept; // expect ')' to close grouping expression



// 201 - 300: interpreter errors

Exception riv_e201(const std::initializer_list<Type>& operands, const Token& op) noexcept; // Operator "..." doesn't support operands of type: type1, type2, ...