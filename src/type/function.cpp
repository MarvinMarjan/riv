#include <type/function.h>

#include <interpreter/interpreter.h>



Type RivFunction::call(Interpreter& interpreter, const std::vector<Type>& arguments)
{
	// creating a local instance of the global environment instead of using the pointer
	// avoids some annoying bugs
	Environment global = *interpreter.environment.top();

	Environment new_env(&global);
	Type return_value;

	// assign the arguments
	for (size_t i = 0; i < declaration.params.size(); i++)
		new_env.declare(declaration.params[i].lexeme, arguments[i]);

	Interpreter::ScopeConfig config;

	config.old_env = interpreter.environment;
	config.new_env = new_env;
	config.enclose_old = false;

	try {
		interpreter.execute_block(declaration.body, config);
	}
	catch (const ReturnSignal& signal) {
		return_value = signal.value;
	}

	return return_value;
}