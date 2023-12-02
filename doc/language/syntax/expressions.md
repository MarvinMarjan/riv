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
	- [Operator not](#operator-not)
		- [Condition Negation](#condition-negation)
- [Grouping](#grouping)


# Binary

## Operator +
### Addition

***(draft)***


Operates the sum of two *Number* values:

`[ value1:Number ] "+" [ value2:Number ]`


### Concatenation

***(draft)***


Operates the merge of two *String* values:

`[ value1:String ] "+" [ value2:String ]`



## Operator -
### Subtraction

***(draft)***


Operates the subtraction of two *Number* values:

`[ value1:Number ] "-" [ value2:Number ]`



## Operator *
### Multiplication

***(draft)***


Operates the multiplication of two *Number* values:

`[ value1:Number ] "*" [ value2:Number ]`



## Operator /
### Division

***(draft)***


Operates the division of two *Number* values:

`[ value1:Number ] "/" [ value2:Number ]`



# Unary

## Operator -
### Number Negation

***(draft)***


Negates a *Number* value:

`"-" [ value:Number ]`

If `value` is positive, then it will be negated to negative. It it's negative, then it will be negated to positive.



## Operator not
### Condition Negation

***(draft)***


Negates a *Bool* value:

`"not" [ value:Bool ]`

If `value` is `true`, it becomes `false`. If it's `false`, it becomes `true`.



# Grouping

***(draft)***


Use `"(" ... ")"` to group an expression. When grouped, it will have a higher precedence.not