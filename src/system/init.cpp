#include <system/init.h>

#include <specter/output/ostream.h>

#include <scanner/scanner.h>
#include <parser/parser.h>
#include <interpreter/interpreter.h>
#include <expression/printer.h>
#include <common/filesys.h>
#include <repl/repl.h>
#include <system/sysstate.h>
#include <language/error_codes.h>
#include <system/exception.h>



InitMode get_init_mode(const int argc, const char** argv) noexcept
{
	if (argc < 2)
		return InitMode::REPL;
	else
		return InitMode::SourceFile;
}



std::vector<Token> scan(const std::string& source)
{
	const SystemState& state = sys_state();

	Scanner scanner(source);

	// scan source into tokens
	std::vector<Token> tokens = scanner.scan();

	return tokens;
}



std::vector<Statement*> parse(const std::vector<Token>& source)
{
	Parser parser(source);

	// parse the tokens
	std::vector<Statement*> statements = parser.parse();

	return statements;
}



void run(const std::vector<Statement*>& statements)
{
	Interpreter().interpret(statements);
}



void run(const std::string& source)
{
	const SystemState& state = sys_state();

	std::vector<Token> tokens = scan(source);

	if (state.has_error)
		return;

	std::vector<Statement*> statements = parse(tokens);

	if (state.has_error)
		return;

	run(statements);
}




void repl_init()
{
	const SystemState& state = sys_state();

	// REPL instance
	RivREPL repl;
	Interpreter interpreter;

	std::string source;

	while (true)
	{
		sp::print("> ");

		source = repl.read();

		if (source == ".exit")
			break;


		init_state_using_repl(source);


		// processing

		std::vector<Token> tokens = scan(source);

		if (state.has_error)
			continue;

		std::vector<Statement*> statements = parse(tokens);
		
		if (state.has_error)
			continue;

		interpreter.interpret(statements);
	}
}



void srcf_init(const int argc, const char** argv)
{
	// checks if file exists
	if (!path_exists(argv[1]))
		throw riv_e001(argv[1]);

	const SystemState& state = sys_state();

	init_state_using_srcfile(argv[1]);
	run(state.strsource);
}