#include <system/init.h>

#include <scanner/scanner.h>
#include <specter/output/ostream.h>
#include <common/filesys.h>
#include <repl/repl.h>


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

	std::vector<Token> tokens = scanner.scan();

	for (const Token& token : tokens)
		sp::println((int)token.type, " - ", token.lexeme);
}



void repl_init()
{
	RivREPL repl;

	std::string source;

	while ((source = repl.read()) != ".exit")
		run(source);
}



void srcf_init(const int argc, const char** argv)
{
	run(read_file(argv[1]));
}