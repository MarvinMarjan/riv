#pragma once

#include <type/callable.h>
#include <statement/statement.h>



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
	RivFunction(const FunctionStatement& declaration)
		: declaration(declaration) {}


	int arity() override { return declaration.params.size(); }

	Type call(Interpreter& interpreter, const std::vector<Type>& arguments) override;


	FunctionStatement declaration;
};