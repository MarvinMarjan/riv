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
- [Runtime errors](#runtime-errors)
	- [*300*: Operator "..." doesn't support operands of type: type1, type2, ...](#300-operator--doesnt-support-operands-of-type-type1-type2-)



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





### *102*: Multi-line string not supported

Error caused when inserting a new line inside a string. **Riv** doesn't support multi-line strings.





## Parser errors

### *200*: Expression expected

Error caused when a location expecting	 an expression doesn't receive it.





### *201*: Expect ")" to close grouping expression

Error caused when a group expression `( ... )` isn't closed.





### *202*: Expect ";" after statement

Error caused when `;` isn't added at a statement end.





## Runtime errors

### *300*: Operator "..." doesn't support operands of type: type1, type2, ...

Error caused when an operator receive operands in which types are not supported. e.g. `2 + false`