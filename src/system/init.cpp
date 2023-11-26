#include <system/init.h>

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




void repl_init()
{
	RivREPL repl;

	std::string source = repl.read();

	sp::println(source);
}



void srcf_init(const int argc, const char** argv)
{
	std::string source = read_file(argv[1]);

	sp::println(source);
}