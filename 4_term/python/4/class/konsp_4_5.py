from itertools import zip_longest


def merge_with_zip(seq1, seq2):
    result = []

    for a, b in zip_longest(seq1, seq2, fillvalue='?'):
        result.append(a)
        result.append(b)

    return result


seq1 = "ABCDE"
seq2 = "123"

result = merge_with_zip(seq1, seq2)
print(result)
