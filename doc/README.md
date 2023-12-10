## Syntax Notation

To improve the way how syntax is notated, it will be used a **Syntax Notation** rule to express ***Riv's*** syntax.

- `text` - Any statement. Can be used to reference others statements
- `"text"` - Identifiers in general. It includes keywords, functions, variables, etc...
- `<text>` - Location where an identifier is expected. Tipically used to indicate a place where you can name things, such as variables, functions, etc...
- `[value]` - Location where a value (or expression) is expected.
- `[value:Type]` - Location where a value (or expression) of a specific type is expected.
- `(field | field)` - Groups two or more fields into one.
- `field?` - Indicates an optional field.
- `field+` - Indicates something that can be repeated as many times as necessary. There must be at least one for it to be valid
- `field*` - Same as above, but no need to it have at least one
- `field | field`