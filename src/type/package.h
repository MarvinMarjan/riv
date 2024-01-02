#pragma once

#include <type/non_assignable.h>



class Environment;


class RivPackage : public NonAssignable
{
public:
	explicit RivPackage(Environment* const environment = nullptr)
		: NonAssignable("package"), environment(environment) {}


	Environment* environment = nullptr;
};