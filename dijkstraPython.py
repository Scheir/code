#Python version of dijkstra using heapq (priority_queue in c++)
#Solves the kata: Find the cheapest
#path https://www.codewars.com/kata/5abeaf0fee5c575ff20000e4/
#The function takes the following parameters:

#   (t)       (start)   (finish)
#toll_map  |  start  |  finish
#          |         |
#[         |         |
# [1,9,1], |  (0,0)  |  (0,2)
# [2,9,1], |         |
# [2,1,1], |         |
#]         |         |

#Goal is to find the cheapes way from start to finish.
#Solved by implementing dijkstras algorithm using heapq
#for efficiency.

import heapq
def cheapest_path(t, start, finnish):
    visited = t.copy()
    visited = [[0] * len(inner) for inner in visited]
    q = [] 
    current = (0,start[0], start[1], "") 
    heapq.heappush(q,current)
    while len(q) != 0:
        cur = heapq.heappop(q) 
        cord = (cur[1],cur[2])
        if cord == finnish:
            arr = cur[3].split(' ')
            return arr[1:]
        for x in (([-1,0]," up"), ([1,0], " down"), ([0,-1], " left"), ([0,1]," right")):
            dx = cord[0]+x[0][0]
            dy = cord[1]+x[0][1]
            if dx >= 0 and dx < len(t) and dy >= 0 and dy < len(t[0]) and visited[dx][dy] == 0:
                heapq.heappush(q, (cur[0]+t[dx][dy],dx,dy,cur[3]+x[1]))
                visited[dx][dy] = 1
