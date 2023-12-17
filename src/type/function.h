#pragma once

#include <type/callable.h>
#include <statement/statement.h>
#include <environment/environment.h>



class RivFunction : public RivCallable
{
public:
	struct ReturnSignal
	{
		ReturnSignal(const Type& value)
			: value(value) {}

		Type value;
	};
	

	RivFunction() = default;
	explicit RivFunction(const FunctionStatement& declaration, const Environment& closure)
		: declaration(declaration), closure(closure) {}

	size_t arity() override { return declaration.params.size(); }

	Type call(Interpreter& interpreter, const std::vector<Type>& arguments) override;


	FunctionStatement declaration;
	Environment closure;
};