#include <system/exception.h>

#include <sstream>

#include <specter/output/color/color.h>

#include <system/sysstate.h>



static std::string get_error_line(std::string& line, const TokenPosition& pos) noexcept
{
	const std::string tabs = "\t";

	std::stringstream stream;
	std::string error_indicator = "";

	while (line.front() == ' ' || line.front() == '\t')
		line.erase(line.begin());

	line.insert(pos.end, sp::RESET_ALL);
	line.insert(pos.begin, sp::clr(sp::fg_bred));

	for (size_t i = 0; i < line.size() && i < pos.end; i++)
	{
		if (i < pos.begin)
			error_indicator += ' ';

		else if (i == pos.begin)
			error_indicator += '^';

		else if (i > pos.begin)
			error_indicator += '~';
	}

	stream << tabs << line << std::endl;
	stream << tabs << error_indicator;

	return stream.str();
}


static std::string format_token_position(const TokenPosition& pos) noexcept
{
	std::stringstream stream;

	stream << "line " << pos.line + 1 << ", ";
	stream << "col " << pos.begin << ":" << pos.end;

	return stream.str();
}



std::string exception_to_string(const Exception& exception) noexcept
{
	const SystemState& state = sys_state();

	const TokenPosition& pos = exception.pos;

	std::string line = state.vecsource[pos.line];
	std::stringstream stream;

	stream << sp::bred("Error ") << state.source_name;
	stream << sp::clr(sp::bold) << " (" << format_token_position(pos) << "): " << sp::RESET_ALL;

	stream << exception.msg;

	stream << std::endl << std::endl << get_error_line(line, pos) << std::endl << std::endl;

	return stream.str();
}



void log_error(const Exception& exception) noexcept {
	sp::println(exception_to_string(exception));
}