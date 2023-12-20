## Basic Usage

A **Variable** is used to store a value and reuse it later in code. You can create a variable with the [Var Statement](/doc/language/syntax/statements.md#var-statement).

```
var number = 50;

print number;
```

Variables also can be modified after their declaration (creation):

```
number = 25;
```

Note that the value to initialize a variable is optional. If no value is specified, the variable will have the value [null](/doc/language/syntax/types.md#null) by default.


## Mutability

As said above, you can modify the value of a variable after its declaration. That behaviour is only valid to mutable variables.
A variable is mutable by default, that's why you can modify its value with no problem. If you want to declare a variable as immutable, use the `imut` [Modifier](/doc/language/features/mutability.md).

```
var my_var = 10;
mut var my_mutable = "mutable";

imut var my_immutable = "forever";

// reassignment

my_var = 2; // ok
my_mutable = "modified"; // ok

my_immutable = "not forever"; // 
```