
//Written by Adam Klindworth
//Solves day 2 part 1 of the Advent of Code 2022

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
        // X     Y       Z
        //Rock  Paper  Scissors
        // 1     2       3
        let line_vec:Vec<char> = line.chars().collect();

        if line_vec[2] == 'X' {
            score += 1;
            match line_vec[0] {
                'A' => score += 3,
                'B' => score += 0,
                'C' => score += 6,
                _ => println!("Invalid"),
            };
        }
        else if line_vec[2] == 'Y' {
            score += 2;
            match line_vec[0] {
                'A' => score += 6,
                'B' => score += 3,
                'C' => score += 0,
                _ => println!("Invalid"),
            };
        }
        else if line_vec[2] == 'Z' {
            score += 3;
            match line_vec[0] {
                'A' => score += 0,
                'B' => score += 6,
                'C' => score += 3,
                _ => println!("Invalid"),
            };
        }

        //println!("Current selection: {}", line_vec[2]);

     }
     println!("Score: {}", score);
    
}