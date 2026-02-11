n = input('Введите N ')

if not n.isdecimal():
    print('N - не целое')
    exit(1)

k = input('Введите k ')

if not k.isdecimal():
    print('k - не целое')
    exit(1)

n, k = int(n), int(k)

print('Каждому достанется по', n // k, 'мандаринов, а останется', n % k)