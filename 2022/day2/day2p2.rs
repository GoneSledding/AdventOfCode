
//Written by Adam Klindworth
//Solves day 2 part 2 of the Advent of Code 2022

use std::env;
use std::fs::File;
use std::io::prelude::*;

fn main()
{
    let args: Vec<String> = env::args().collect();

    let filename = &args[1];

    let mut f = File::open(filename).expect("file not found");

    let mut contents = String::new();
    f.read_to_string(&mut contents).expect("Something went wrong reading the file");

    let lines = contents.split("\n").collect::<Vec<_>>();

    //println!("With text:\n{}", contents);
    println!("Number of lines:\n{}", lines.len());

    let mut score:u64 = 0;
    for line in lines {
        // A     B       C
        //Rock  Paper  Scissors
        // 1     2       3
        // X = lose (0), Y = draw (3), Z = win (6)
        let line_vec:Vec<char> = line.chars().collect();

        if line_vec[0] == 'A' {
            match line_vec[2] {
                'X' => score += 3,
                'Y' => score += 4,
                'Z' => score += 8,
                _ => println!("Invalid"),
            };
        }
        else if line_vec[0] == 'B' {
            match line_vec[2] {
                'X' => score += 1,
                'Y' => score += 5,
                'Z' => score += 9,
                _ => println!("Invalid"),
            };
        }
        else if line_vec[0] == 'C' {
            match line_vec[2] {
                'X' => score += 2,
                'Y' => score += 6,
                'Z' => score += 7,
                _ => println!("Invalid"),
            };
        }

        //println!("Current selection: {}", line_vec[2]);

     }
     println!("Score: {}", score);
    
}