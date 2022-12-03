
//Written by Adam Klindworth
//Solves day 3 part 1 of the Advent of Code 2022

use std::env;
use std::fs::File;
use std::io::prelude::*;
use std::convert::TryInto;

fn find_duplicate(first:Vec<char>, second:Vec<char>) -> char
{
    for c in first {
        if second.contains(&c) {
            return c;
        }
    }
    return 'a';
}

fn convert_char_to_value(c:char) -> u32
{
    let alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return (alpha.find(c).expect("Invalid value; impossible") + 1).try_into().unwrap();
}

fn main()
{
    let args: Vec<String> = env::args().collect();

    let filename = &args[1];

    let mut f = File::open(filename).expect("file not found");

    let mut contents = String::new();
    f.read_to_string(&mut contents).expect("Something went wrong reading the file");

    let lines = contents.split("\n").collect::<Vec<_>>();

    //println!("With text:\n{}", contents);
    //println!("Number of lines:\n{}", lines.len());

    let mut score:u32 = 0;

    for line in lines {
        let mut line_vec:Vec<char> = line.chars().collect();
        if line_vec.len() % 2 == 1 {
            line_vec.remove(line_vec.len()-1);
        }

        //println!("Length of line: {}", line_vec.len());

        let first_half = &line_vec[0..line_vec.len()/2];
        let second_half = &line_vec[line_vec.len()/2..line_vec.len()];

        //println!("First half: {}", first_half.len());
        //println!("Second half: {}", second_half.len());

        let dup_char = find_duplicate(first_half.to_vec(), second_half.to_vec());
        //println!("Duplicate character value: {}", dup_char);
        let dup_value = convert_char_to_value(dup_char);
        //println!("Duplicate value: {}", dup_value);
        
        score += dup_value;
    }
    
     println!("Score: {}", score);
    
}