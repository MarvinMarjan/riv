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
- [Runtime errors](#runtime-errors)
	- [*300*: Operator "..." doesn't support operands of type: type1, type2, ...](#300-operator--doesnt-support-operands-of-type-type1-type2-)
	- [*301*: Undefined indentifier "..."](#301-undefined-indentifier-)



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