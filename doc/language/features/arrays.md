An array is a data type that can store values inside it that can be accessed later. An array starts with `[`, ends with `]` and has values separated by `,`. e.g.: `["peter", "john", "julia", "ana]`. The previous array has four string values stored (note that you can create an array that stores values of any type at once: `[10, "string", true, null, ["other array", 5.6], "end"]`).

You can access the value of an array with the [Indexing Expression](/doc/language/syntax/expressions.md#indexing). Note that the first index starts with `0` (zero).

```
var languages = ["C++", "Java", "Python", "Lua", "Javascript", "C#"];

print "My favorite language is " + languages[0];
```