# Parsing

To parse an expression node that looks like this:
```lisp
(+ 2 func[1, 2])
```
what we would do is first loop through all the nodes in the expression, and append them to a vector. When we reach a ArgMap node (anything between `[` and `]`), we check if the vector size is greater that 0. If it is, we get the last value on the vector, and put it with the ArgMap to form a new expression. After parsing, the node would look like this:
```lisp
(+ 2 (func [1 2]))
```

This also works with nodes that look like this:
```lisp
(+ 10 index[1][2, 3])
```

It would make an AST like this:
```lisp
(+ 10 
    ((index [1]) 
        [2 3]))
```