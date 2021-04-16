# Third Parsing Test

decl test;
decl inside_list_func;

fn test[x, y] {
    return (+ (* x y) (/ x y));
}

let test_return = test[
    test[12, 13], 
    test[14, 15]
];

fn inside_list_func[x] {
    return test[x, x];
}
decl ls = list[inside_list_func];

decl inner = test[
    index[ls, 0][12], test_return
];

println test_return;