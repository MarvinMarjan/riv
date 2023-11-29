#include <expression/printer.h>

#include <sstream>

#include <specter/output/ostream.h>


Type ExprPrinter::parenthesize(const std::initializer_list<Expression* const>& exprs, const std::string& op) noexcept
{
	std::stringstream stream;

	stream << op << " (";


	// iterate each expression
	for (size_t i = 0; i < exprs.size(); i++)
	{
		Expression* const* current = exprs.begin() + i;

		stream << (*current)->process(*this).to_string() << (current + 1 == exprs.end() ? "" : ", ");
	}


	stream << ')';

	return stream.str();
}