using System;
using System.IO;
using System.Collections;

namespace d5
{
    internal class Program
    {
        static int Main(string[] args)
        {
            if (args == null || args.Length == 0)
            {
                Console.Error.WriteLine("Usage: <program> <path-to-file>");
                return 1;
            }

            var path = args[0];

            try
            {
                int fresh_p1 = CheckForFreshness(path);
                Console.WriteLine("Part 1: " + fresh_p1);
                Console.WriteLine("Part 2: " + ConsolidateIngredientIDs(path));
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine("Error: " + ex.Message);
                return 1;
            }

            return 0;
        }

        static List<Tuple<Int64, Int64>> ConsolidateRanges(List<Tuple<Int64, Int64>> ranges)
        {
            List<Tuple<Int64, Int64>> merged_ranges = new List<Tuple<Int64, Int64>>();

            // Now process the ingredient IDs
            foreach (Tuple<Int64, Int64> range in ranges)
            {
                bool merged = false;
                Int64 start = range.Item1;
                Int64 end = range.Item2;
                if (merged_ranges.Count == 0)
                {
                    merged_ranges.Add(new Tuple<Int64, Int64>(start, end));
                }
                else
                {
                    //Need to check if the new range overlaps with any existing ranges
                    foreach (Tuple<Int64, Int64> existing_range in merged_ranges)
                    {
                        if ((start <= existing_range.Item1 && end >= existing_range.Item1) ||
                            (end >= existing_range.Item2 && start <= existing_range.Item2) ||
                            (start >= existing_range.Item1 && end <= existing_range.Item2))
                        {
                            //They overlap, so we need to merge them
                            start = Math.Min(start, existing_range.Item1);
                            end = Math.Max(end, existing_range.Item2);
                            merged_ranges.Remove(existing_range);
                            merged_ranges.Add(new Tuple<Int64, Int64>(start, end));
                            merged = true;
                            break;
                        }
                    }
                    if (merged == false)
                    {
                        merged_ranges.Add(new Tuple<Int64, Int64>(start, end));
                    }
                }
            }
            return merged_ranges;
        }

        static Int64 ConsolidateIngredientIDs(string path)
        {
            Int64 total_valid_ids = 0;
            if(!File.Exists(path))
            {
                throw new FileNotFoundException("The specified file does not exist.", path);
            }

            string? line;

            List<Tuple<Int64, Int64>> ranges = new List<Tuple<Int64, Int64>>();
            using StreamReader reader = new StreamReader(path);
            while ((line = reader.ReadLine()) is not null)
            {
                line = line.Trim();
                if (line == string.Empty)
                {   //That's all we needed to get from the file this time
                    break;
                }
                string[] parts = line.Split('-', StringSplitOptions.RemoveEmptyEntries);
                if (parts.Length != 2)
                {
                    throw new FormatException($"Invalid range format: {line}");
                }
                if (!Int64.TryParse(parts[0], out Int64 start) || !Int64.TryParse(parts[1], out Int64 end))
                {
                    throw new FormatException($"Invalid integers in range: {line}");
                }
                ranges.Add(new Tuple<Int64, Int64>(start, end));
            }

            //Consolidate the lists until there is no change
            while(true)
            {
                int current_count = ranges.Count;
                ranges = ConsolidateRanges(ranges);
                Console.WriteLine("Consolidation pass complete. Ranges count: " + ranges.Count);
                if(ranges.Count == current_count)
                {
                    break;
                }
            }

            //Now calculate the total number of valid IDs
            foreach (Tuple<Int64, Int64> range in ranges)
            {
                //Console.WriteLine("Merged range: " + range.Item1 + " - " + range.Item2);
                total_valid_ids += (Int64)(range.Item2 - range.Item1 + 1);
            }

            return total_valid_ids;
        }

        static int CheckForFreshness(string path)
        {
            if (!File.Exists(path))
            {
                throw new FileNotFoundException("The specified file does not exist.", path);
            }
            string? line;

            List<Tuple<Int64, Int64>> ranges = new List<Tuple<Int64, Int64>>();
            using StreamReader reader = new StreamReader(path);
            while((line = reader.ReadLine()) is not null)
            {
                line = line.Trim();
                if (line == string.Empty)
                {   //now we're checking the actual items
                    break;
                }
                string[] parts = line.Split('-', StringSplitOptions.RemoveEmptyEntries);
                if (parts.Length != 2)
                {
                    throw new FormatException($"Invalid range format: {line}");
                }
                if (!Int64.TryParse(parts[0], out Int64 start) || !Int64.TryParse(parts[1], out Int64 end))
                {
                    throw new FormatException($"Invalid integers in range: {line}");
                }
                ranges.Add(new Tuple<Int64, Int64>(start, end));
            }

            int freshCount = 0;

            // Now process the items
            while ((line = reader.ReadLine()) is not null)
            {
                line = line.Trim();
                if (line == string.Empty)
                {
                    continue;
                }
                if (!Int64.TryParse(line, out Int64 item))
                {
                    throw new FormatException($"Invalid integer item: {line}");
                }
                bool inRange = false;

                if (ranges.Count > 0) {
                    foreach (var range in ranges)
                    {
                        if (item >= range.Item1 && item <= range.Item2)
                        {
                            inRange = true;
                            break;
                        }
                    }
                }
                //Console.WriteLine(inRange ? "in" : "out");
                freshCount = inRange ? freshCount + 1 : freshCount;
            }
            return freshCount;
        }
    }
}
