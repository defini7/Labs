def sum_range(start, end):
    try:
        start, end = int(start), int(end)
    except ValueError:
        return None

    if start > end:
        start, end = end, start

    return sum(n ** 2 for n in range(start, end + 1))


print(sum_range(1, 10))