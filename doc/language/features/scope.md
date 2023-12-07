Every ***Riv*** program has an environment that stores each variable and identifier declared. When you declare a variable, it's only accessible in that scope or in inner scopes. It means that if you have the scopes **A**, **B** and **C**, being **A** the outer one and **C** the inner one and you declare a variable at **B**, the variable declared will only be accessible in **B** (scope in which the variable was declared) and **C** (inner scope that inherits the outer one identifiers).

Every program starts with a scope: the global scope. It's the root scope in which every other inner scope will have access. A new scope is created every time a block is used `{ ... }`.

```
var global_x = "global";

{ // this scope inherits from the outer one, so "global_x" also is accessible

	var local_x = "local";

	print global_x; // ok
	print local_x; // ok
}

print global_x; // ok
print local_x; // error: "local_x" is inaccessible
```