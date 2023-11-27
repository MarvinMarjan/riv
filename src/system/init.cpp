#include <system/init.h>

#include <scanner/scanner.h>
#include <specter/output/ostream.h>
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
	Scanner scanner(source);

	// scan source into tokens
	std::vector<Token> tokens = scanner.scan();

	for (const Token& token : tokens)
		sp::println((int)token.type, " - ", token.lexeme);
}



void repl_init()
{
	const SystemState& state = sys_state();

	// REPL instance
	RivREPL repl;

	std::string source;

	while ((source = repl.read()) != ".exit")
	{
		init_state_repl(source);
		run(source);
	}
}



void srcf_init(const int argc, const char** argv)
{
	const SystemState& state = sys_state();

	init_state_srcfile(argv[1]);
	run(state.strsource);
}