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
	- [*204*: Expect "}" to close block statement](#204-expect--to-close-block-statement)
	- [*205*: Expect "(" after "if" statement](#205-expect--after-if-statement)
	- [*206*: Expect ")" after "if" condition](#206-expect--after-if-condition)
	- [*207*: Expect "(" after "while" statement](#207-expect--after-while-statement)
	- [*208*: Expect ")" after "while" condition](#208-expect--after-while-condition)
	- [*209*: Expect "(" after "for" statement](#209-expect--after-for-statement)
	- [*210*: Expect ";" after "for" condition](#210-expect--after-for-condition)
	- [*211*: Expect ")" after "for" increment](#211-expect--after-for-increment)
	- [*212*: Cannot use "break" statement outside a loop](#212-cannot-use-break-statement-outside-a-loop)
	- [*213*: Cannot use "continue" statement outside a loop](#213-cannot-use-continue-statement-outside-a-loop)
	- [*214*: Expect function name after "function" statement](#214-expect-function-name-after-function-statement)
	- [*215*: Expect "(" after function name](#215-expect--after-function-name)
	- [*216*: Expect ")" after function parameter list](#216-expect--after-function-parameter-list)
	- [*217*: Expect parameter after ","](#217-expect-parameter-after-)
	- [*218*: Expect function body](#218-expect-function-body)
	- [*219*: Expect ")" after function arguments](#219-expect--after-function-arguments)
	- [*220*: Cannot use "return" statement outside a function](#220-cannot-use-return-statement-outside-a-function)
	- [*221*: Expect module path string after "import" statement](#221-expect-module-path-string-after-import-statement)
	- [*222*: Expect declaration statement](#222-expect-declaration-statement)
	- [*223*: Expect package name](#223-expect-package-name)
	- [*224*: Expect package body](#224-expect-package-body)
	- [*225*: Expect package member identifier](#225-expect-package-member-identifier)
	- [*226*: Expect "else" after left expression of ternary expression](#226-expect-else-after-left-expression-of-ternary-expression)
	- [*227*: Expect "\]" to close array](#227-expect--to-close-array)
	- [*228*: Expect "\]" to close indexing](#228-expect--to-close-indexing)
	- [*229*: Expect call expression after ":"](#229-expect-call-expression-after-)
- [Runtime errors](#runtime-errors)
	- [*300*: Operator "..." doesn't support operands of type: type1, type2, ...](#300-operator--doesnt-support-operands-of-type-type1-type2-)
	- [*301*: Undefined indentifier "..."](#301-undefined-indentifier-)
	- [*302*: Only functions can be called](#302-only-functions-can-be-called)
	- [*303*: Expect ... arguments, got ...](#303-expect--arguments-got-)
	- [*304*: Invalid module path](#304-invalid-module-path)
	- [*305*: Identifier ... already declared at ...](#305-identifier--already-declared-at-)
	- [*306*: Function "main" not declared](#306-function-main-not-declared)
	- [*307*: Expect package at left of "::"](#307-expect-package-at-left-of-)
	- [*308*: Invalid non-assignable type "..."](#308-invalid-non-assignable-type-)
	- [*309*: Only variables can be assigned](#309-only-variables-can-be-assigned)
	- [*310*: Cannot modify the value of an immutable variable](#310-cannot-modify-the-value-of-an-immutable-variable)
	- [*311*: Recursion limit of ... exceeded](#311-recursion-limit-of--exceeded)
	- [*312*: Only arrays can be indexed](#312-only-arrays-can-be-indexed)
	- [*313*: Expect number as array index](#313-expect-number-as-array-index)
	- [*314*: Index out of range](#314-index-out-of-range)



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





### *204*: Expect "}" to close block statement

Error caused when a [Block Statement](/doc/language/syntax/statements.md#block-statement) isn't closed.

```
{
	print "a unclosed block";
```





### *205*: Expect "(" after "if" statement

Error caused when the token after an `if` ([If Statement](/doc/language/syntax/statements.md#if-else-statement)) isn't a `(`.

`if 2 + 5 == 6) { ... }`





### *206*: Expect ")" after "if" condition

Error caused when the token before the then-block of an `if` isn't a `)`.

`if (!null == true { ... }`





### *207*: Expect "(" after "while" statement

Error caused when the token after a `while` ([While Statement](/doc/language/syntax/statements.md#while-statement)) isn't `(`.

`while true) { ... }`





### *208*: Expect ")" after "while" condition

Error caused when the token before a `while` body isn't `)`.

`while (i > 100 { ... }`





### *209*: Expect "(" after "for" statement

Error caused when the token after a `for` ([For Statement](/doc/language/syntax/statements.md#for-statement)) isn't `(`.

`for i; i >= 100; i -= 1) { ... }`





### *210*: Expect ";" after "for" condition

Error caused when the token after a `for` condition `for (decl; condition; incr) { ... }` isn't a `;`.

`for (var i = 0; i < 20, i += 1) { ... }`





### *211*: Expect ")" after "for" increment

Error caused when the token after a `for` increment `for (decl; cond; increment) { ... }` isn't a `)`.

`for (var i = 100; i > 0; i -= 1 { ... }`





### *212*: Cannot use "break" statement outside a loop

Error caused when a `break` ([Break Statement](/doc/language/syntax/statements.md#break-statement)) is placed outside any loop body.

```
var foo = 10;

if (foo < 20)
	break; // e212
```





### *213*: Cannot use "continue" statement outside a loop

Error caused when a `continue` ([Continue Statement](/doc/language/syntax/statements.md#continue-statement)) is placed outside any loop body.

```
var bar = !!false != (!true == true);

if (!bar)
	continue; // e213
```





### *214*: Expect function name after "function" statement

Error caused when the token after a `function` ([Function Statement](/doc/language/syntax/statements.md#function-statement)) isn't an identifier (name of the function).

`function (foo, baz) { ... }`





### *215*: Expect "(" after function name

Error caused when the token after a `function` name isn't a `(`.

`function foo [bar) { ... }`





### *216*: Expect ")" after function parameter list

Error caused when the token after a `function` parameter list isn't `)`.

`function baz(foo, foo2, foo3 { ... }`





### *217*: Expect parameter after ","

Error caused when the token after a `,` (used to separate parameters) isn't an identifier (parameter).

`function foo(bar, baz, 123) { ... }`





### *218*: Expect function body

Error caused when the token after a `)` (closes the parameter list) of a parameter list isn't `{`.

`function bar(foo) ... }`





### *219*: Expect ")" after function arguments

Error caused when the token after an arguments list of a [Call Expression](/doc/language/syntax/expressions.md#calling) isn't `)`.

```
function foo(number) { ... }


foo(4; // e219
```





### *220*: Cannot use "return" statement outside a function

Error caused when a `return` ([Return Statement](/doc/language/syntax/statements.md#return-statement)) is placed outside a function body.

```
var is_monday = true;

if (is_monday)
	return "wanna die..."; // e220
```





### *221*: Expect module path string after "import" statement

Error caused when the token after an `import` ([Import Statement](/doc/language/syntax/statements.md#import-statement)) isn't a string.

`import false;`





### *222*: Expect declaration statement

Error caused when a statement is placed in somewhere that expects a declaration.

```
// at global scope...

print "invalid statement"; // e222
```





### *223*: Expect package name

Error caused when the token after a `package` ([Package Statement](/doc/language/syntax/statements.md#package-statement)) isn't an identifier.

`package 2 + 2 { ... }`





### *224*: Expect package body

Error caused by omitting the package body after its name.

`package foo 15`





### *225*: Expect package member identifier

Error caused when the token after an `::` ([Package Resolution Expression](/doc/language/syntax/expressions.md#package-resolution)) isn't a identifier.

`my_pack::(2 / 9.4);`





### *226*: Expect "else" after left expression of ternary expression

Error caused when the token after the left expression of a [Ternary Expression](/doc/language/syntax/expressions.md#ternary) isn't `else`.

`true ? "true!!" : "false :("`





### *227*: Expect "]" to close array

Error caused when an [Array](/doc/language/features/arrays.md) isn't closed with `]`.

```
var my_array = [0, 1, 1, 2, 3, 5, 8, 13;
```





### *228*: Expect "]" to close indexing

Error caused when an [Indexing Expression](/doc/language/syntax/expressions.md#indexing) isn't closed with `]`.

`my_array[4;`





### *229*: Expect call expression after ":"

Error caused when there is not an expression after `:` ([Argument Simplification](/doc/language/syntax/expressions.md#argument-simplification)).

`"hello, world":if (true) {}`





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





### *304*: Invalid module path

Error caused when the path specified after an `import` ([Import Statement](/doc/language/syntax/statements.md)) isn't valid (does not exist).

`import "some_invalid/path";`





### *305*: Identifier ... already declared at ...

Error caused when an identifier is being re-declared.

```
var foo = 8;

var foo = "string"; // e305
```




### *306*: Function "main" not declared

Error caused when the `main` function isn't declared.

```
function invert(x) { return !x; }
function is_null(x) { return !x; }

// interpreter: where do i start the program? (e306)
```





### *307*: Expect package at left of "::"

Error caused when the value at left of a `::` ([Package Resolution Expression](/doc/language/syntax/expressions.md#package-resolution)) isn't a [Package](/doc/language/features/packages.md)

```
package my_pack
{
	...
}

print 50::my_var; // e307
```





### *308*: Invalid non-assignable type "..."

Error caused when trying to do an invalid operation with any [non-assignable](/doc/language/syntax/non-assignable.md) type





### *309*: Only variables can be assigned

Error caused when trying to assign a non-variable value.

`5 = 90;`





### *310*: Cannot modify the value of an immutable variable

Error caused when trying to modify a immutable [Variable](/doc/language/features/variables.md) or [Function](/doc/language/features/functions.md).

```
imut my_const = "constant";

my_const = "volatile"; // e310
```

or

```
// functions are immutable by default
function my_func() {}

my_func = "another value"; // e310
```





### *311*: Recursion limit of ... exceeded

Error caused when a function is called inside itself (recursive function) more than the recursion limit, which is 1000 by default. This error exists to prevent stack overflow.

```
function recursive() {
	recursive() // calling itself infinitely
}
```





### *312*: Only arrays can be indexed

Error caused when trying to do an [Indexing Expression](/doc/language/syntax/expressions.md#indexing) with a non-array-type value.

`2[5];`





### *313*: Expect number as array index

Error caused when the value inside an [Indexing Expression](/doc/language/syntax/expressions.md#indexing) isn't a number.

`["peter", "ana", "smith"][false]`





### *314*: Index out of range

Error caused when the index passed in an [Indexing Expression](/doc/language/syntax/expressions.md#indexing) is invalid (e.g. it may be greater (or lesser) than the array size).

`[1, 2, 3][3]`