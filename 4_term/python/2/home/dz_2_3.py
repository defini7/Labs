import math


with open('3.txt', 'r', encoding='utf-8') as file:
    lines = file.readlines()

total_dists = {}
trajectories_list = []

for line in lines:
    line = line.strip()
    
    parts = line.split(' ', 2)
    pairs = parts[2].split(';')
    
    current_points = []
    total_dist = 0.0
    
    for pair in pairs:
        pair = pair.strip()

        if not pair:
            continue

        x, y = map(int, pair.split(','))
        current_points.append((x, y))
        
        if len(current_points) > 1:
            p1 = current_points[-2]
            p2 = current_points[-1]

            total_dist += math.hypot(p2[0] - p1[0], p2[1] - p1[1])
            
    traj_id = parts[1]
    total_dists[traj_id] = total_dist

    trajectories_list.append([traj_id, current_points])

print('Расстония:', total_dists)

max_segment_dist = 0.0
best_segment = []
best_ids = set()

for i in range(len(trajectories_list)):
    for j in range(i + 1, len(trajectories_list)):
        id1, pts1 = trajectories_list[i]
        id2, pts2 = trajectories_list[j]
        
        for s1 in range(len(pts1)):
            for s2 in range(len(pts2)):
                current_segment = []
                k = 0

                while s1 + k < len(pts1) and s2 + k < len(pts2) and pts1[s1 + k] == pts2[s2 + k]:
                    current_segment.append(pts1[s1 + k])
                    k += 1
                
                if len(current_segment) > 1:
                    current_dist = 0.0

                    for m in range(len(current_segment) - 1):
                        pt1 = current_segment[m]
                        pt2 = current_segment[m+1]

                        current_dist += math.hypot(pt2[0] - pt1[0], pt2[1] - pt1[1])
                    
                    if abs(current_dist - max_segment_dist) < 1e-9 and current_dist > 0:
                        if current_segment == best_segment:
                            best_ids.add(id1)
                            best_ids.add(id2)
                    
                    elif current_dist > max_segment_dist:
                        max_segment_dist = current_dist
                        best_segment = current_segment
                        best_ids = {id1, id2}

if best_segment:
    print('\nОбщий, самый длинный участок:')
    print(f'Координаты: {best_segment}')
    print(f'Номера траекторий: {list(best_ids)}')
    print(f'Длина участка: {max_segment_dist:.2f}')
else:
    print('\nСовпадающих участков не найдено')