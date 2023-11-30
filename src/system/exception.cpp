#include <system/exception.h>

#include <sstream>

#include <specter/output/color/color.h>

#include <system/sysstate.h>



static std::string generate_error_indicator(const std::string& line, const TokenPosition& pos)
{
	std::string error_indicator = "";

	// generates it
	for (size_t i = 0; i < line.size() && i < pos.end; i++)
	{
		// before the begin of the token
		if (i < pos.begin)
			error_indicator += line[i] == '\t' ? '\t' : ' ';

		// at the begin of the token
		else if (i == pos.begin)
			error_indicator += '^';

		// after the begin of the token
		else if (i > pos.begin)
			error_indicator += '~';
	}

	return sp::bred(error_indicator);
}


static std::string format_token_position(const TokenPosition& pos) noexcept
{
	std::stringstream stream;

	stream << "line " << pos.line + 1 << ", ";
	stream << "col " << pos.begin << ":" << pos.end;

	return stream.str();
}


static std::string get_error_line(std::string& line, const TokenPosition& pos) noexcept
{
	std::stringstream stream;

	// paints the error token with red
	line.insert(pos.end, sp::RESET_ALL);
	line.insert(pos.begin, sp::clr(sp::fg_bred));

	stream << line << std::endl;
	stream << generate_error_indicator(line, pos);

	return stream.str();
}



std::string exception_to_string(const Exception& exception) noexcept
{
	const SystemState& state = sys_state();

	// error position (generally a token)
	const TokenPosition& pos = exception.pos;

	// line where the error occurred
	std::string line = state.vecsource[pos.line];
	std::stringstream stream;

	// source where the error occurred
	stream << std::endl << sp::bred("Error ") << state.source_name;

	// error position
	stream << sp::clr(sp::bold) << " (" << format_token_position(pos) << "): " << sp::RESET_ALL;

	// error message
	stream << exception.msg;

	// error view
	stream << std::endl << std::endl << get_error_line(line, pos) << std::endl << std::endl;

	return stream.str();
}




void log_error(const Exception& exception) noexcept {
	sp::println(exception_to_string(exception));
}