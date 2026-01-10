using System;
using System.IO;
using System.Collections;

namespace d4
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
                List<List<int>> data = ParseFile(path);
                int forklifts = FindToiletPaper(data, false);
                Console.WriteLine("Forklifts p1: " + forklifts);
                int forklifts_p2 = 0;
                while((forklifts = FindToiletPaper(data, true)) > 0)
                {
                    forklifts_p2 += forklifts;
                    
                }
                Console.WriteLine("Forklifts p2 iteration: " + forklifts_p2);
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine("Error: " + ex.Message);
                return 1;
            }

            return 0;
        }

        private static int FindToiletPaper(List<List<int>> data, bool shouldRemove)
        {
            int forkliftCount = 0;

            // Loop through the 2d array to determine where the forklifts should be placed
            for (int i = 0; i < data.Count; i++)
            {
                for (int j = 0; j < data[i].Count; j++)
                {
                    int surrounding = 0;
                    if (data[i][j] == 0)
                    {
                        continue; // Can't place forklift on empty space
                    }
                    //Now we need to check the surrounding 8 cells
                    for (int k = -1; k <= 1; k++)
                    {
                        for (int m = -1; m <= 1; m++)
                        {
                            try
                            {
                                if (k == 0 && m == 0)
                                {
                                    continue; // Skip the center cell
                                }
                                if (data[i + k][j + m] == 1)
                                {
                                    surrounding++;
                                }
                            }
                            catch (ArgumentOutOfRangeException)
                            {
                                // Ignore out of bounds
                            }
                        }
                    }
                    if (surrounding <= 3)
                    {
                        //Console.WriteLine($"Place forklift at ({i}, {j}) with {surrounding} surrounding obstacles.");
                        if(shouldRemove)
                            data[i][j] = 0;
                        forkliftCount++;
                    }
                }
            }
            return forkliftCount;
        }

        private static List<List<int>> ParseFile(string path)
        {
            List<List<int>> data = new List<List<int>>();
            
            string? line;
            using var reader = new StreamReader(path);
            //Read in all of the lines and convert to 2D array
            while ((line = reader.ReadLine()) is not null)
            {
                data.Add(new List<int>());
                foreach (char ch in line)
                {
                    if(ch == '@')
                    {
                        data[^1].Add(1);
                    }
                    else if(ch == '.')
                    {
                        data[^1].Add(0);
                    }
                }
                //Console.WriteLine(string.Join(" ", data[^1]));
            }
            return data;
        }
    }
}
