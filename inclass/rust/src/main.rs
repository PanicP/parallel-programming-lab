extern crate rayon;

const N: usize = 1_000_000_000;
const W: f64 = 1f64 / (N as f64);
fn f(x: f64) -> f64 {
    4.0 / (1.0 + x * x)
}

fn main() {
    use rayon::prelude::*;
    let sum: f64 = (0..N)
        .into_iter()
        .map(|i| f(W * ((i as f64) + 0.5)))
        .sum::<f64>();
    println!("pi = {}", W * sum);
}
