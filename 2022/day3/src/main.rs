//Written by Adam Klindworth
//Solves day 3 of the Advent of Code 2022

//use std::io::prelude::*;
use std::io::BufRead;
use std::io::BufReader;
use std::fs::File;

pub fn find_common2(s1: &str, s2: &str) -> char
{
    for c in s1.chars() {
        if s2.contains(c) {
            return c;
        }
    }
    return 'a';
}

pub fn char_to_item_priority(c:char) -> u32
{
    let alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return (alpha.find(c).expect("Invalid value; impossible") + 1).try_into().unwrap();
}

pub fn part_one()
{
    let f = File::open("data/input.txt").expect("file not found");
    let reader = BufReader::new(f);

    let mut total_priority:u32 = 0;

    for line in reader.lines()
    {
        let s_line = line.expect("Unlikely error");
        //println!("{}", s_line);
        let first_half = &s_line[0..s_line.len()/2];
        let second_half = &s_line[s_line.len()/2..s_line.len()];

        let common_char = find_common2(first_half, second_half);

        let priority = char_to_item_priority(common_char);

        total_priority += priority;
    }
    println!("Priority: {}", total_priority);

    f.close();
}

pub fn part_two()
{
    let f = File::open("data/input.txt").expect("file not found");

    f.close();
}

fn main() 
{
    part_one();
    part_two();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_priority_value()
    {
        assert_eq!(char_to_item_priority('L'), 38);
        assert_eq!(char_to_item_priority('p'), 16);
    }

    #[test]
    fn test_common2_strings()
    {
        assert_eq!(find_common2("abcdefgh", "ijklmnoep"), 'e');
        assert_eq!(find_common2("vJrwpWtwJgWr", "hcsFMMfFFhFp"), 'p');
    }
}
