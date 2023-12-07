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


**Expressions** are literal values (like `false` `"hello"` and `8`) or operations that returns a value.


# Binary

## Operator +
### Addition

***(stable)***


`[ value1:Number ] "+" [ value2:Number ]`


Operates the sum of two *Number* values.



### Concatenation

***(stable)***


`[ value1:String ] "+" [ value2:String ]`


Operates the merge of two *String* values.



## Operator -
### Subtraction

***(stable)***


`[ value1:Number ] "-" [ value2:Number ]`


Operates the subtraction of two *Number* values.



## Operator *
### Multiplication

***(stable)***


`[ value1:Number ] "*" [ value2:Number ]`


Operates the multiplication of two *Number* values.



## Operator /
### Division

***(stable)***


`[ value1:Number ] "/" [ value2:Number ]`


Operates the division of two *Number* values.



# Unary

## Operator -
### Number Negation

***(stable)***


`"-" [ value:Number ]`


Negates a *Number* value.
If `value` is positive, then it will be negated to negative. It it's negative, then it will be negated to positive.



## Operator !
### Condition Negation

***(stable)***


`"!" [ value:Bool ]`


Negates a *Bool* value.
If `value` is `true`, it becomes `false`. If it's `false`, it becomes `true`.



# Grouping

***(stable)***


Use `"(" ... ")"` to group an expression. When grouped, it will have a higher precedence.



# Assignment

***(stable)***


`< variable > "=" [ value ] ";"`


After a variable is declared, you can change its value.