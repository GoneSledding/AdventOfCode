use std::fs::File;
use std::io::Read;

pub fn find_nonrepeating_characters(input_string:&str, marker_length:usize) -> usize
{
    let mut marker_string:Vec<char> = Vec::<char>::new();
    let mut offset:usize = 0;

    for c in input_string.chars()
    {
        if marker_string.len() < marker_length
        {
            //Remove the first item from the vector until we no longer have the current character in it anymore
            while marker_string.contains(&c)
            {
                marker_string.remove(0);
            }
            //Now that the current character is not in the vector, add it to the end
            marker_string.push(c);
        }
        
        // We have the right length in our vector, which means that our string should have all unique characters as well
        if marker_string.len() == marker_length
        {
            return offset+1;
        }

        offset += 1;
    }
    return 0;
}

//Solve part one where we're trying to find the first time that 4 characters are in the buffer that do not repeat
pub fn part_one()
{
    let mut f = File::open("data/input.txt").expect("file not found");
    let mut input_data:String = String::new();
    f.read_to_string(&mut input_data);
    let marker:usize = find_nonrepeating_characters(input_data.as_str(), 4);
    println!("Part one: {}", marker);
}

//This time we need to find 14 characters in a row, marking the start of a message
pub fn part_two()
{
    let mut f = File::open("data/input.txt").expect("file not found");
    let mut input_data:String = String::new();
    f.read_to_string(&mut input_data);
    let marker:usize = find_nonrepeating_characters(input_data.as_str(), 14);
    println!("Part two: {}", marker);
}

fn main() {
    part_one();
    part_two();
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_find_nonrepeating_characters()
    {
        assert_eq!(find_nonrepeating_characters("bvwbjplbgvbhsrlpgdmjqwftvncz", 4), 5);
        assert_eq!(find_nonrepeating_characters("nppdvjthqldpwncqszvftbrmjlhg", 4), 6);
        assert_eq!(find_nonrepeating_characters("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 4), 10);
        assert_eq!(find_nonrepeating_characters("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 4), 11);

        assert_eq!(find_nonrepeating_characters("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 14), 19);
        assert_eq!(find_nonrepeating_characters("bvwbjplbgvbhsrlpgdmjqwftvncz", 14), 23);
        assert_eq!(find_nonrepeating_characters("nppdvjthqldpwncqszvftbrmjlhg", 14), 23);
        assert_eq!(find_nonrepeating_characters("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 14), 29);
        assert_eq!(find_nonrepeating_characters("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 14), 26);
    }
}