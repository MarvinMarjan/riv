#pragma once

#include <type/callable.h>
#include <statement/statement.h>



class Environment;


// implements the functionality of functions
class RivFunction : public RivCallable
{
public:

	// struct thrown when a ReturnStatement is reached
	struct ReturnSignal
	{
		explicit ReturnSignal(const Type& value)
			: value(value) {}

		Type value;
	};
	

	RivFunction() = default;
	explicit RivFunction(const FunctionStatement& declaration, Environment* const closure)
		: declaration(declaration), closure(closure) {}

	size_t arity() const noexcept override { return declaration.params.size(); }

	Type call(Interpreter& interpreter, const std::vector<Type>& arguments) override;


	FunctionStatement declaration;
	Environment*      closure = nullptr;

private:
	size_t recursion_depth_ = 0;
};