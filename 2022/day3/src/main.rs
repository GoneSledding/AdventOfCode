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

pub fn find_common3(s1: &str, s2: &str, s3: &str) -> char
{
    for c1 in s1.chars()
    {
        for c2 in s2.chars()
        {
            if s3.contains(c1) && s3.contains(c2) && c1 == c2
            {
                return c1;
            }
        }
    }
    return '0';
}

pub fn char_to_item_priority(c:char) -> u32
{
    let alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return (alpha.find(c).expect("Invalid value") + 1).try_into().unwrap();
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
}

pub fn part_two()
{
    let f = File::open("data/input.txt").expect("file not found");
    let reader = BufReader::new(f);

    let mut total_badge_priorities = 0;
    let mut line_num = 0;
    let mut line_1 = String::new();
    let mut line_2 = String::new();
    let mut line_3 = String::new();

    for line in reader.lines()
    {
        if line_num % 3 == 0
        {
            line_1 = line.unwrap();
        }
        else if line_num % 3 == 1
        {
            line_2 = line.unwrap();
        }
        else if line_num % 3 == 2
        {
            line_3 = line.unwrap();
        }

        if line_num % 3 == 2
        {
            let badge = find_common3(line_1.as_str(), line_2.as_str(), line_3.as_str());

            total_badge_priorities += char_to_item_priority(badge);

            line_1.clear();
            line_2.clear();
            line_3.clear();
        }

        line_num += 1;
    }

    println!("Badge Priorities: {}", total_badge_priorities);
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

    #[test]
    fn test_common3_strings()
    {
        assert_eq!(find_common3("vJrwpWtwJgWrhcsFMMfFFhFp", "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL", "PmmdzqPrVvPwwTWBwg"), 'r');
        assert_eq!(find_common3("wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn", "ttgJtRGJQctTZtZT", "CrZsJsPPZsGzwwsLwLmpwMDw"), 'Z');
    }
}
