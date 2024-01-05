***Riv*** provides an API for library development. For compatibilty purposes, the API is written in C (more precisely, with `extern "C"`). The API is in-code documented.

***note: The API is declared at `/src/language/api` folder.***


## How to create libraries with it (basic)

To create your own libary and extend Riv's functionality with it, you will need to use the API and generate a shared library (`.so` file). Keep in mind that you will not be able to use C++, since it has symbol name-mungling.

To start, create a `.c` or `.cpp` file (in case of `.cpp`, you will need to use `extern "C"` to disable name-mangling (and, consequently, disable the whole C++)). In this tutorial, i will work with `.cpp`.


file.cpp:

``` C++
extern "C"
{

}
```

The library should use the API, so you need to include it. We are going to add the include path to it later.

``` C++
#include <riv/src/language/api/api.h>

extern "C"
{

}
```

Now that we have access to the API functionalities, we can start creating the library functions. Let's create a function that sum two numbers.

``` C++
#include <riv/src/language/api/api.h>

extern "C"
{
	void rlib_sum(APICallData* data)
	{

	}

	int rlib_sum_arity = 2;
}
```

We added two identifiers: `rlib_sum` and `rlib_sum_arity`, both prefixed with `rlib_`. The `rlib_` prefix means the identifier will be considered of the library. You need to prefix with it every library function you want to be available in Riv. `rlib_sum` is a library function and `rlib_sum_arity` tells how much arguments our function will receive. Note that the function name in Riv will be `sum`, and not `rlib_sum`. The prefix is removed when importing the library. You also need to make sure the two identifiers `rlib_sum` and `rlib_sum_arity` have the same base name, which is `sum`.

***note: currently, Riv has not support for creating library variables. So you can't do, for example `const char* rlib_my_variable = "a string";`. The code may compile, but you will not be able to access the variable***

Inside `rlib_sum`, we receive one argument of type `APICallData*`. It stores the arguments passed to our function (input) and stores the return value our function will return (output).

In our case, we receive only two arguments, the two numbers to sum. To get the arguments, we need to get it from `data->args.array`, which is an array that stores `APIType` values.

The first argument is at the index `0`, the second is at index `1`, and so on.

``` C++
#include <riv/src/language/api/api.h>

extern "C"
{
	void rlib_sum(APICallData* data)
	{
		const APIType num1 = data->args.array[0]; // first argument
		const APIType num2 = data->args.array[1]; // second argument
	}

	int rlib_sum_arity = 2;
}
```

Note that we can't sum two values of type `APIType`, since they aren't numbers. The API provides functions to get the value from a `APIType`. In this case, we need to get them as numbers.

``` C++
#include <riv/src/language/api/api.h>

extern "C"
{
	void rlib_sum(APICallData* data)
	{
		const APIType num1 = data->args.array[0]; // first argument
		const APIType num2 = data->args.array[1]; // second argument

		const double d_num1 = as_number(num1);
		const double d_num2 = as_number(num2);
	}

	int rlib_sum_arity = 2;
}
```

***note: In Riv, a Number type is actually a double. ***

With it, we can sum them and return the value. To return a value from a library function, you need to set the value of `data->return_value`, which also is from type `APIType`.

We need to return a Number, but `return_value` is from type `APIType`, which isn't any number type. But the API also provide functions for that. We are returning a number, so we use `new_number` to create a `APIType` that stores a number.

``` C++
#include <riv/src/language/api/api.h>

extern "C"
{
	void rlib_sum(APICallData* data)
	{
		const APIType num1 = data->args.array[0]; // first argument
		const APIType num2 = data->args.array[1]; // second argument

		const double d_num1 = as_number(num1);
		const double d_num2 = as_number(num2);

		data->return_value = new_number(d_num1 + d_num2);
	}

	int rlib_sum_arity = 2;
}
```

And that's it. Our library code is done. Now we need to compile it and import it from a Riv code. We need to compile our `file.cpp` file and the `api.cpp` file, in which the API implementation is defined.

I will use g++ to compile. The command would be something like this:

``` sh
g++ file.cpp path/to/riv/directory/src/language/api/api.cpp -o file.so -I path/to/riv/directory -fPIC -shared
```

After compiling, you can load the library from your Riv code.

```
import std.io;

import file; // the library


function main()
{
	println(sum(10, 50));
}
```

And it should work. Note that `file.so` needs to be accessible (in your `.riv` file folder. or you can add the path to the folder to import paths in the interpreter command line)