#pragma once

#include <vector>



class Interpreter;
class Type;


class RivCallable
{
public:
	virtual int arity() = 0;
	virtual Type call(Interpreter& interpreter, const std::vector<Type>& arguments) = 0;
};