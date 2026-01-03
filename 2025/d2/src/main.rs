use std::env;
use std::fs::File;
use std::io::{self, BufRead, BufReader};

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Usage: {} <filename>", args[0]);
        std::process::exit(1);
    }
    let file = File::open(&args[1])?;
    let mut reader = BufReader::new(file);

    let mut first_line = String::new();
    if reader.read_line(&mut first_line)? == 0 {
        println!("File is empty.");
        return Ok(());
    }

    let mut total_p1_invalids: i64 = 0;

    // println!("Line: {}", first_line.trim_end());
    let parts: Vec<&str> = first_line.trim_end().split(',').collect();
    for part in parts {
        //println!("{}", part);
        let (start, end) = part.split_once('-').unwrap();
        // println!("Start: {}, End: {}", start, end);
        let starti: i64 = start.parse().unwrap();
        let endi: i64 = end.parse().unwrap();
        for current_value in starti..=endi {
            let str_value: String = current_value.to_string();
            if str_value.len() % 2 != 0 {
                continue;
            }
            let fhalf = &str_value[..str_value.len() / 2];
            let shalf = &str_value[str_value.len() / 2..];
            let ifhalf:i64 = fhalf.parse::<i64>().unwrap();
            let ishalf:i64 = shalf.parse::<i64>().unwrap();
            if ifhalf == ishalf {
                // println!("Found invalid value P1: {}", current_value);
                total_p1_invalids += current_value;
            }
        }
    }

    let mut total_p2_invalids:i64 = 0;

    let parts: Vec<&str> = first_line.trim_end().split(',').collect();
    for part in parts {
        let (start, end) = part.split_once('-').unwrap();
        let starti: i64 = start.parse().unwrap();
        let endi: i64 = end.parse().unwrap();
        for current_value in starti..=endi {
            let str_value: String = current_value.to_string();
            let half_length = str_value.len() / 2;
            // only need to go to half the length because it can't repeat if the length is more than half
            let mut is_invalid: bool = false;
            for current_length in 1..=half_length {
                if str_value.len() % current_length != 0 {
                    continue;
                }
                let fpart = &str_value[..current_length];
                
                for i in 2..=str_value.len()/current_length {
                    let spart = &str_value[current_length*(i-1)..current_length*i];
                    // println!("Comparing {} to {}", fpart, spart);
                    if fpart != spart {
                        break;
                    }
                    if i == str_value.len()/current_length {
                        is_invalid = true;
                    }
                }
            }
            if is_invalid==true {
                println!("Found invalid value P2: {}", current_value);
                total_p2_invalids += current_value;
            }
        }
    }

    println!("Total invalids P1: {}", total_p1_invalids);
    println!("Total invalids P2: {}", total_p2_invalids);

    Ok(())
}