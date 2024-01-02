#pragma once

#include <map>

#include <specter/input/istream.h>
#include <specter/output/color/painter/painter.h>



// language REPL implementer
class RivREPL : public sp::StdIstream
{
public:
	RivREPL();


private:
	sp::Painter painter_;



	std::string format() noexcept override { return painter_.paint(m_data); }
};