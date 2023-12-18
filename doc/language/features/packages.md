If you need to organize code into a accessible scope, use packages. A package stores declarations inside itself. You can access that declaration later if you want using the [Package Resolution Expression](/doc/language/syntax/expressions.md#package-resolution). You can interpret a package as it being a scope with a name.

Use the [Package Statement](/doc/language/syntax/statements.md#package-statement) to create a package.


```
package data
{
	var name = "awesome_shell";
	var version = "1.0.0";
	var alpha = true;
}

print data::name;		// "awesome_shell"
print data::version;	// "1.0.0"
print data::alpha;		// true


data::version = "1.1.0";
```

Note that packages are static (you can't add or remove anything from it) and just serve to organize code. Don't try to use them as dynamic data structures like classes or structs of C++.