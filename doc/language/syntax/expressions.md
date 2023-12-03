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


**Expressions** are literal values (like `false` `"hello"` and `8`) or operations that returns a value.


# Binary

## Operator +
### Addition

***(stable)***


Operates the sum of two *Number* values:

`[ value1:Number ] "+" [ value2:Number ]`


### Concatenation

***(stable)***


Operates the merge of two *String* values:

`[ value1:String ] "+" [ value2:String ]`



## Operator -
### Subtraction

***(stable)***


Operates the subtraction of two *Number* values:

`[ value1:Number ] "-" [ value2:Number ]`



## Operator *
### Multiplication

***(stable)***


Operates the multiplication of two *Number* values:

`[ value1:Number ] "*" [ value2:Number ]`



## Operator /
### Division

***(stable)***


Operates the division of two *Number* values:

`[ value1:Number ] "/" [ value2:Number ]`



# Unary

## Operator -
### Number Negation

***(stable)***


Negates a *Number* value:

`"-" [ value:Number ]`

If `value` is positive, then it will be negated to negative. It it's negative, then it will be negated to positive.



## Operator !
### Condition Negation

***(stable)***


Negates a *Bool* value:

`"!" [ value:Bool ]`

If `value` is `true`, it becomes `false`. If it's `false`, it becomes `true`.



# Grouping

***(stable)***


Use `"(" ... ")"` to group an expression. When grouped, it will have a higher precedence.