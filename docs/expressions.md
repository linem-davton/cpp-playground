# C++ Expressions

## Comma Expressions

`(expr1, expr2, expr3, ..., exprn)` evaluates each expression from left to right and returns the value of the last expression.

**OPERANDS**: Multiple expressions separated by commas.
**RETURN VALUE**: The value of the comma expression is the value of the last expression.

```C++
int x = (1, 2, 3, 4, 5); // x = 5
int y = 6, z = 7;
int v = (x = 10, y + 10); // v = 16, x = 10

for (int i = 0, j = 10; i < j; i++, j--){} // multiple initialization and increment/decrement
c = (a < b) ? (a++, b++) : (a--, b--); // returns either b++ or b--, c is always b
int result = add_two_numbers (10, (a = 10, a + 3)); // call function with (10, 13)
```

**Others** Javascript also has the same semantics. Go and Python do not have the comma operator.

## Function Call Expressions

`function_name(arguments)` calls the function with the given arguments.
In C++, functions can only return one value.

**OPERANDS**: Function name and arguments.
**RETURN VALUE**: The return value of the function.

**Others** Javascript also has the same semantics.
Python returns comma separated values as a tuple, and can return variable number of values, (conditional returns).
Go returns multiple values, but always the same number of values.

## Assigmnet Expressions

`=` assigns the value of the right-hand side to the left-hand side.
Right hand side is evaluated first, then assigned to the left-hand side.

**OPERANDS**: lvalue and rvalue. lvalue is a variable or expression referring to memory location, rvalue is an expression.
Lvalue and rvalue must have the same type.
**RETURN VALUE**: The value that was assigned to the left-hand side.

```C++
int x = 10;
int a = b = c = x; // a = 10, b = 10, c = 10, from right to left
int y = (x = 20); // y = 20, x = 20
int z  = (x = 30, y = 40); // z = 40, x = 30, y = 40
```

**Others** Javascript has the same semantics. Python assigment expression uses `:=` operator. Same semantics as C++.
Go does not have the assignment expressions.(a = b = 10, not valid)

## Pre and Post Increment/Decrement Operators

`++` and `--` are unary operators that increment or decrement the value of the operand by 1.
**RETURN VALUE**: The value of the operand before or after the increment/decrement.
Pre-increment: `++x` increments x by 1 and returns the new value of x.
Post-increment: `x++` returns the current value of x and then increments x by 1.

**Others** Javascript has the same semantics.
Python does not have pre-increment/decrement operators.
Go does not support pre-increment/decrement operators.
Post-increment/decrement operators are only supported in statements. (x++ is valid, not ++x)

````C++

## Conditional Operator `? :`

`? :` is a ternary operator that takes three operands.
**OPERANDS** The first operand is a condition, the second is the value returned if the condition is true,
and the third is the value returned if the condition is false.

```C++
int a = 1, b = 2;
int z = (a > b) ? a : b; // z  = 2
````

**Others** Javascript has the same semantics. Python uses `if else` statement.
Go does not have the conditional operator. Use traditional `if else` statement.

```Python
z = a if a > b else b
```

## Logical Operators and Short-Circuit Evaluation

`&&` returns true if both operands are true, otherwise false.
If the first operand is false, the second operand is not evaluated.

`||` returns true if at least one of the operands is true, otherwise false.
If the first operand is true, the second operand is not evaluated.

**OPERANDS**: Expressions that evaluates to bool.

- ints - (Non zero is true, zero is false)
- pointers - (Non-null is true, null is false)
- User defined types - must have the `operator bool()` defined.

**RETURN VALUE**: bool.

**Others** Javascript and Go has the same semantics. Python uses `and`, `or` operators.
All have short-circuit evaluation.

## Bitwise Operators

`&`, `|`, `^`, `~`, `<<`, `>>` are bitwise operators that operate on integer operands at the bit level.
`>>` preserves the sign bit when shifting right, if positive, fills with 0, if negative, fills with 1.

**Others** Same semantics in other languages.
Go also has `&^` operator for bitwise AND NOT.
Javascript also has `>>>` operator for unsigned right shift, fills with 0 no matter the sign.

```C++
let x = 8; //00000000 00000000 00000000 00001000
let y = -8; //11111111 11111111 11111111 11111000 (in two's complement)

console.log(x >>> 2); // Output: 2, 00000000 00000000 00000000 00000010
console.log(y >>> 2); // Output: 1073741822, Binary: 00111111 11111111 11111111 11111110
```

## Relational Operators

`==`, `!=`, `>`, `<`, `>=`, `<=` are relational operators that compare two operands.

**RETURN VALUE**: bool.
**Others** Same semantics in other languages. Python allows for chaining of relational operators.

```Python
if 0 < x < 10:
    print("x is between 0 and 10")
res = a < b < c # same as (a < b) and (b < c)
```

## Arithmetic Operators

`+`, `-`, `*`, `/`, `%` are arithmetic operators that perform addition, subtraction, multiplication, division, and modulus.

**RETURN VALUE**: The result of the operation.

**Others** Same semantics in other languages.
Python has floor division `//` and exponentiation `**` operators.
Javascript has `**` operator for exponentiation.
