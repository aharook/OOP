using System;
using System.Linq;
using System.Diagnostics;
using System.Collections.Generic;
using System.IO;
using System.Threading;

class Program
{
    static void Main()
    {
        var sizes = new int[] { 100_000, 500_000, 1_000_000 };
        var rnd = new Random(52);
        var results = new List<string>();

        foreach (var size in sizes)
        {
            var data = new double[size];
            for (int i = 0; i < size; i++)
                data[i] = rnd.NextDouble() * 1000.0;

            var sw = new Stopwatch();

            sw.Restart();
            var linqSum = data
                .Where(x => x > 0.0)
                .Select(x => HeavOperation(x))
                .Sum();
            sw.Stop();
            var linqTime = sw.Elapsed.TotalMilliseconds;

            sw.Restart();
            var plinqSum = data
                .AsParallel()
                .Where(x => x > 0.0)
                .Select(x => HeavOperation(x))
                .Sum();
            sw.Stop();
            var plinqTime = sw.Elapsed.TotalMilliseconds;

            results.Add($"Size: {size}, LINQ ms: {linqTime:F0}, PLINQ ms: {plinqTime:F0}, LINQ result: {linqSum:F6}, PLINQ result: {plinqSum:F6}");

            Console.WriteLine(results.Last());
        }

        Console.WriteLine();
        Console.WriteLine("Demonstrating side-effects with PLINQ:");
        var testSize = 1_000_000;
        var testData = Enumerable.Range(0, testSize).ToArray();
        int unsafeCounter = 0;
        testData.AsParallel().ForAll(_ => unsafeCounter++);
        Console.WriteLine($"Unsafe counter (expected {testSize}): {unsafeCounter}");

        int interlockedCounter = 0;
        testData.AsParallel().ForAll(_ => Interlocked.Increment(ref interlockedCounter));
        Console.WriteLine($"Interlocked counter (expected {testSize}): {interlockedCounter}");
        int lockCounter = 0;
        object locker = new object();
        testData.AsParallel().ForAll(_ =>
        {
            lock (locker)
            {
                lockCounter++;
            }
        });
        Console.WriteLine($"Lock counter (expected {testSize}): {lockCounter}");
    }
    static double HeavOperation(double x)
    {
        double r = 0.0;
        for (int i = 0; i < 50; i++)
            r += Math.Sqrt(x + i) * Math.Sin(x + i);
        return r;
    }
}
