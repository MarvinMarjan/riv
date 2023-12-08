#include <type/function.h>

#include <interpreter/interpreter.h>

#include <specter/output/ostream.h>

Type RivFunction::call(Interpreter& interpreter, const std::vector<Type>& arguments)
{
	sp::println("begin");
	Environment new_env(interpreter.environment.top());
	sp::println("end");
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