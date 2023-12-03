#include <language/error_codes.h>

#include <sstream>

#include <common/string.h>
#include <system/exception.h>



Exception riv_e001(const std::string& path) noexcept {
	return Exception("Invalid source file: " + qt(path), {}, 1);
}





Exception riv_e101(const TokenPosition& pos) noexcept {
	return Exception("Invalid token.", pos, 101);
}

Exception riv_e102(const TokenPosition& pos) noexcept {
	return Exception("Unterminated string.", pos, 102);
}

Exception riv_e103(const TokenPosition& pos) noexcept {
	return Exception("Multi-line string not supported.", pos, 103);
}





Exception riv_e151(const TokenPosition& pos) noexcept {
	return Exception("Expression expected.", pos, 151);
}

Exception riv_e152(const TokenPosition& pos) noexcept {
	return Exception("Expect \")\" to close grouping expression.", pos, 152);
}

Exception riv_e153(const TokenPosition& pos) noexcept {
	return Exception("Expect \";\" after statement.", pos, 153);
}





Exception riv_e201(const std::initializer_list<Type>& operands, const Token& op) noexcept
{
	std::stringstream operands_str;

	for (size_t i = 0; i < operands.size(); i++)
	{
		const Type* const operand = operands.begin() + i;
		operands_str << type_index_to_string(operand->type()) << (operand + 1 == operands.end() ? "" : ", ");
	}

	return Exception("Operator \"" + op.lexeme + "\" doesn't support operands of type: " + operands_str.str(), op.pos, 201);
}