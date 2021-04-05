# Design

## Expressions and Comparisons

`edulo` uses Polish Notation for expressions and comparisons. Expressions are indicated by 
parentheses surrounding them. For example:
```lisp
(+ 2 2)
```
is equal to four. The expressions can also be nested in each other. For example:
```lisp
(* 2 (+ 4 5 (- 10 7)))
```
is the equivilant of `2 * (4 + 5 + (10 - 7))` in other languages.

## Functions 

`edulo` uses brackets to indicate the calling of a function. For example:
```ruby
func[2 3];
```
is calling the function `func` and passing the arguments `2` and `3`.

## Keywords

- `dec`     - Declare a variable that points to a certain address.
- `let`     - Set a declared variable to a value.
- `print`   - Print a value.
- `println` - Print a value with a trailing newline.