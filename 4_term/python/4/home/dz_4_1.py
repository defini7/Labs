import argparse
import time
import sys
from itertools import product


def find_ways_without_itertools(N, K, min_throws_only=False):
    ways = []
    
    def backtrack(current_sum, current_sequence):
        if current_sum == N:
            ways.append(current_sequence.copy())
            return
        
        if current_sum > N:
            return

        for points in range(1, K + 1):
            current_sequence.append(points)
            backtrack(current_sum + points, current_sequence)
            current_sequence.pop()
    
    backtrack(0, [])
    
    if min_throws_only:
        if ways:
            min_len = min(len(way) for way in ways)
            ways = [way for way in ways if len(way) == min_len]
    
    return ways


def find_ways_with_itertools(N, K, min_throws_only=False):
    ways = []
    
    min_throws = (N + K - 1) // K
    max_throws = N
    
    for num_throws in range(min_throws, max_throws + 1):
        for combination in product(range(1, K + 1), repeat=num_throws):
            print(combination)
            if sum(combination) == N:
                ways.append(list(combination))
    
    if min_throws_only and ways:
        min_len = min(len(way) for way in ways)
        ways = [way for way in ways if len(way) == min_len]
    
    return ways


def write_results_to_file(filename, ways, N, K, execution_time=None, min_throws_only=False):
    with open(filename, 'w', encoding='utf-8') as f:
        f.write(f"N = {N}, K = {K}\n")
        
        if min_throws_only:
            f.write("Только варианты с минимальным количеством бросков\n")
        
        f.write(f"\nКол-во способов: {len(ways)}\n")
        
        if ways:
            f.write("\nСпособы:\n")
            for i, way in enumerate(ways, 1):
                f.write(f"{i}. {' + '.join(map(str, way))} = {N}\n")
            
            if min_throws_only:
                min_throws_count = len(ways[0]) if ways else 0
                f.write(f"\nМинимальное количество бросков: {min_throws_count}\n")
        
        if execution_time is not None:
            f.write(f"\nВремя выполнения: {execution_time:.6f} секунд\n")


def parse_arguments():
    parser = argparse.ArgumentParser()
    
    parser.add_argument('-N', type=int)
    parser.add_argument('-K', type=int)
    parser.add_argument('-F', default='out_1.txt')
    parser.add_argument('-NS', action='store_true')
    parser.add_argument('-t', action='store_true')
    parser.add_argument('-i', action='store_true')
    
    return parser.parse_args()


def main():
    args = parse_arguments()
    
    if args.N is not None:
        N = args.N
    else:
        N = int(input("Введите количество очков N: "))
    
    if args.K is not None:
        K = args.K
    else:
        K = int(input("Введите максимальное количество очков за бросок K: "))
    
    if N <= 0 or K <= 0:
        print("Ошибка: N и K должны быть положительными числами")
        sys.exit(1)
    
    start_time = time.time()
    
    if args.i:
        ways = find_ways_with_itertools(N, K, args.NS)
    else:
        ways = find_ways_without_itertools(N, K, args.NS)
    
    end_time = time.time()
    execution_time = end_time - start_time
    
    print(f"\nНайдено способов: {len(ways)}")
    
    if ways:
        print("\nСпособы:")
        for i, way in enumerate(ways, 1):
            print(f"{i}. {' + '.join(map(str, way))} = {N}")
    
    if args.NS and ways:
        min_throws = len(ways[0])
        print(f"\nМинимальное количество бросков: {min_throws}")
    
    print(f"\nВремя выполнения: {execution_time:.6f} секунд")

    write_results_to_file(args.F, ways, N, K, 
                          execution_time if args.t else None, 
                          args.NS)
    
    print(f"\nРезультаты сохранены в файл: {args.F}")


if __name__ == "__main__":
    main()
    