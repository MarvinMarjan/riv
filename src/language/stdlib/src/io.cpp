#include <cstdio>

#include <language/api/api.h>



extern "C"
{
	void lib_println(CallData* data)
	{
		printf("%s", to_string(data->args[0]));
	}
}