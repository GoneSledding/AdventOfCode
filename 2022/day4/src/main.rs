use std::io::BufRead;
use std::io::BufReader;
use std::fs::File;
use std::str::FromStr;

pub fn range_to_minmax(input:&str) -> (u32, u32)
{
    let v:Vec<&str> = input.split('-').collect();
    let min:u32 = FromStr::from_str(v[0]).unwrap();
    let max:u32 = FromStr::from_str(v[1]).unwrap();

    return (min, max);
}

pub fn are_elves_fully_contained(elf_one_min:u32, elf_one_max:u32, elf_two_min:u32, elf_two_max:u32) -> bool
{
    if (elf_one_min <= elf_two_min && elf_one_max >= elf_two_max) || (elf_two_min <= elf_one_min && elf_two_max >= elf_one_max)
    {
        return true;
    }
    return false;
}

pub fn are_elves_overlapping(elf_one_min:u32, elf_one_max:u32, elf_two_min:u32, elf_two_max:u32) -> bool
{
    if (elf_one_min <= elf_two_max && elf_one_max >= elf_two_min) || (elf_two_min <= elf_one_max && elf_two_max >= elf_one_min)
    {
        return true;
    }
    return false;
}

//I started writing this, and it works for what it is meant to, but ended up not using it. 
pub fn range_to_vector(start: u32, end: u32) -> Vec<u32>
{
    let mut v:Vec<u32> = Vec::new();
    let mut i:u32 = start;
    while i <= end
    {
        v.push(i);
        i += 1;
    }
    return v;
}

pub fn part_one()
{
    let f = File::open("data/input.txt").expect("file not found");
    let reader = BufReader::new(f);

    let mut total_fully_contained:u32 = 0;

    for line in reader.lines()
    {
        let s_line = line.unwrap();
        let assignments_vec:Vec<&str> = s_line.split(',').collect();
        let elf_one:&str = assignments_vec[0];
        let elf_two:&str = assignments_vec[1];

        let elf_one_min:u32;
        let elf_one_max:u32;
        let elf_two_min:u32;
        let elf_two_max:u32;

        (elf_one_min, elf_one_max) = range_to_minmax(elf_one);
        (elf_two_min, elf_two_max) = range_to_minmax(elf_two);

        let b_is_contained = are_elves_fully_contained(elf_one_min, elf_one_max, elf_two_min, elf_two_max);
        if b_is_contained == true
        {
            total_fully_contained += 1;
        }
    }
    println!("Total fully contained: {}", total_fully_contained);

}

//There is so much duplication of effort here and really should be optimized, but 
//I'm not worried about it for the moment.
pub fn part_two()
{
    let f = File::open("data/input.txt").expect("file not found");
    let reader = BufReader::new(f);

    let mut total_overlapping:u32 = 0;

    for line in reader.lines()
    {
        let s_line = line.unwrap();
        let assignments_vec:Vec<&str> = s_line.split(',').collect();
        let elf_one:&str = assignments_vec[0];
        let elf_two:&str = assignments_vec[1];

        let elf_one_min:u32;
        let elf_one_max:u32;
        let elf_two_min:u32;
        let elf_two_max:u32;

        (elf_one_min, elf_one_max) = range_to_minmax(elf_one);
        (elf_two_min, elf_two_max) = range_to_minmax(elf_two);

        let b_is_overlapping = are_elves_overlapping(elf_one_min, elf_one_max, elf_two_min, elf_two_max);
        if b_is_overlapping == true
        {
            total_overlapping += 1;
        }
    }
    println!("Total overlapping: {}", total_overlapping);
}

fn main() {
    part_one();
    part_two();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_range_to_vec()
    {
        let v = range_to_vector(5, 10);

        assert_eq!(v.len(), 6);
        assert_eq!(v.contains(&5), true);
        assert_eq!(v.contains(&6), true);
        assert_eq!(v.contains(&7), true);
        assert_eq!(v.contains(&8), true);
        assert_eq!(v.contains(&9), true);
        assert_eq!(v.contains(&10), true);
    }

    #[test]
    fn test_range_to_vec_single()
    {
        let v = range_to_vector(7, 7);

        assert_eq!(v.len(), 1);
        assert_eq!(v.contains(&7), true);
    }

    #[test]
    fn test_range_to_minmax()
    {
        let min:u32;
        let max:u32;
        (min, max) = range_to_minmax("6-9");

        assert_eq!(min, 6);
        assert_eq!(max, 9);
    }

    #[test]
    fn test_elves_contained()
    {
        assert_eq!(are_elves_fully_contained(1, 5, 1, 3), true);
        assert_eq!(are_elves_fully_contained(3, 4, 1, 9), true);
        assert_eq!(are_elves_fully_contained(1, 5, 4, 8), false);
        assert_eq!(are_elves_fully_contained(1, 2, 4, 6), false);
    }

    #[test]
    fn test_elves_overlapping()
    {
        assert_eq!(are_elves_overlapping(3, 5, 1, 3), true);
        assert_eq!(are_elves_overlapping(1, 5, 5, 8), true);
        assert_eq!(are_elves_overlapping(1, 5, 8, 10), false);
        assert_eq!(are_elves_overlapping(9, 15, 4, 6), false);
    }

}