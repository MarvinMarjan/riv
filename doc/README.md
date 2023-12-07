## Syntax Notation

To improve the way how syntax is notated, it will be used a **Syntax Notation** rule to express ***Riv's*** syntax.

- `statement` - Any statement.
- `"text"` - Identifiers in general. It includes keywords, functions, variables, etc...
- `< text >` - Location where an identifier is expected. Tipically used to indicate a place where you can name things, such as variables, functions, etc...
- `[ value ]` - Location where a value (or expression) is expected.
- `[ value:Type ]` - Location where a value (or expression) of a specific type is expected.
- `( field | field )` - Groups two or more fields into one.
- `field ?` - Indicates an optional field.
- `field +` - Indicates something that can be repeated as many times as necessary. There must be at least one for it to be valid
- `field *` - Same as above, but no need to it have at least one
- `field | field`

## Development State Indicator

Sometimes a feature is specified in the documentation, but not really implemented in the interpreter. Other times, a feature is being implemented and developed...

To indicate state of the development of a feature, it will be used the following indicators:

- ***(stable)*** - Feature is supported and stable.
- ***(unstable)*** - Feature is supported, but things may not work as they should
- ***(development)*** - Feature being developed
- ***(draft)*** - Preview of an incoming feature