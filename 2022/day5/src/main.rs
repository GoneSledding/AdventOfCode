use std::io::BufRead;
//use std::io::BufReader;
use std::fs::File;
use std::io::Read;

//Structure that describes each move being made
pub struct Rearrangement
{
    quantity:usize,
    from:usize,
    to:usize,
}

//Parse the rearrangements, basically the lines that start with 'move' to move crates from one stack to another
pub fn parse_rearrangement(input_str:&str) -> Rearrangement
{
    let mut ret:Rearrangement = Rearrangement {quantity: 0, from: 0, to: 0};
    let split:Vec<&str> = input_str.split(' ').collect();
    ret.quantity = split[1].parse::<usize>().unwrap();
    //Subtracting 1 for 0-base arrays
    ret.from = split[3].parse::<usize>().unwrap() - 1;
    ret.to = split[5].parse::<usize>().unwrap() - 1;

    return ret;
}

//Parse the input stack and cargo coming in as input
pub fn parse_stack(input_str:&str) -> Vec<Vec<char>>
{
    let mut stack_arr:Vec<Vec<char>> = Vec::new();

    //First need to determine how many stacks there are
    //This is determined largely by the longest line length, so we find that first
    let mut max_line_len:usize = 0;
    for line in input_str.split('\n')
    {
        max_line_len = if line.len() > max_line_len { line.len() } else { max_line_len };
    }

    let num_stacks = max_line_len/4+1;

    //Create the vectors for each stack
    for _i in 0..num_stacks
    {
        stack_arr.push(Vec::<char>::new());
    }

    //Second time through the loop to actually populate the stacks
    for line in input_str.split('\n')
    {
        //Now go through each stack to see if there's anything there at this level
        for i in 0..num_stacks
        {
            let c = line.chars().nth(i*4+1).unwrap();
            //println!("Found the '{}' char at the {} stack", c, i);
            if c != ' '
            {
                stack_arr[i].push(c);
            }
        }
    }

    //Now reverse the stacks so that they are in the right 'stack' order
    for i in 0..stack_arr.len()
    {
        stack_arr[i].reverse();
    }

    return stack_arr;
}

//Wrapper to parse the entire input file into structures to be used later
pub fn parse_input_data(reader: &mut dyn BufRead) -> (Vec<Vec<char>>, Vec<Rearrangement>)
{
    let mut moves:Vec<Rearrangement> = Vec::new();
    let mut stack_input_string:String = String::new();

    for line in reader.lines()
    {

        let string_line = line.unwrap();
        let s_line:&str = string_line.as_str();
        if s_line.contains("move")
        {
            let cur_move:Rearrangement = parse_rearrangement(&s_line);
            moves.push(cur_move);
        }
        else if s_line.contains("[")
        {
            stack_input_string += &s_line;
            stack_input_string += "\n";
        }
    }
    stack_input_string.pop();

    //println!("Full stack string input: {}", stack_input_string);
    let starting_stack:Vec<Vec<char>> = parse_stack(stack_input_string.as_str());

    //println!("Number of rearrangements: {}", moves.len());

    return (starting_stack, moves);
}

//Make the specified move of the cargo
//The cargo should act just like a normal stack
pub fn move_cargo( mut stacks:Vec<Vec<char>>, movement:&Rearrangement) -> Vec<Vec<char>>
{
    for _i in 0..movement.quantity
    {
        let c:char = stacks[movement.from].pop().unwrap();
        stacks[movement.to].push(c);
    }

    return stacks;
}

//Make the specified move of the cargo, part two
//The cargo should stay in the same order that it was in the other stack
pub fn move_cargo2(mut stacks:Vec<Vec<char>>, movement:&Rearrangement) -> Vec<Vec<char>>
{
    let mut tmp_cargo:Vec<char> = Vec::<char>::new();
    for _i in 0..movement.quantity
    {
        let c:char = stacks[movement.from].pop().unwrap();
        tmp_cargo.push(c);
    }

    for _i in 0..movement.quantity
    {
        let c:char = tmp_cargo.pop().unwrap();
        stacks[movement.to].push(c);
    }

    return stacks;
}

pub fn part_one()
{
    let mut f = File::open("data/input.txt").expect("file not found");
    let mut input_data:String = String::new();
    f.read_to_string(&mut input_data);
    let mut buf = input_data.as_bytes();

    let (mut stacks, moves) = parse_input_data(&mut buf);

    for move_num in 0..moves.len()
    {
        stacks = move_cargo(stacks, &moves[move_num]);
    }

    print!("Part one: ");
    for i in 0..stacks.len()
    {
        print!("{}", stacks[i].pop().unwrap());
    }
    println!("");

}

pub fn part_two()
{
    let mut f = File::open("data/input.txt").expect("file not found");
    let mut input_data:String = String::new();
    f.read_to_string(&mut input_data);
    let mut buf = input_data.as_bytes();

    let (mut stacks, moves) = parse_input_data(&mut buf);

    for move_num in 0..moves.len()
    {
        stacks = move_cargo2(stacks, &moves[move_num]);
    }

    print!("Part two: ");
    for i in 0..stacks.len()
    {
        print!("{}", stacks[i].pop().unwrap());
    }
    println!("");
}

fn main() {
    part_one();
    part_two();
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_rearrangement_parsing()
    {
        let first_move:Rearrangement = parse_rearrangement("move 3 from 2 to 1");
        assert_eq!(first_move.quantity, 3);
        assert_eq!(first_move.from, 1);
        assert_eq!(first_move.to, 0);
    }

    #[test]
    fn test_stack_parsing()
    {
        let mut input_data:String = String::new();
        input_data += "    [D]    \n";
        input_data += "[N] [C]    \n";
        input_data += "[Z] [M] [P]";
        
        let mut stack_vec:Vec<Vec<char>> = parse_stack(input_data.as_str());

        assert_eq!(stack_vec[0].len(), 2);
        assert_eq!(stack_vec[0].pop().unwrap(), 'N');
        assert_eq!(stack_vec[0].pop().unwrap(), 'Z');

        assert_eq!(stack_vec[1].len(), 3);
        assert_eq!(stack_vec[1].pop().unwrap(), 'D');
        assert_eq!(stack_vec[1].pop().unwrap(), 'C');
        assert_eq!(stack_vec[1].pop().unwrap(), 'M');

        assert_eq!(stack_vec[2].len(), 1);
        assert_eq!(stack_vec[2].pop().unwrap(), 'P');
    }

    #[test]
    fn test_stack_rearranging()
    {
        let mut input_data:String = String::new();
        input_data += "    [D]    \n";
        input_data += "[N] [C]    \n";
        input_data += "[Z] [M] [P]\n";
        input_data += " 1   2   3 \n\n";
        input_data += "move 2 from 2 to 1\n";
        input_data += "move 1 from 3 to 2\n";


        let mut input_buf = input_data.as_bytes();
        let (stacks, moves) = parse_input_data(&mut input_buf);

        assert_eq!(moves[0].quantity, 2);
        assert_eq!(moves[0].from, 1);
        assert_eq!(moves[0].to, 0);

        let stacks = move_cargo(stacks, &moves[0]);

        assert_eq!(stacks[0].len(), 4);
        assert_eq!(stacks[1].len(), 1);
        assert_eq!(stacks[2].len(), 1);

        let stacks = move_cargo(stacks, &moves[1]);
        assert_eq!(stacks[0].len(), 4);
        assert_eq!(stacks[1].len(), 2);
        assert_eq!(stacks[2].len(), 0);
    }
}