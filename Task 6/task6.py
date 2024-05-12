from collections import deque

chessboard = [[0]*4 for _ in range(3)]
initial_state = [(0, i) for i in range(3)] + [(2, i) for i in range(3)]
goal_state = [(2, i) for i in range(3)] + [(0, i) for i in range(3)]

# knight moves
knight_moves = [(2, 1), (1, 2), (-1, 2), (-2, 1), (-2, -1), (-1, -2), (1, -2), (2, -1)]

def is_valid(pos):
    x, y = pos
    return 0 <= x < 3 and 0 <= y < 4

def bfs(start, end):
    queue = deque([(start, 0)])
    visited = {start}
    while queue:
        pos, cost = queue.popleft()
        if pos == end:
            return cost
        for move in knight_moves:
            new_pos = (pos[0] + move[0], pos[1] + move[1])
            if is_valid(new_pos) and new_pos not in visited:
                queue.append((new_pos, cost + 1))
                visited.add(new_pos)
    return float('inf')

#the total cost
total_cost = 0
for start, end in zip(initial_state, goal_state):
    total_cost += bfs(start, end)

print(f'The minimum number of moves is {total_cost}.')
