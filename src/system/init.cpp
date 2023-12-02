#include <system/init.h>

#include <specter/output/ostream.h>

#include <scanner/scanner.h>
#include <parser/parser.h>
#include <expression/printer.h>
#include <common/filesys.h>
#include <repl/repl.h>
#include <system/sysstate.h>



InitMode get_init_mode(const int argc, const char** argv) noexcept
{
	if (argc < 2)
		return InitMode::REPL;
	else
		return InitMode::SourceFile;
}




void run(const std::string& source)
{
	const SystemState& state = sys_state();

	Scanner scanner(source);

	// scan source into tokens
	std::vector<Token> tokens = scanner.scan();

	if (state.has_error)
		return;

	Parser parser(tokens);

	// parse the tokens
	Expression* expr = parser.parse();

	std::string exprstr = ExprPrinter().print(expr);

	sp::println(exprstr);
}



void repl_init()
{
	const SystemState& state = sys_state();

	// REPL instance
	RivREPL repl;

	std::string source;

	while ((source = repl.read()) != ".exit")
	{
		init_state_using_repl(source);
		run(source);
	}
}



void srcf_init(const int argc, const char** argv)
{
	const SystemState& state = sys_state();

	init_state_using_srcfile(argv[1]);
	run(state.strsource);
}