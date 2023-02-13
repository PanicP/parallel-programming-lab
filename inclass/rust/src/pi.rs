const N: usize = 1_000_000_000;
const W: f64 = 1f64 / (N as f64);

fn f(x: f64) -> f64 {
    4.0 / (1.0 + x * x)
}

fn main() {
    let mut sum = 0.0;
    for i in 0..N {
        let x = W * ((i as f64) + 0.5);
        sum = sum + f(x);
    }
    println!("pi = {}", W * sum);
}
