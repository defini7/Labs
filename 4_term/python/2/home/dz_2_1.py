raw_ips = {} # (ip, [connected, count])

with open('1.txt') as logs:
    for line in logs:
        start = line.find(' ', line.find(' ') + 1) + 1
        end = line.find(' ', start)

        ip = line[start:end]
        op = line[end+1:].rstrip()

        if ip in raw_ips:
            if raw_ips[ip][0]: # connected
                # Если ip подсоединен, то можно его отсоединить,
                # но если он пытается подключиться еще раз, то ничего не делаем
                if op == 'LOGOUT':
                    raw_ips[ip][0] = False
                    raw_ips[ip][1] += 1
            else: # not connected
                # Если ip не подсоединен, то можно его подсоединить,
                # но если он пытается отключиться еще раз, то ничего не делаем
                if op == 'LOGIN':
                    raw_ips[ip][0] = True
                    raw_ips[ip][1] += 1
        else:
            # Если такого ip еще нет, то смотрим, что он подключается,
            # иначе ничего не добавляем
            if op == 'LOGIN':
                raw_ips[ip] = [True, 1]

n = int(input('N: '))
ips = []

for key in raw_ips:
    if raw_ips[key][1] > n:
        ips.append(key)

print(ips)
