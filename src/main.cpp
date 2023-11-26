#include <system/init.h>



int main(const int argc, const char** argv)
{
	// mode in which system will be initialized
	InitMode mode = get_init_mode(argc, argv);

	// interative mode
	if (mode == InitMode::REPL)
		repl_init();

	// source file mode
	else if (mode == InitMode::SourceFile)
		srcf_init(argc, argv);
}