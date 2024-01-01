#include <system/init.h>

#include <system/exception.h>



int main(const int argc, const char** argv)
{
	// mode in which system will be initialized
	InitMode mode = get_init_mode(argc, argv);

	try
	{
		// interactive mode
		if (mode == InitMode::REPL)
			repl_init(argc, argv);

		// source file mode
		else if (mode == InitMode::SourceFile)
			srcf_init(argc, argv);
	}

	catch (const Exception& e)
	{
		log_error(e);
	}
}