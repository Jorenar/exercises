#!/usr/bin/env python3
# -*- coding: UTF-8 -*-


board = [[ 0, 0, 0, 0 ],
         [ 0, 1, 0, 1 ],
         [ 0, 0, 1, 0 ],
         [ 0, 1, 0, 0 ]]

board = [[ 0, 1, 0, 1 ],
         [ 0, 1, 1, 1 ],
         [ 1, 0, 0, 0 ]]

board = [[ 0, 0, 0, 0 ],
         [ 0, 1, 0, 1 ],
         [ 0, 0, 1, 0 ],
         [ 0, 1, 1, 0 ]]

m = len(board)
n = len(board[0])

mem = { (m-1,n-1) : (board[m-1][n-1], "") }

def walk(y,x):
    if y >= m or x >= n:
        return (0, None)

    if (y,x) in mem:
        return mem[(y,x)]

    Sy,strY = walk(y+1, x)
    Sx,strX = walk(y, x+1)

    str=""
    S = max(Sy, Sx)
    if S == Sx and strX != None:
        str = ">" + strX
    elif strY != None:
        str = "v" + strY

    mem[(y,x)] = (S + board[y][x], str)
    return mem[(y,x)]

print(walk(0,0))
