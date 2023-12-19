#include <type/function.h>

#include <interpreter/interpreter.h>
#include <system/sysstate.h>
#include <system/exception.h>
#include <language/error_codes.h>



Type RivFunction::call(Interpreter& interpreter, const std::vector<Type>& arguments)
{
	if (recursion_depth_ >= sys_state().recursion_limit)
		throw riv_e311(declaration.name.pos, sys_state().recursion_limit);

	// creating a local instance of the global environment instead of using the pointer
	// avoids some annoying bugs
	Environment new_env(&closure);
	Type return_value;

	// assign the arguments
	for (size_t i = 0; i < declaration.params.size(); i++)
		new_env.declare(declaration.params[i], arguments[i]);

	Interpreter::ScopeConfig config;

	// configure the function body scope

	// use "closure" instead o "interpreter.environment", that way, changes made
	// to it by this function will not be discarded
	config.old_env = closure;
	config.new_env = new_env;
	config.enclose_old = false;

	// stores the current recursion depth of the function.
	// useful if you want to avoid a stack overflow
	recursion_depth_++;

	try {
		interpreter.execute_block(declaration.body, config);
	}
	catch (const ReturnSignal& signal)
	{
		return_value = signal.value;
	}

	recursion_depth_--;

	return return_value;
}