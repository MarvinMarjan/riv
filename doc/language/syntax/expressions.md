- [Binary](#binary)
	- [Operator +](#operator-)
		- [Addition](#addition)
		- [Concatenation](#concatenation)
	- [Operator -](#operator--)
		- [Subtraction](#subtraction)
	- [Operator \*](#operator--1)
		- [Multiplication](#multiplication)
	- [Operator /](#operator--2)
		- [Division](#division)
- [Unary](#unary)
	- [Operator -](#operator---1)
		- [Number Negation](#number-negation)
	- [Operator !](#operator--3)
		- [Condition Negation](#condition-negation)
- [Grouping](#grouping)
- [Assignment](#assignment)
	- [Operator +=](#operator--4)
	- [Operator -=](#operator---2)
	- [Operator \*=](#operator--5)
	- [Operator /=](#operator--6)
- [Calling](#calling)
- [Package Resolution](#package-resolution)
- [Ternary](#ternary)
- [Indexing](#indexing)
- [Argument Simplification](#argument-simplification)


**Expressions** are literal values (like `false` `"hello"` and `8`) or operations that returns a value.


# Binary

## Operator +
### Addition

`[value1:Number] "+" [value2:Number]`


Operates the sum of two *Number* values.



### Concatenation

`[value1:String] "+" [value2:String]`


Operates the merge of two *String* values.



## Operator -
### Subtraction

`[value1:Number] "-" [value2:Number]`


Operates the subtraction of two *Number* values.



## Operator *
### Multiplication

`[value1:Number] "*" [value2:Number]`


Operates the multiplication of two *Number* values.



## Operator /
### Division

`[value1:Number] "/" [value2:Number]`


Operates the division of two *Number* values.



# Unary

## Operator -
### Number Negation

`"-" [value:Number]`


Negates a *Number* value.
If `value` is positive, then it will be negated to negative. If it's negative, then it will be negated to positive.



## Operator !
### Condition Negation

`"!" [value:Bool]`


Negates a *Bool* value.
If `value` is `true`, it becomes `false`. If it's `false`, it becomes `true`.



# Grouping

Use `"(" ... ")"` to group an expression. When grouped, it will have a higher precedence.



# Assignment

`<variable> "=" [value]`


After a variable is declared, you can change its value. This expression evaluates to the value assigned.



## Operator +=

`<variable> "+=" [value]`


[Syntatic Sugar](/doc/language/syntax/syntatic_sugar.md) for `<variable> = <variable> + [value]`



## Operator -=

`<variable> "-=" [value]`


[Syntatic Sugar](/doc/language/syntax/syntatic_sugar.md) for `<variable> = <variable> - [value]`



## Operator *=

`<variable> "*=" [value]`


[Syntatic Sugar](/doc/language/syntax/syntatic_sugar.md) for `<variable> = <variable> * [value]`



## Operator /=

`<variable> "/=" [value]`


[Syntatic Sugar](/doc/language/syntax/syntatic_sugar.md) for `<variable> = <variable> / [value]`



# Calling

`<identifier> "(" <params>* ")"`

Calls anything that can be called.

See [Function Calling](/doc/language/features/functions.md#calling).



# Package Resolution

`<package> "::" <package_member>`

Searches for a identifier inside a package. [See More](/doc/language/features/packages.md).



# Ternary

`[condition] "?" [if_true_value] "else" [if_false_value]`

A ternary expression is a compact way to execute conditions that returns a value.
If the condition is true, `if_true_value` is returned, otherwise `if_false_value` is returned.


# Indexing

`[array:Array] "[" [index:Number] "]"`

[See More](/doc/language/features/arrays.md).



# Argument Simplification

`[first_argument] ":" [function_call:Function]`

Sends `first_argument` as the first argument to `function_call`.

e.g. `5:negate()` is the same as `negate(5)`.