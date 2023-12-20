# Structure

Functions are piece of code that you can reutilize as many times as you need. With functions, you can write organizated code in which each function does it work.

You can declare a function using the [Function Statement](/doc/language/syntax/statements.md#function-statement):


```
function greetings(name)
{
	print "hello, " + name + "!";
}
```

The above function is separated into three sections:

- **Name**
- **Parameters**
- **Body**


The **Name** means, obviously, the name (identifier) of the function. The **Parameters** are values that you pass to the function when you call it. The **Body** is the code that the function will execute everytime it is called.

Knowing that, the above function has the name `greetings`, receive one parameter `name` and has one [Statement](/doc/language/syntax/statements.md) of code: `print`.


***Note: The variable that receives a value passed to the function is called `parameter` and it's declared with the function declaration. The value passed to a function is called `argument` and you pass it when calling the function.*** 



# Calling

Once you have a function, you can call it with the [Call Expression](/doc/language/syntax/expressions.md#calling). So, to call the function `greetings`, we use: `greetings("someone name")`. The param `name` in the function will be assigned with `"someone name"`. After calling a function, the code inside it will be executed and the argument passed to it will be assigned to the right parameter. So, when the function's code be executed, the message printed would be `hello, someone name!`.

***note: separate arguments and parameters with `,`***


# Returning

After executing code, a function can return a value to the call location **(that's why a function is treated as an [Expression](/doc/language/syntax/expressions.md), not a [Statement](/doc/language/syntax/statements.md): it always evaluates to a value)**. It does that using the [Return Statement](/doc/language/syntax/statements.md#return-statement).

For example, you declare a function that encloses a text with `" ... "` and returns it:

```
function quote(text)
{
	return "\"" + text + "\"";
}

function greetings(name)
{
	// the value returned by quote will be "replaced" at the function's call location:

	print "hello, " + quote(name) + "!";
}


greetings("peter"); // hello, "peter"!
```


A function, by default, returns `null` if no value is specified at `return` or if `return` is not present in the function.


# Mutability

A function is also a variable, so the following code would (but it's not) be valid:

```
function say(text) {
	print text;
}

say("hello");

say = "i don't wanna be a function anymore"; // e310
```

The above code would be valid if the function was mutable (See [Mutability](/doc/language/features/mutability.md)), but it's not. A function is immutable by default and, if you want to make it mutable, you need to specify the `mut` modifier at its declaration:

```
mut function say(text) {
	print text;
}

say("hello");

say = "i don't wanna be a function anymore"; // ok
```