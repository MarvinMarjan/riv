- [Expression Statement](#expression-statement)
- [Print Statement](#print-statement)


**Statements** are operations that, unlike [Expressions](/doc/language/syntax/expressions.md), do not return any value. They just perform an action and... that's it. These actions generally affects the current environment, produces a side effect and stuff like that. **Statements** may use **Expressions**.

## Expression Statement

`[ expression ] ";"`

**Expression Statements** treat conventional **Expressions** as **Statements**. Basically, with it, you can put **Expressions** where **Statements** are expected.


## Print Statement

`"print" [ value ] ";"`

Prints a value to the terminal.