use std::io::BufRead;
use std::fs::File;
use std::io::Read;

mod command_interpreter
{
    use super::*;

    #[derive(Debug, PartialEq)]
    enum ObjectType
    {
        Directory,
        File,
    }

    #[derive(Debug)]
    pub struct Object
    {
        path:String,
        obj_name:String,
        obj_type:ObjectType,
        file_size:usize,
    }

    #[derive(Debug)]
    pub struct Interpreter
    {
        pub filesystem:Vec::<Object>,
        pub current_path:String,
    }

    impl Interpreter {
        //Process the command "cd" 
        pub fn change_directory(&mut self, command:&str)
        {
            let mut new_path:String = String::new();

            new_path += self.current_path.as_str();
    
            let split_command:Vec<&str> = command.trim().split(" ").collect();
            //let cd_command:&str = &split_command[0];
            let change_path:&str = &split_command[1];
            //println!("changing to the relative path {}", change_path);

            if change_path.eq("..") {
                //Pop off the '/' at the end of the current path, only if we're not at the '/' level
                if !new_path.eq("/") {
                    new_path.pop();
                }

                while new_path.chars().nth(new_path.len() - 1).unwrap() != '/'
                {
                    new_path.pop();
                }
            } else if change_path.eq("/") {
                new_path = "/".to_string();
            } else {
                new_path.push_str(&change_path);
                new_path.push('/');
            }

            self.current_path = new_path;

        }

        //Returns what kind of object is being referred to by a path
        fn path_objtype(&self, path:&str) -> ObjectType
        {
            if path.ends_with("/") {
                return ObjectType::Directory;
            } else {
                return ObjectType::File;
            }
        }

        //Takes a path in and returns whether it exists in our directory tree
        pub fn path_exists(&self, path:&str) -> bool
        {
            let search_objtype = self.path_objtype(path);
            let mut path_split:Vec<&str> = path.trim_end_matches("/").split("/").collect();

            let search_objname = path_split[path_split.len()-1];
            path_split.pop();
            let tmp_binding = path_split.join("/");
            let mut tmp_search_path:String = String::new();

            tmp_search_path += tmp_binding.as_str();
            tmp_search_path += "/";
            let search_path:&str = tmp_search_path.as_str();
            //println!("Searching for objname: {} at \"{}\"", search_objname, search_path);
            
            for obj in &self.filesystem {

                if search_objtype == obj.obj_type && search_objname == obj.obj_name && search_path.eq(obj.path.as_str()) {
                    return true;
                }

            }

            return false;
        }

        //Find the total size of a Directory
        pub fn directory_size(&self, directory:&str) -> usize
        {
            let mut dir_size:usize = 0;

            for obj in &self.filesystem {
                if obj.path.starts_with(directory) && obj.obj_type == ObjectType::File {
                    dir_size += obj.file_size;
                }
            }
            return dir_size;
        }

        //Counts up all used space in the filesystem
        pub fn find_total_used_space(&self) -> usize
        {
            let mut used_space:usize = 0;
            for obj in &self.filesystem {
                if obj.obj_type == ObjectType::File {
                    used_space += obj.file_size;
                }
            }
            return used_space;
        }

        //Find all directories less than 100000, add them all together
        //This has some bugs that would make it not able to work in reality, but 
        //maybe it's good enough for this particular event
        pub fn add_small_directories(&self) -> usize
        {
            let mut added_size:usize = 0;

            let root_size:usize = self.directory_size("/");
            //println!("The '/' directory has size {}", root_size);
            for obj in &self.filesystem {
                if obj.obj_type == ObjectType::Directory {
                    let mut dir_name:String = String::new();
                    dir_name += obj.path.as_str();
                    dir_name += obj.obj_name.as_str();
                    dir_name += "/";
                    let dir_size:usize = self.directory_size(dir_name.as_str());
                    //println!("The directory {} has a size of {}", dir_name, dir_size);
                    if dir_size <= 100000 {
                        //println!("Found a small directory: ({})! Size: {}", dir_name, dir_size);
                        added_size += dir_size;
                    }
                }
            }
            return added_size;
        }

        //Find the smallest directory that could be deleted to free up
        //bytes on the disk
        pub fn find_smallest_directory_above_value(&self, deletion_needed:usize) -> usize
        {
            let mut smallest_directory:usize = 70000000;

            for obj in &self.filesystem {
                if obj.obj_type == ObjectType::Directory {
                    let mut dir_name:String = String::new();
                    dir_name += obj.path.as_str();
                    dir_name += obj.obj_name.as_str();
                    dir_name += "/";
                    let dir_size:usize = self.directory_size(dir_name.as_str());
                    if dir_size > deletion_needed && dir_size < smallest_directory {
                        smallest_directory = dir_size;
                    }
                }
            }

            return smallest_directory;
        }

        //============== BEGIN FORMAT ============
        //ls
        //dir a
        //14848514 b.txt
        //8504156 c.dat
        //dir d
        //=============== END FORMAT =============
        //Process the command "ls", adding new files and directories to our filesystem
        pub fn list_directory(&mut self, command_output:&str)
        {
            //println!("Listing directories");

            let output_lines:Vec<&str> = command_output.split("\n").collect();
            for line_num in 1..output_lines.len() {
                //dbg!(output_lines[line_num]);
                
                let object_output_line:Vec<&str> = output_lines[line_num].split(" ").collect();
                let new_first_arg = object_output_line[0];
                let new_filename = object_output_line[1];
                let mut full_path:String = String::new();
                full_path += self.current_path.as_str();
                full_path += new_filename;
            
                if self.path_exists(full_path.as_str()) {
                    //println!("Path already exists!!");
                    continue;
                }
            
                if new_first_arg.eq("dir") {
                    let newobj:Object = Object {path:self.current_path.as_str().to_string(), obj_name:new_filename.to_string(),
                    obj_type:ObjectType::Directory, file_size:0};
                    self.filesystem.push(newobj);
                } else {
                    let newobj:Object = Object {path:self.current_path.as_str().to_string(), obj_name:new_filename.to_string(),
                    obj_type:ObjectType::File, file_size:new_first_arg.parse::<usize>().unwrap()};
                    self.filesystem.push(newobj);
                }
            }

        }


        //Parse the input enough in here to get it into commands and their associated output
        //as one str to send to the actual methods for processing those commands
        pub fn handle_input(&mut self, reader: &mut dyn BufRead)
        {
            let mut buffer:String = String::new();
            
            for line in reader.lines() {
                let string_line = line.unwrap();
                let s_line:&str = string_line.as_str();
                //println!("{}", s_line);
                if string_line.starts_with("$") && buffer.len() > 0 {
                    self.list_directory(buffer.trim());
                    buffer.clear();
                }

                if !s_line.starts_with("$") {
                    buffer.push('\n');
                    buffer.push_str(s_line);
                }

                if s_line.starts_with("$ cd") {
                    self.change_directory(s_line.trim_start_matches("$").trim());
                } else if s_line.starts_with("$ ls") {
                    buffer.push_str("ls");
                }
            }
            //dbg!(&self.filesystem);
        }
    }
}


pub fn part_one()
{
    let mut f = File::open("data/input.txt").expect("file not found");
    let mut input_data:String = String::new();
    if !f.read_to_string(&mut input_data).is_ok() {
        println!("Failed to read to string");
        return;
    }
    let mut buf = input_data.as_bytes();
    //dbg!(buf);
    
    let mut interpreter = command_interpreter::Interpreter {
        filesystem: Vec::<command_interpreter::Object>::new(),
        current_path: String::new(),
    };

    interpreter.handle_input(&mut buf);

    println!("Part one: {}", interpreter.add_small_directories());
    
}

pub fn part_two()
{
    let mut f = File::open("data/input.txt").expect("file not found");
    let mut input_data:String = String::new();
    if f.read_to_string(&mut input_data).is_ok() != true {
        println!("Failed to read to string");
        return;
    }
    let mut buf = input_data.as_bytes();

    let mut interpreter = command_interpreter::Interpreter {
        filesystem: Vec::<command_interpreter::Object>::new(),
        current_path: String::new(),
    };

    interpreter.handle_input(&mut buf);

    let total_used_space = interpreter.find_total_used_space();

    println!("Used space on disk: {}", total_used_space);
    let free_space:usize = 70000000-total_used_space;
    println!("Free space on disk: {}", free_space);
    let deletion_needed:usize = 30000000-free_space;
    println!("Deletion needed for update: {}", deletion_needed);

    println!("Part two: {}", interpreter.find_smallest_directory_above_value(deletion_needed));
    println!("");
}

fn main() {
    part_one();
    part_two();
}


#[cfg(test)]
mod tests {
    use super::*;

    //Test that our parser can recognize the object in an 'ls' command


    //Test a series of 'cd' commands
    #[test]
    fn test_cd_commands()
    {
        let mut interpreter = command_interpreter::Interpreter {
            filesystem: Vec::<command_interpreter::Object>::new(),
            current_path: String::new(),
        };
        
        interpreter.change_directory("cd /\n");
        assert_eq!(interpreter.current_path, "/");
        interpreter.change_directory("cd a\n");
        assert_eq!(interpreter.current_path, "/a/");
        interpreter.change_directory("cd b\n");
        assert_eq!(interpreter.current_path, "/a/b/");
        interpreter.change_directory("cd ..\n");
        assert_eq!(interpreter.current_path, "/a/");
    }

    //Test a series of 'ls' commands, in the process also tests if the method to
    //checking if a valid path exists for a file works
    #[test]
    fn test_ls_commands()
    {
        let mut interpreter = command_interpreter::Interpreter {
            filesystem: Vec::<command_interpreter::Object>::new(),
            current_path: String::new(),
        };

        interpreter.change_directory("cd /\n");
        assert_eq!(interpreter.path_exists("/a/"), false);
        assert_eq!(interpreter.path_exists("/b.txt"), false);
        assert_eq!(interpreter.path_exists("/c.dat"), false);
        assert_eq!(interpreter.path_exists("/d/"), false);
        interpreter.list_directory("ls\ndir a\n14848514 b.txt\n8504156 c.dat\ndir d");
        //dbg!(&interpreter);
        assert_eq!(interpreter.path_exists("/a/"), true);
        assert_eq!(interpreter.path_exists("/b.txt"), true);
        assert_eq!(interpreter.path_exists("/c.dat"), true);
        assert_eq!(interpreter.path_exists("/d/"), true);
        interpreter.change_directory("cd a\n");
        assert_eq!(interpreter.path_exists("/a/e/"), false);
        assert_eq!(interpreter.path_exists("/a/f"), false);
        assert_eq!(interpreter.path_exists("/a/g"), false);
        assert_eq!(interpreter.path_exists("/a/h.lst"), false);
        interpreter.list_directory("ls\ndir e\n29116 f\n2557 g\n62596 h.lst");
        //dbg!(&interpreter);
        assert_eq!(interpreter.path_exists("/a/e/"), true);
        assert_eq!(interpreter.path_exists("/a/f"), true);
        assert_eq!(interpreter.path_exists("/a/g"), true);
        assert_eq!(interpreter.path_exists("/a/h.lst"), true);
        interpreter.change_directory("cd ..\n");
        assert_eq!(interpreter.path_exists("/e/"), false);
        assert_eq!(interpreter.path_exists("/f"), false);
        assert_eq!(interpreter.path_exists("/g"), false);
        assert_eq!(interpreter.path_exists("/h.lst"), false);
        interpreter.list_directory("ls\ndir e\n4635463 f\n246557 g\n642 h.lst");
        dbg!(&interpreter);
        assert_eq!(interpreter.path_exists("/e/"), true);
        assert_eq!(interpreter.path_exists("/f"), true);
        assert_eq!(interpreter.path_exists("/g"), true);
        assert_eq!(interpreter.path_exists("/h.lst"), true);
    }

    //Test functionality to determine sizes of directories
    #[test]
    fn test_directory_size()
    {
        let mut interpreter = command_interpreter::Interpreter {
            filesystem: Vec::<command_interpreter::Object>::new(),
            current_path: String::new(),
        };

        interpreter.change_directory("cd /\n");
        interpreter.list_directory("ls\ndir a\n14848514 b.txt\n8504156 c.dat\ndir d");
        interpreter.change_directory("cd a\n");
        interpreter.list_directory("ls\ndir e\n29116 f\n2557 g\n62596 h.lst");
        interpreter.change_directory("cd e\n");
        interpreter.list_directory("ls\n584 i");
        interpreter.change_directory("cd ..\n");
        interpreter.change_directory("cd ..\n");
        interpreter.change_directory("cd d\n");
        interpreter.list_directory("ls\n4060174 j\n8033020 d.log\n5626152 d.ext\n7214296 k");
        assert_eq!(interpreter.directory_size("/a/e/"), 584);
        assert_eq!(interpreter.directory_size("/a/"), 94853);
        assert_eq!(interpreter.directory_size("/d/"), 24933642);
    }

    //Test functionality to sum up all directories where the size 
    //of all files contained within them is less than 100000
    #[test]
    fn test_add_small_directories()
    {
        let mut interpreter = command_interpreter::Interpreter {
            filesystem: Vec::<command_interpreter::Object>::new(),
            current_path: String::new(),
        };

        interpreter.change_directory("cd /\n");
        interpreter.list_directory("ls\ndir a\n14848514 b.txt\n8504156 c.dat\ndir d");
        interpreter.change_directory("cd a\n");
        interpreter.list_directory("ls\ndir e\n29116 f\n2557 g\n62596 h.lst");
        interpreter.change_directory("cd e\n");
        interpreter.list_directory("ls\n584 i");
        interpreter.change_directory("cd ..\n");
        interpreter.change_directory("cd ..\n");
        interpreter.change_directory("cd d\n");
        interpreter.list_directory("ls\n4060174 j\n8033020 d.log\n5626152 d.ext\n7214296 k");
        assert_eq!(interpreter.add_small_directories(), 95437);
    }
}
