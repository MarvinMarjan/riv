#include <system/init.h>

#include <system/exception.h>

#include <dlfcn.h>
#include <language/api/api.h>



int main(const int argc, const char** argv)
{
	void* lib = dlopen("lib/std/io.so", RTLD_LAZY);


	CallData data = new_call_data();

	data.args = new APIType[] { new_string("hello, world") };


	auto fun = (void (*)(CallData*))dlsym(lib, "lib_println");

	fun(&data);


	return 0;

	// mode in which system will be initialized
	InitMode mode = get_init_mode(argc, argv);

	try
	{
		// interactive mode
		if (mode == InitMode::REPL)
			repl_init();

		// source file mode
		else if (mode == InitMode::SourceFile)
			srcf_init(argc, argv);
	}

	catch (const Exception& e)
	{
		log_error(e);
	}
}