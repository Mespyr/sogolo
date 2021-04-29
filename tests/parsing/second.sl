# Parsing Test 2.
# Functions called after other Functions,
# Functions called inside expressions,
# and ArgMaps

let x = list[1, 2, 3];
fn func[x, y] {
    println `Hello world`;
    println (+ x y);
}

append[func, x];
index[x, 3][2, 3];

fn square[x] {
    return (* x x);
}

let y = (+ square[12] square[13]);
let sqsq = square[square[12]];