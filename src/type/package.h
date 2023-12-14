#pragma once

#include <environment/environment.h>
#include <type/non_assignable.h>



class RivPackage : public NonAssignable
{
public:
	explicit RivPackage(const Environment& environment = {})
		: NonAssignable("package"), environment(environment) {}


	Environment environment;
};