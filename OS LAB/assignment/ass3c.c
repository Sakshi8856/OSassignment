import heapq

class PuzzleState:
    def __init__(self, board, empty_tile_pos, g, h):
        self.board = board
        self.empty_tile_pos = empty_tile_pos
        self.g = g  # Cost from start to current node
        self.h = h  # Heuristic cost from current node to goal
        self.f = g + h  # Total cost

    def __lt__(self, other):
        return self.f < other.f

def calculate_h(board, goal):
    h = 0
    for i in range(3):
        for j in range(3):
            tile = board[i][j]
            if tile != 0:  # Ignore the empty tile
                goal_pos = divmod(goal.index(tile), 3)
                h += abs(goal_pos[0] - i) + abs(goal_pos[1] - j)  # Manhattan distance
    return h

def get_neighbors(state):
    neighbors = []
    x, y = state.empty_tile_pos
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]  # Down, Up, Right, Left
    for dx, dy in directions:
        new_x, new_y = x + dx, y + dy
        if 0 <= new_x < 3 and 0 <= new_y < 3:
            new_board = [row[:] for row in state.board]  # Make a copy of the current board
            new_board[x][y], new_board[new_x][new_y] = new_board[new_x][new_y], new_board[x][y]
            neighbors.append(PuzzleState(new_board, (new_x, new_y), state.g + 1, calculate_h(new_board, goal)))
    return neighbors

def is_goal(state, goal):
    return state.board == goal

def a_star(initial_board, goal):
    initial_empty_tile_pos = [(i, j) for i in range(3) for j in range(3) if initial_board[i][j] == 0][0]
    initial_h = calculate_h(initial_board, goal)
    initial_state = PuzzleState(initial_board, initial_empty_tile_pos, 0, initial_h)
    
    open_list = []
    heapq.heappush(open_list, initial_state)
    closed_set = set()
    closed_set.add(tuple(map(tuple, initial_board)))

    while open_list:
        current_state = heapq.heappop(open_list)

        if is_goal(current_state, goal):
            return current_state.g  # Return the cost to reach the goal

        for neighbor in get_neighbors(current_state):
            neighbor_tuple = tuple(map(tuple, neighbor.board))

            if neighbor_tuple not in closed_set:
                closed_set.add(neighbor_tuple)
                heapq.heappush(open_list, neighbor)

    return None  # No solution found

if __name__ == "__main__":
    initial_board = [
        [2, 8, 3],
        [1, 6, 4],
        [7, 0, 5]
    ]

    goal = [
        [1, 2, 3],
        [8, 0, 4],
        [7, 6, 5]
    ]

    result = a_star(initial_board, goal)
    if result is not None:
        print(f"Cost to reach goal: {result}")
    else:
        print("No solution found.")

