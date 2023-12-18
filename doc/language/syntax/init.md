When starting a new ***Riv*** program and creating the first (probaly the `main.riv`) file, you will need to know two basic things:

1. At global scope, you will not be able to put statements that aren't declarations. So you will not be able to do:

```
// global scope


loop
	print "my program loop";
```

The code above would throw the [E222](/doc/language/error_codes.md#222-expect-declaration-statement) ("Expect declaration statement") parser error. If you try to fix it with:

```
// global scope


var my_global_var = "just declarations here";
```

Then the [E309](/doc/language/error_codes.md#306-function-main-not-declared) ("Function 'main' not declared") runtime error would be thrown, bringing us to the second:

2. Every ***Riv*** program need to have one `function main() { ... }`, that way the interpreter knows where to start the code. Inside it, you are able to use statements. With that, the correct code would be:

```
// global scope


var my_global_var = "just declarations here."

function main()
{
	loop
		print "my program loop.";
}
```