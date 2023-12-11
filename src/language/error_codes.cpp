#include <language/error_codes.h>

#include <sstream>

#include <common/string.h>
#include <system/exception.h>



Exception riv_e001(const std::string& path) noexcept {
	return Exception("Invalid source file: " + qt(path), {}, 1);
}





Exception riv_e100(const TokenPosition& pos) noexcept {
	return Exception("Invalid token.", pos, 100);
}

Exception riv_e101(const TokenPosition& pos) noexcept {
	return Exception("Unterminated string.", pos, 101);
}

Exception riv_e102(const TokenPosition& pos) noexcept {
	return Exception("Multi-line string not supported.", pos, 102);
}





Exception riv_e200(const TokenPosition& pos) noexcept {
	return Exception("Expression expected.", pos, 200);
}

Exception riv_e201(const TokenPosition& pos) noexcept {
	return Exception("Expect \")\" to close grouping expression.", pos, 201);
}

Exception riv_e202(const TokenPosition& pos) noexcept {
	return Exception("Expect \";\" after statement.", pos, 202);
}

Exception riv_e203(const TokenPosition& pos) noexcept {
	return Exception("Expect variable name after \"var\" statement.", pos, 203);
}

Exception riv_e204(const TokenPosition& pos) noexcept {
	return Exception("Only variables can be assigned.", pos, 204);
}

Exception riv_e205(const TokenPosition& pos) noexcept {
	return Exception("Expect \"}\" to close block statement.", pos, 205);
}

Exception riv_e206(const TokenPosition& pos) noexcept {
	return Exception("Expect \"(\" after \"if\" statement.", pos, 206);
}

Exception riv_e207(const TokenPosition& pos) noexcept {
	return Exception("Expect \")\" after \"if\" condition.", pos, 207);
}

Exception riv_e208(const TokenPosition& pos) noexcept {
	return Exception("Expect \"(\" after \"while\" statement.", pos, 208);
}

Exception riv_e209(const TokenPosition& pos) noexcept {
	return Exception("Expect \")\" after \"while\" condition.", pos, 209);
}

Exception riv_e210(const TokenPosition& pos) noexcept {
	return Exception("Expect \"(\" after \"for\" statement.", pos, 210);
}

Exception riv_e211(const TokenPosition& pos) noexcept {
	return Exception("Expect \";\" after \"for\" condition.", pos, 211);
}

Exception riv_e212(const TokenPosition& pos) noexcept {
	return Exception("Expect \")\" after \"for\" increment.", pos, 212);
}

Exception riv_e213(const TokenPosition& pos) noexcept {
	return Exception("Cannot use \"break\" statement outside a loop.", pos, 213);
}

Exception riv_e214(const TokenPosition& pos) noexcept {
	return Exception("Cannot use \"continue\" statement outside a loop.", pos, 214);
}

Exception riv_e215(const TokenPosition& pos) noexcept {
	return Exception("Expect function name after \"function\" statement.", pos, 215);
}

Exception riv_e216(const TokenPosition& pos) noexcept {
	return Exception("Expect \"(\" after function name.", pos, 216);
}

Exception riv_e217(const TokenPosition& pos) noexcept {
	return Exception("Expect \")\" after parameter list.", pos, 217);
}

Exception riv_e218(const TokenPosition& pos) noexcept {
	return Exception("Expect parameter after \",\".", pos, 218);
}

Exception riv_e219(const TokenPosition& pos) noexcept {
	return Exception("Expect function body.", pos, 219);
}

Exception riv_e220(const TokenPosition& pos) noexcept {
	return Exception("Expect \")\" after function arguments.", pos, 220);
}

Exception riv_e221(const TokenPosition& pos) noexcept {
	return Exception("Cannot use \"return\" statement outside a function.", pos, 221);
}

Exception riv_e222(const TokenPosition& pos) noexcept {
	return Exception("Expect module path string after \"import\" statement.", pos, 222);
}

Exception riv_e223(const TokenPosition& pos) noexcept {
	return Exception("Expect identifier to export after \",\".", pos, 223);
}

Exception riv_e224(const TokenPosition& pos) noexcept {
	return Exception("Unexpected token after \"export\" statement.", pos, 224);
}








Exception riv_e300(const std::initializer_list<Type>& operands, const Token& op) noexcept
{
	std::stringstream operands_str;

	for (size_t i = 0; i < operands.size(); i++)
	{
		const Type* const operand = operands.begin() + i;
		operands_str << type_index_to_string(operand->type()) << (operand + 1 == operands.end() ? "" : ", ");
	}

	return Exception("Operator \"" + op.lexeme + "\" doesn't support operands of type: " + operands_str.str(), op.pos, 300);
}

Exception riv_e301(const Token& identifier) noexcept {
	return Exception("Undefined identifier \"" + identifier.lexeme + "\".", identifier.pos, 301);
}

Exception riv_e302(const TokenPosition& pos) noexcept {
	return Exception("Only functions can be called.", pos, 302);
}

Exception riv_e303(const int expect, const int got, const TokenPosition& pos) noexcept {
	return Exception("Expect " + std::to_string(expect) + " arguments, got " + std::to_string(got) + ".", pos, 303);
}

Exception riv_e304(const TokenPosition& pos) noexcept {
	return Exception("Invalid module path.", pos, 304);
}