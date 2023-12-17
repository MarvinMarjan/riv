#pragma once

#include <vector>



class Interpreter;
class Type;


class RivCallable
{
public:
	virtual ~RivCallable() = default;

	virtual size_t arity() = 0;
	virtual Type call(Interpreter& interpreter, const std::vector<Type>& arguments) = 0;
};