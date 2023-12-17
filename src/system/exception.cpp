#include <system/exception.h>

#include <sstream>

#include <specter/output/color/color.h>
#include <specter/output/ostream.h>

#include <common/string.h>
#include <system/sysstate.h>



std::string generate_error_indicator(const std::string& line, const TokenPosition& pos)
{
	std::string error_indicator;

	// generates it
	for (size_t i = 0; i < line.size() && i < pos.end; i++)
	{
		// before the beginning of the token
		if (i < pos.begin)
			error_indicator += line[i] == '\t' ? '\t' : ' ';

		// at the beginning of the token
		else if (i == pos.begin)
			error_indicator += '^';

		// after the beginning of the token
		else if (i > pos.begin)
			error_indicator += '~';
	}

	return sp::bred(error_indicator);
}


std::string format_token_position(const TokenPosition& pos) noexcept
{
	std::stringstream stream;

	stream << "line " << pos.line + 1 << ", ";
	stream << "col " << pos.begin << ":" << pos.end;

	return stream.str();
}


std::string get_error_line(std::string& line, const TokenPosition& pos) noexcept
{
	std::stringstream stream;

	// paints the error token with red
	line.insert(pos.end, sp::RESET_ALL);
	line.insert(pos.begin, sp::clr(sp::fg_bred));

	stream << line << std::endl;
	stream << generate_error_indicator(line, pos);

	return stream.str();
}


unsigned int count_decimal_floors(const unsigned int number) noexcept
{
	unsigned int buff = 1;

	for (size_t i = 1;; i++)
	{
		buff *= 10;

		if (buff > number)
			return i;
	}
}


std::string format_code(const char ch, const unsigned int code) noexcept
{
	std::stringstream stream;

	std::string zero_count = "000";
	
	// erase the right number of zeros
	for (size_t i = 0; i < count_decimal_floors(code); i++)
		zero_count.erase(zero_count.begin());

	stream << ch << zero_count << std::to_string(code);

	return stream.str();
}



std::string exception_to_string(const Exception& exception) noexcept
{
	const SystemState& state = sys_state();

	// error position (generally a token)
	const TokenPosition& pos = exception.pos;
	const bool pos_valid = pos.valid();

	// line where the error occurred
	std::string line;
	
	// only initialize when the position is valid
	if (pos_valid)
		line = state.vecsource[pos.line];
	
	std::stringstream stream;

	const std::string code = format_code('E', exception.code);

	// source where the error occurred
	stream << std::endl << sp::clr(surround(code, "(", ")"), sp::fg_bred, sp::underline) << " " << sp::bred("Error ") << state.source_name;
	
	if (!state.source_name.empty() && pos_valid)
		stream << " ";

	// error position
	if (pos_valid)
		stream << sp::clr(sp::bold) << "(" << format_token_position(pos) << ")" << sp::RESET_ALL;

	stream << ": ";

	// error message
	stream << exception.msg;

	// error view
	if (pos.valid())
		stream << std::endl << std::endl << get_error_line(line, pos) << std::endl << std::endl;

	return stream.str();
}




void log_error(const Exception& exception) noexcept
{
	sp::println(exception_to_string(exception));
	set_error_flag();
}