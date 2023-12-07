***(stable)***- [Expression Statement](#expression-statement)
- [Expression Statement](#expression-statement)
- [Block Statement](#block-statement)
- [Print Statement](#print-statement)
- [Var Statement](#var-statement)


**Statements** are operations that, unlike [Expressions](/doc/language/syntax/expressions.md), do not return any value. They just perform an action and... that's it. These actions generally affects the current environment, produces a side effect and stuff like that. **Statements** may use **Expressions**.



## Expression Statement

`[ expression ] ";"`

**Expression Statements** treat conventional **Expressions** as **Statements**. Basically, with it, you can put **Expressions** where **Statements** are expected.


`2 + 2;`



## Block Statement

`"{" statement* "}"`

A **Block Statement** is a list of statements that are executed from top to bottom. A block lalso creates a new scope.


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

`"print" [ value ] ";"`

Prints a value to the terminal.


`print "hello, world";`



## Var Statement

`"var" < name > ("=" [ value ]) ";"`

Declares a variable.


`var language = "riv";` |
`var language;`