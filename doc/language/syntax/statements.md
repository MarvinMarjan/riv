- [Expression Statement](#expression-statement)
	- [Expansion](#expansion)
	- [About](#about)
	- [Example](#example)
- [Block Statement](#block-statement)
	- [Expansion](#expansion-1)
	- [About](#about-1)
	- [Example](#example-1)
- [`var` Statement](#var-statement)
	- [Expansion](#expansion-3)
	- [About](#about-3)
	- [Example](#example-3)
- [`if` / `else` Statement](#if--else-statement)
	- [Expansion](#expansion-4)
	- [About](#about-4)
	- [Example](#example-4)
- [`while` Statement](#while-statement)
	- [Expansion](#expansion-5)
	- [About](#about-5)
	- [Example](#example-5)
- [`loop` Statement](#loop-statement)
	- [Expansion](#expansion-6)
	- [About](#about-6)
	- [Example](#example-6)
- [`for` Statement](#for-statement)
	- [Expansion](#expansion-7)
	- [About](#about-7)
	- [Example](#example-7)
- [`break` Statement](#break-statement)
	- [Expansion](#expansion-8)
	- [About](#about-8)
	- [Example](#example-8)
- [`continue` Statement](#continue-statement)
	- [Expansion](#expansion-9)
	- [About](#about-9)
	- [Example](#example-9)
- [`function` Statement](#function-statement)
	- [Expansion](#expansion-10)
	- [About](#about-10)
	- [Example](#example-10)
- [`return` Statement](#return-statement)
	- [Expansion](#expansion-11)
	- [About](#about-11)
	- [Example](#example-11)
- [`import` Statement](#import-statement)
	- [Expansion](#expansion-12)
	- [About](#about-12)
	- [Example](#example-12)
- [`package` Statement](#package-statement)
	- [Expansion](#expansion-13)
	- [About](#about-13)
	- [Example](#example-13)



**Statements** are operations that, unlike [Expressions](/doc/language/syntax/expressions.md), do not return any value. They just perform an action and... that's it. These actions generally affects the current environment, produces a side effect, changes the control flow and stuff like that. **Statements** may use **Expressions** as "arguments" (operands).





# Expression Statement

`[expression] ";"`


## Expansion

`expression;`


## About

**Expression Statements** treat conventional **Expressions** as **Statements**. Basically, with it, you can put **Expressions** where **Statements** are expected.


## Example


`2 + 2;`





# Block Statement

`"{" statement* "}"`


## Expansion

`{ statement1; statement2; ... }`


## About

A **Block Statement** is a list of statements that are executed from top to bottom. A block also creates a new [Scope](/doc/language/features/scope.md).


## Example

```
print "block ahead!";

var outer = "outer the block";

{
	var inner = "inner the block";

	print "into";
	print "the";
	print "block!!";

	print inner; // ok
	print outer; // ok
}

print inner; // error
```





# `var` Statement

`("mut" | "imut")? "var" <name> ("=" expression)? ";"`


## Expansion

```
var name;
var name = expression;

mut var name;
mut var name = expression;

imut var name;
imut var name = expression;
```



## About

Declares a [Variable](/doc/language/features/variables.md).


## Example

`var language = "riv";` |
`var language;`





# `if` / `else` Statement

`"if" "(" [condition] ")" then_statement ("else" else_statement)?`


## Expansion

```
if (condition)
	then_statement;
```

```
if (condition)
	then_statement;

else
	else_statement
```


## About

One of the most basic control flow statement in any language. If `[condition]` is true, the `then_statement` is executed. If it's not, `else_statement` is executed, if specified.


## Example

```
if (2 == 2)
	print "condition is true";

else
	print "condition is false";
```





# `while` Statement

`"while" "(" [condition] ")" statement`


## Expansion

```
while (condition)
	statement;
```


## About

Executes `statement` while `[condition]` is true.


## Example

```
var i = 0;

while (i < 10)
{
	print i;
	i += 1;
}
```





# `loop` Statement

`"loop" statement;`


## Expansion

```
loop
	statement;
```


## About

[Syntatic Sugar](/doc/language/syntax/syntatic_sugar.md) for `while (true) ...`


## Example

```
loop
	print "forever...";
```





# `for` Statement

`"for" "(" (var_statement | [expression])? ";" [condition]? ";" [increment_expression]? ")" statement`


## Expansion

```
// i'm not going to expand all that ☠️.
// just take the basic:

for (var_declaration | expression; condition; increment)
	statement
```



## About

[Syntatic Sugar](/doc/language/syntax/syntatic_sugar.md) for:


```
init;

while (condition)
{
	statement;
	increment;
}
```


## Example

```
for (var i = 0; i < 10; i++)
	print i;
```






# `break` Statement

`"break" ";"`


## Expansion

`break;`


## About

Can only be used inside a loop. When reached, this statement immediately sends the control flow to out of the loop.


## Example

```
var i = 0;

while (true)
{
	if (i >= 10)
		break;

	print i;
	i += 1;
}
```





# `continue` Statement

`"continue" ";"`


## Expansion

`continue;`


## About

Can only be used inside a loop. When reached, this statement immediately sends the control flow to the start of the loop.


## Example

```
var i = 0;

while (true)
{
	print i;
	i += 1;

	// go to the start of the loop
	if (i < 10)
		continue;

	// stop the loop
	break;
}
```





# `function` Statement

`("mut" | "imut")? "function" <name> "(" <params>* ")" "{" statements* "}"`


## Expansion

```
function name(...) { statements }
mut function name(...) { statements }
imut function name(...) { statements }
```


## About

This statement declares a [Function](/doc/language/features/functions.md).


## Example

```
function foo() {
	print "at foo...";
}
```





# `return` Statement

`"return" [expression]? ";"`


## Expansion

```
return;
return expression;
```


## About

Returns a value from a function. [See More](/doc/language/features/functions.md).


## Example

```
function sum(x, y) {
	return x + y;
}

print sum(5, -2);
```





# `import` Statement

`"import" [path] ";"`


## Expansion

`import path;`


## About

Imports data from other source file. [See More](/doc/language/features/importing.md).


## Example

`import "path/to/my/file"`





# `package` Statement

`"package" <name> "{" declarations* "}"`


## Expansion

```
package name
{
	declarations
}
```


## About

Declares a new [Package](/doc/language/features/packages.md).


## Example

```
package state
{
	var quit = false;
	imut var version = "1.0.0";
	imut var name = "my_app";
}

function quit() {
	state::quit = true;
}

function main()
{
	loop
	{
		if (state::quit)
			break;

		if (2 > 0)
			quit();
	}

	print "bye bye!";
}
```