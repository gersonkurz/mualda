using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp_benchmarks
{
    class Program
    {
        static void Main(string[] args)
        {
            new SortingBenchmarks().Run();
            Console.WriteLine("[PRESS ANY KEY TO CLOSE THIS APP]");
            Console.ReadLine();
        }
    }
}
