#pragma once

#include <vector>



class Interpreter;
class Type;


// interface for callable objects
class RivCallable
{
public:
	virtual ~RivCallable() = default;

	virtual size_t arity() const noexcept = 0;
	virtual Type call(Interpreter& interpreter, const std::vector<Type>& arguments) = 0;
};