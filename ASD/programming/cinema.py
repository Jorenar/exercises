#!/usr/bin/env python
# -*- coding: UTF-8 -*-

movies = [{'title': 'A', 'start':  8, 'end': 10},
          {'title': 'B', 'start':  8, 'end': 11},
          {'title': 'C', 'start':  9, 'end': 10},
          {'title': 'D', 'start': 10, 'end': 12},
          {'title': 'E', 'start': 11, 'end': 14},
          {'title': 'F', 'start': 12, 'end': 17}]

halls = [[movies.pop(0)]]

while movies:
    mov = movies.pop(0)
    flag = True
    for hall in halls:
        if mov['start'] >= hall[-1]['end']:
            hall.append(mov)
            flag = False
            break

    if flag:
        halls.append([mov])

print("Needed halls:", len(halls), "\nSchedule:")
for hall in halls:
    for mov in hall:
        print("  [{} {}-{}]".format(mov['title'], mov['start'], mov['end']), end="")
    print()
