# Evaluation

Lets say we have this program:
```perl
dec x;
read x;
if (= x `Hello`) {
    println `Hello to you too!`;
}
else {
    println x;
}
```
Once it is parsed, the AST would look like this:
```
[dec x]
[read x]
[if (= x `Hello`)  {
    [println `Hello to you too!`]
} 
else {
    [println x]
}]
```

To evaluate this, what we would do is pop of the top value, and do something with that until the AST is empty. For this AST, we would first pop of `[dec x]`, which would declare a new variable called `x`. Then we would pop off `[read x]` which would read from the input stream and save that value to `x`. Then we reach the if statement.

## If Statements

For the if statement, we first check if `x` equals `Hello`. If it does, what we do is we take all the values in the statement next to it, and push it onto the AST stack.

So the stack would then look like:
```
[println `Hello to you too!`]
```

We would do the same thing if `x` didn't equal `Hello`. We would take all the lines in the else statement, and push them onto the stack.

Then, the stack would look like:

```
[println x]
```
This would eliminate some of the recursion in the code, making it faster.

## For and While Loops

The same would be for `while` loops. For example, if we have the code:
```perl
dec input;
while (!= input `The secret code!`)
{
    read input;
    if (!= input `The secret code!`)
    {
        println format[input ` is wrong!`];
    }
};
println `You got it correct!`;
```

what would happen is the `dec input;` would first be evaluated, setting `input` to `0`. When we go to the while loop, initially, `input` doesn't equal `The secret code!` so then we would push this node back onto the stack, and then push all of it's lines onto the stack after it, so the stack would look like this:
```
[read input]
[if (!= input `The secret code!`) 
{
    [println [format input ` is wrong!`]]
}]
[while (!= input `The secret code!`) 
{
    [read input]
    [if (!= input `The secret code!`) 
    {
        [println [format input ` is wrong!`]]
    }]
}]
[println `You got it correct!`]
```

We would evaluate all of the nodes, until we reached the `while` loop again. Then we would check if the condition is false, and if it is, we would skip the node, and move on. If it isn't false, we would repeat the previous steps.