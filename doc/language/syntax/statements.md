***(stable)***- [Expression Statement](#expression-statement)
- [Expression Statement](#expression-statement)
- [Block Statement](#block-statement)
- [Print Statement](#print-statement)
- [Var Statement](#var-statement)
- [If-Else Statement](#if-else-statement)
- [While Statement](#while-statement)
- [Loop Statement](#loop-statement)
- [For Statement](#for-statement)
- [Break Statement;](#break-statement)
- [Continue Statement;](#continue-statement)
- [Function Statement](#function-statement)
- [Return Statement](#return-statement)


**Statements** are operations that, unlike [Expressions](/doc/language/syntax/expressions.md), do not return any value. They just perform an action and... that's it. These actions generally affects the current environment, produces a side effect and stuff like that. **Statements** may use **Expressions** as "arguments".



## Expression Statement

`[expression] ";"`

**Expression Statements** treat conventional **Expressions** as **Statements**. Basically, with it, you can put **Expressions** where **Statements** are expected.


`2 + 2;`



## Block Statement

`"{" statement* "}"`

A **Block Statement** is a list of statements that are executed from top to bottom. A block also creates a new scope.


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



## Print Statement

`"print" expression ";"`

Prints a value to the terminal.


`print "hello, world";`



## Var Statement

`"var" <name> ("=" expression) ";"`

Declares a [Variable](/doc/language/features/variables.md).


`var language = "riv";` |
`var language;`



## If-Else Statement

`"if" "(" [condition] ")" then_statement ("else" else_statement)?`

One of the most basic control flow statement in any language. If `[condition]` is true, the `then_statement` is executed. If it's not, `else_statement` is executed, if specified.


```
if (2 == 2)
	print "condition is true";

else
	print "condition is false";
```



## While Statement

`"while" "(" [condition] ")" statement`

Executes `statement` while `[condition]` is true.


```
var i = 0;

while (i < 10)
{
	print i;
	i += 1;
}
```



## Loop Statement

`"loop" statement;`

[Syntatic Sugar](/doc/language/syntax/syntatic_sugar.md) for `while (true) ...`


```
loop
	print "forever...";
```



## For Statement

`"for" "(" (var_statement | [expression])? ";" [condition]? ";" [increment_expression]? ")" statement`

For better understanding:

`for (init; condition; increment) statement`

[Syntatic Sugar](/doc/language/syntax/syntatic_sugar.md) for:

```
init;

while (condition)
{
	statement;
	increment;
}
```



## Break Statement;

`"break" ";"`

Can only be used inside a loop. When reached, this statement immediately sends the control flow to out of the loop.


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



## Continue Statement;

`"continue" ";"`

Can only be used inside a loop. When reached, this statement immediately sends the control flow to the start of the loop.


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



## Function Statement

`"function" <name> "(" <params>* ")" "{" statements* "}"`

For better understanding:

```
function my_func(param1, param2, ...)
{
	statement1
	statement2
	...
}
```

This statement declares a [Function](/doc/language/features/functions.md).



## Return Statement

`"return" [expression]? ";"`

Returns a value from a function. [See More](/doc/language/features/functions.md)