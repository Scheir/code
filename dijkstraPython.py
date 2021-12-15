import heapq
def dijkstra(mat):
    R = len(mat)
    C = len(mat[0])
    visited = [[0] * C for _ in range(R)]
    q = [] 
    current = (0,0,0)
    heapq.heappush(q,current)
    while len(q):
        cnt,x,y = heapq.heappop(q)
        if (x,y) == (C-1,R-1):
            return cnt
        for i,j in ((-1,0),(1,0),(0,-1),(0,1)):
            X = x+i
            Y = y+j
            if 0<=X<R and 0<=Y<C and visited[X][Y] == 0:
                visited[X][Y] = -1
                heapq.heappush(q,(cnt+mat[X][Y],X,Y))
