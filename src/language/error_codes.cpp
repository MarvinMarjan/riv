#include <language/error_codes.h>

#include <sstream>

#include <common/string.h>
#include <system/exception.h>



extern std::string format_token_position(const TokenPosition& pos) noexcept;



Exception riv_e001(const std::string& path) noexcept {
	return { "Invalid source file: " + qt(path), {}, 1 };
}





Exception riv_e100(const TokenPosition& pos) noexcept {
	return { "Invalid token.", pos, 100 };
}

Exception riv_e101(const TokenPosition& pos) noexcept {
	return { "Unterminated string.", pos, 101 };
}

Exception riv_e102(const TokenPosition& pos) noexcept {
	return { "Multi-line string not supported.", pos, 102 };
}





Exception riv_e200(const TokenPosition& pos) noexcept {
	return { "Expression expected.", pos, 200 };
}

Exception riv_e201(const TokenPosition& pos) noexcept {
	return { "Expect \")\" to close grouping expression.", pos, 201 };
}

Exception riv_e202(const TokenPosition& pos) noexcept {
	return { "Expect \";\" after statement.", pos, 202 };
}

Exception riv_e203(const TokenPosition& pos) noexcept {
	return { "Expect variable name after \"var\" statement.", pos, 203 };
}

Exception riv_e204(const TokenPosition& pos) noexcept {
	return { "Expect \"}\" to close block statement.", pos, 204 };
}

Exception riv_e205(const TokenPosition& pos) noexcept {
	return { R"(Expect "(" after "if" statement.)", pos, 205 };
}

Exception riv_e206(const TokenPosition& pos) noexcept {
	return { "Expect \")\" after \"if\" condition.", pos, 206 };
}

Exception riv_e207(const TokenPosition& pos) noexcept {
	return { R"(Expect "(" after "while" statement.)", pos, 207 };
}

Exception riv_e208(const TokenPosition& pos) noexcept {
	return { "Expect \")\" after \"while\" condition.", pos, 208 };
}

Exception riv_e209(const TokenPosition& pos) noexcept {
	return { R"(Expect "(" after "for" statement.)", pos, 209 };
}

Exception riv_e210(const TokenPosition& pos) noexcept {
	return { R"(Expect ";" after "for" condition.)", pos, 210 };
}

Exception riv_e211(const TokenPosition& pos) noexcept {
	return { "Expect \")\" after \"for\" increment.", pos, 211 };
}

Exception riv_e212(const TokenPosition& pos) noexcept {
	return { "Cannot use \"break\" statement outside a loop.", pos, 212 };
}

Exception riv_e213(const TokenPosition& pos) noexcept {
	return { "Cannot use \"continue\" statement outside a loop.", pos, 213 };
}

Exception riv_e214(const TokenPosition& pos) noexcept {
	return { "Expect function name after \"function\" statement.", pos, 214 };
}

Exception riv_e215(const TokenPosition& pos) noexcept {
	return { "Expect \"(\" after function name.", pos, 215 };
}

Exception riv_e216(const TokenPosition& pos) noexcept {
	return { "Expect \")\" after parameter list.", pos, 216 };
}

Exception riv_e217(const TokenPosition& pos) noexcept {
	return { "Expect parameter after \",\".", pos, 217 };
}

Exception riv_e218(const TokenPosition& pos) noexcept {
	return { "Expect function body.", pos, 218 };
}

Exception riv_e219(const TokenPosition& pos) noexcept {
	return { "Expect \")\" after function arguments.", pos, 219 };
}

Exception riv_e220(const TokenPosition& pos) noexcept {
	return { "Cannot use \"return\" statement outside a function.", pos, 220 };
}

Exception riv_e221(const TokenPosition& pos, const std::string& after) noexcept {
	return { "Expect symbols to import after " + after + ".", pos, 221 };
}

Exception riv_e222(const TokenPosition& pos) noexcept {
	return { "Expect declaration statement.", pos, 222 };
}

Exception riv_e223(const TokenPosition& pos) noexcept {
	return { "Expect package name.", pos, 223 };
}

Exception riv_e224(const TokenPosition& pos) noexcept {
	return { "Expect package body.", pos, 224 };
}

Exception riv_e225(const TokenPosition& pos) noexcept {
	return { "Expect package member identifier.", pos, 225 };
}

Exception riv_e226(const TokenPosition& pos) noexcept {
	return { "Expect \"else\" after left expression of ternary expression.", pos, 226 };
}

Exception riv_e227(const TokenPosition& pos) noexcept {
	return { "Expect \"]\" to close array.", pos, 227 };
}

Exception riv_e228(const TokenPosition& pos) noexcept {
	return { "Expect \"]\" to close indexing.", pos, 228 };
}

Exception riv_e229(const TokenPosition& pos) noexcept {
	return { "Expect call expression after \":\".", pos, 229 };
}







Exception riv_e300(const std::initializer_list<Type>& operands, const Token& op) noexcept
{
	std::stringstream operands_str;

	for (size_t i = 0; i < operands.size(); i++)
	{
		const Type* const operand = operands.begin() + i;
		operands_str << type_index_to_string(operand->type()) << (operand + 1 == operands.end() ? "" : ", ");
	}

	return { "Operator \"" + op.lexeme + "\" doesn't support operands of type: " + operands_str.str(), op.pos, 300 };
}

Exception riv_e301(const TokenPosition& pos) noexcept {
	return { "Undefined identifier.", pos, 301 };
}

Exception riv_e302(const TokenPosition& pos) noexcept {
	return { "Only functions can be called.", pos, 302 };
}

Exception riv_e303(const int expect, const int got, const TokenPosition& pos) noexcept {
	return { "Expect " + std::to_string(expect) + " arguments, got " + std::to_string(got) + ".", pos, 303 };
}

Exception riv_e304(const TokenPosition& pos) noexcept {
	return { "Invalid import symbol.", pos, 304 };
}

Exception riv_e305(const std::string& identifier, const TokenPosition& pos, const TokenPosition& already_declared, const std::string& file_path) noexcept
{
	const std::string already_declared_location = qt(file_path) + surround(format_token_position(already_declared), " (", ")");
	const std::string message = "Identifier " + qt(identifier) + " already declared at " + already_declared_location + ".";

	return { message, pos, 305 };
}

Exception riv_e306() noexcept {
	return { "Function \"main\" not declared.", {}, 306 };
}

Exception riv_e307(const TokenPosition& pos) noexcept {
	return { "Expect package at left of \"::\".", pos, 307 };
}

Exception riv_e308(const TokenPosition& pos, const std::string& type_name) noexcept {
	return { "Invalid non-assignable type " + qt(type_name) + ".", pos, 308 };
}

Exception riv_e309(const TokenPosition& pos) noexcept {
	return { "Only variables can be assigned.", pos, 309 };
}

Exception riv_e310(const TokenPosition& pos) noexcept {
	return { "Cannot modify the value of an immutable variable.", pos, 310 };
}

Exception riv_e311(const TokenPosition& pos, const size_t limit) noexcept {
	return { "Recursion limit of " + std::to_string(limit) + " exceeded.", pos, 311 };
}

Exception riv_e312(const TokenPosition& pos) noexcept {
	return { "Only arrays or strings can be indexed.", pos, 312 };
}

Exception riv_e313(const TokenPosition& pos) noexcept {
	return { "Expect number as index.", pos, 313 };
}

Exception riv_e314(const TokenPosition& pos) noexcept {
	return { "Index out of range.", pos, 314 };
}