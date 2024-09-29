# Common graph algorithms

# Breadth First Search
# O(V+E)
def bfs(graph: dict, start: int) -> list:
    bfs_nodes = []
    visited = set()
    queue = [start]
    visited.add(start)

    while queue:
        node = queue.pop(0)
        bfs_nodes.append(node)

        for neighbor in graph[node]:
            if neighbor not in visited:
                queue.append(neighbor)
                visited.add(neighbor)
        
    return bfs_nodes

# Depth First Search
# O(V+E)
def dfs_iterative(graph: dict, start: int) -> list:
    dfs_nodes = []
    visited = set()
    stack = [start]

    while stack:
        node = stack.pop()
        if node not in visited:
            dfs_nodes.append(node)
            visited.add(node)

            for neighbor in graph[node]:
                if neighbor not in visited:
                    stack.append(neighbor)
        
    return dfs_nodes

# Topological sort: O(V+E)
# Topological sorting is a linear ordering of vertices in a directed graph such that for every directed edge
# uv from vertex u to vertex v, u comes before v in the ordering. Topological sorting is possible if and only
# if the graph has no directed cycles, i.e., it is a Directed Acyclic Graph (DAG).
# Applications:
#  Task scheduling (tasks with dependencies)
#  Course prerequisite ordering
#  Resolving symbol dependencies in linkers

def topological_sort(graph: dict) -> list:
    visited = set()
    stack = []
    
    for node in graph:
        if node not in visited:
            topological_sort_util(graph, node, visited, stack)

    stack.reverse()
    return stack

def topological_sort_util(graph: dict, v: int, visited: set, stack: list) -> None:
    visited.add(v)

    for neighbor in graph.get(v, []):
        if neighbor not in visited:
            topological_sort_util(graph, neighbor, visited, stack)
    
    stack.append(v)

# A graph is bipartite if it is possible to divide its set of vertices into two disjoint sets U and V such that
# every edge connects a vertex in U to a vertex in V.
#
# The problem of checking if a graph is bipartite is equivalent to checking if the graph can be colored using two
# colors such that adjacent vertices have different colors.
# O(V+E)

def is_bipartite(graph: dict) -> bool:
    color = {}
    queue = []

    for node in graph:
        if node not in color:
            # Start BFS from this node
            queue.append(node)
            color[node] = 0

            while queue:
                current = queue.pop(0)
                for neighbor in graph[current]:
                    if neighbor not in color:
                        # Assign the opposite color to the neighbor
                        color[neighbor] = 1 - color[current]
                        queue.append(neighbor)
                    elif color[neighbor] == color[current]:
                        # If the neighbor has the same color, graph is not bipartite
                        return False
    return True

if __name__ == "__main__":
    graph0 = {
        1: [2, 3],
        2: [1, 4, 5],
        3: [1, 6, 7],
        4: [2],
        5: [2],
        6: [3],
        7: [3]
    }
    
    graph1 = {
        5: [2, 0],
        4: [0, 1],
        2: [3],
        3: [1],
        1: [],
        0: []
    }

    graph2 = {
        0: [1, 3],
        1: [0, 2],
        2: [1, 3],
        3: [0, 2]
    }

    graph3 = {
        0: [1, 2],
        1: [0, 2],
        2: [0, 1]
    }

    print(bfs(graph0, 1))
    print(dfs_iterative(graph0, 1))
    print(topological_sort(graph1))
    print(is_bipartite(graph2))
    print(is_bipartite(graph3))
