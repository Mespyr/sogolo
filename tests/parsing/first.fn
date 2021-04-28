# Parsing test for Sogolo
# run this with the -p or --read_ast flag

let x = 12;
if (= x 12) {
    println `True!`;
}
else {
    println `False.`;
}

# nested statements
fn func[x, y, z] {
    println (+ x y z);
    println (- x y z);
    if (= (+ x y z) 10) {
        println `x + y + z = 10`;
    } 
    else {
        println `Done!`;
    }
}

func[4, 5, 6];