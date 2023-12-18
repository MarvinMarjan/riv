***Riv*** allows you to import data from another source file. Doing that is useful to separate a program into smaller pieces, making code more readable. To import a source file, use the [Import Statement](/doc/language/syntax/statements.md#import-statement).


***fileA.riv***:
```
function sum(x, y) {
	return x + y;
}

function sub(x, y) {
	return x - y;
}

function mult(x, y) {
	return x * y;
}

function div(x, y) {
	return x / y;
}
```


***fileB.riv***
```
import "fileA.riv";

print sum(5, 10); // 15
print mult(3.14159, mult(5, 5)); // ??
```


In the code above, we have two files: ***fileA.riv*** and ***fileB.riv***, where ***fileB.riv*** imports ***fileA.riv***'s functions.