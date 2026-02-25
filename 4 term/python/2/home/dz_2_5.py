graph = {}
adj_counts = {}

with open('5.txt', 'r') as file:
    for line in file:
        n1, n2 = map(int, line.split(' '))

        if n1 not in graph:
            graph[n1] = [n2]
        else:
            graph[n1].append(n2)

        if n2 not in graph:
            graph[n2] = [n1]
        else:
            graph[n2].append(n1)

for node in graph:
    if node not in adj_counts:
        adj_counts[node] = 0

    adj_counts[node] += len(graph[node])

with open('5.txt', 'a', encoding='utf-8') as file:
    file.write('\nВершины и степени:\n')
    
    for node in adj_counts:
        file.write(f'{node}: {adj_counts[node]}\n')
