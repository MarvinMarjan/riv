Mutability defines when something can be modified or not. Mutable objects can be modified, while Immutable can't.

The mutability of an object is set at its declaration. Once the mutability is defined, it can't be changed in the future.
To change the mutability, the following modifiers can be used:


- [`mut` (Mutable) Modifier](#mut-mutable-modifier)
- [`imut` (Immutable) Modifier](#imut-immutable-modifier)



***note: the general syntax of these modifier is:*** `("mut" | "imut")? declaration`

# `mut` (Mutable) Modifier

Declares something as *mutable*. Can be used with [Functions](/doc/language/features/functions.md) or [Variables](/doc/language/features/variables.md).

In case of a variable, it's declared as mutable by default, so `var num = 10;` is the same as `mut var num = 10;`



# `imut` (Immutable) Modifier

Declares something as *immutable*. Can be used with [Functions](/doc/language/features/functions.md) or [Variables](/doc/language/features/variables.md).

In case of a function, it's declared as immutable by default, so `function my_func() { ... }` is the same as `imut function my_func() { ... }`.