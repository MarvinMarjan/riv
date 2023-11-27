#include <system/exception.h>

#include <sstream>

#include <system/sysstate.h>



std::string exception_to_string(const Exception& exception) noexcept
{
	const SystemState& state = sys_state();

	const TokenPosition& pos = exception.pos;

	std::stringstream stream;

	stream << "Error " << state.source_name << " (" << "line " << pos.line + 1 << ", col " << pos.begin << ":" << pos.end << "): ";
	stream << exception.msg;

	return stream.str();
}



void log_error(const Exception& exception) noexcept {
	sp::println(exception_to_string(exception));
}