- [Interpreter errors](#interpreter-errors)
	- [*001*: Invalid source file](#001-invalid-source-file)
- [Scanner errors](#scanner-errors)
	- [*100*: Invalid token](#100-invalid-token)
	- [*101*: Unterminated string](#101-unterminated-string)
	- [*102*: Multi-line string not supported](#102-multi-line-string-not-supported)
- [Parser errors](#parser-errors)
	- [*200*: Expression expected](#200-expression-expected)
	- [*201*: Expect ")" to close grouping expression](#201-expect--to-close-grouping-expression)
	- [*202*: Expect ";" after statement](#202-expect--after-statement)
	- [*203*: Expect variable name after "var" keyword](#203-expect-variable-name-after-var-keyword)
	- [*204*: Only variables can be assigned](#204-only-variables-can-be-assigned)
	- [*205*: Expect "}" to close block statement](#205-expect--to-close-block-statement)
	- [*206*: Expect "(" after "if" statement](#206-expect--after-if-statement)
	- [*207*: Expect ")" after "if" condition](#207-expect--after-if-condition)
	- [*208*: Expect "(" after "while" statement](#208-expect--after-while-statement)
	- [*209*: Expect ")" after "while" condition](#209-expect--after-while-condition)
	- [*210*: Expect "(" after "for" statement](#210-expect--after-for-statement)
	- [*211*: Expect ";" after "for" condition](#211-expect--after-for-condition)
	- [*212*: Expect ")" after "for" increment](#212-expect--after-for-increment)
	- [*213*: Cannot use "break" statement outside a loop](#213-cannot-use-break-statement-outside-a-loop)
	- [*214*: Cannot use "continue" statement outside a loop](#214-cannot-use-continue-statement-outside-a-loop)
	- [*215*: Expect function name after "function" statement](#215-expect-function-name-after-function-statement)
	- [*216*: Expect "(" after function name](#216-expect--after-function-name)
	- [*217*: Expect ")" after function parameter list](#217-expect--after-function-parameter-list)
	- [*218*: Expect parameter after ","](#218-expect-parameter-after-)
	- [*219*: Expect function body](#219-expect-function-body)
	- [*220*: Expect ")" after function arguments](#220-expect--after-function-arguments)
	- [*221*: Cannot use "return" statement outside a function](#221-cannot-use-return-statement-outside-a-function)
- [Runtime errors](#runtime-errors)
	- [*300*: Operator "..." doesn't support operands of type: type1, type2, ...](#300-operator--doesnt-support-operands-of-type-type1-type2-)
	- [*301*: Undefined indentifier "..."](#301-undefined-indentifier-)
	- [*302*: Only functions can be called](#302-only-functions-can-be-called)
	- [*303*: Expect ... arguments, got ...](#303-expect--arguments-got-)



***Riv*** uses a code to represent every error message. They are grouped this way:

- **001** - **099**: interpreter errors
- **100** - **199**: scanner errors
- **200** - **299**: parser errors
- **300** - **399**: runtime errors



## Interpreter errors

### *001*: Invalid source file

Error caused when passing an invalid file path to the interpreter.





## Scanner errors

### *100*: Invalid token

Error caused when inserting an invalid (not supported) token.





### *101*: Unterminated string

Error caused when a string is not closed.

`"hello, world`





### *102*: Multi-line string not supported

Error caused when inserting a new line inside a string. **Riv** doesn't support multi-line strings.


```
"hello, 
world"
```




## Parser errors

### *200*: Expression expected

Error caused when a location expecting an expression doesn't receive it.

`print ;`





### *201*: Expect ")" to close grouping expression

Error caused when a group expression `( ... )` isn't closed.

`(2 + (-8)`





### *202*: Expect ";" after statement

Error caused when `;` isn't added at a statement end.

`print 10`





### *203*: Expect variable name after "var" keyword

Error caused when the variable name is missing at its declaration.

`var = 90;`





### *204*: Only variables can be assigned

Error caused when trying to assign a non-variable value.

`5 = 90;`





### *205*: Expect "}" to close block statement

Error caused when a [Block Statement](/doc/language/syntax/statements.md#block-statement) isn't closed.

```
{
	print "a unclosed block";
```





### *206*: Expect "(" after "if" statement

Error caused when the token after an `if` ([If Statement](/doc/language/syntax/statements.md#if-else-statement)) isn't a `(`.

`if 2 + 5 == 6) { ... }`





### *207*: Expect ")" after "if" condition

Error caused when the token before the then-block of an `if` isn't a `)`.

`if (!null == true { ... }`





### *208*: Expect "(" after "while" statement

Error caused when the token after a `while` ([While Statement](/doc/language/syntax/statements.md#while-statement)) isn't `(`.

`while true) { ... }`





### *209*: Expect ")" after "while" condition

Error caused when the token before a `while` body isn't `)`.

`while (i > 100 { ... }`





### *210*: Expect "(" after "for" statement

Error caused when the token after a `for` ([For Statement](/doc/language/syntax/statements.md#for-statement)) isn't `(`.

`for i; i >= 100; i -= 1) { ... }`





### *211*: Expect ";" after "for" condition

Error caused when the token after a `for` condition `for (decl; condition; incr) { ... }` isn't a `;`.

`for (var i = 0; i < 20, i += 1) { ... }`





### *212*: Expect ")" after "for" increment

Error caused when the token after a `for` increment `for (decl; cond; increment) { ... }` isn't a `)`.

`for (var i = 100; i > 0; i -= 1 { ... }`





### *213*: Cannot use "break" statement outside a loop

Error caused when a `break` ([Break Statement](/doc/language/syntax/statements.md#break-statement)) is placed outside any loop body.

```
var foo = 10;

if (foo < 20)
	break; // e213
```





### *214*: Cannot use "continue" statement outside a loop

Error caused when a `continue` ([Continue Statement](/doc/language/syntax/statements.md#continue-statement)) is placed outside any loop body.

```
var bar = !!false != (!true == true);

if (!bar)
	continue; // e214
```





### *215*: Expect function name after "function" statement

Error caused when the token after a `function` ([Function Statement](/doc/language/syntax/statements.md#function-statement)) isn't an identifier (name of the function).

`function (foo, baz) { ... }`





### *216*: Expect "(" after function name

Error caused when the token after a `function` name isn't a `(`.

`function foo [bar) { ... }`





### *217*: Expect ")" after function parameter list

Error caused when the token after a `function` parameter list isn't `)`.

`function baz(foo, foo2, foo3 { ... }`





### *218*: Expect parameter after ","

Error caused when the token after a `,` (used to separate parameters) isn't an identifier (parameter).

`function foo(bar, baz, 123) { ... }`





### *219*: Expect function body

Error caused when the token after a `)` (closes the parameter list) of a parameter list isn't `{`.

`function bar(foo) ... }`





### *220*: Expect ")" after function arguments

Error caused when the token after an arguments list of a [Call Expression](/doc/language/syntax/expressions.md#calling) isn't `)`.

```
function foo(number) { ... }


foo(4; // e220
```





### *221*: Cannot use "return" statement outside a function

Error caused when a `return` ([Return Statement](/doc/language/syntax/statements.md#return-statement)) is placed outside a function body.

```
var is_monday = true;

if (is_monday)
	return "wanna die..."; // e221
```





## Runtime errors

### *300*: Operator "..." doesn't support operands of type: type1, type2, ...

Error caused when an operator receive operands in which types are not supported.

`2 + false`





### *301*: Undefined indentifier "..."

Error caused when trying to call an undefined indetifier.

```
var boolean = true;

print number; // undefined indentifier "number"
```





### *302*: Only functions can be called

Error caused when trying to call a non-callable value.

`"totally callable value"(true);`





### *303*: Expect ... arguments, got ...

Error caused when passing the incorrect number of arguments a function can receive.

```
function say(text)
{
	print text;
}


say("hello, " + "world", "some extra value here"); // e303
```