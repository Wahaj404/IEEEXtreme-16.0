def langs(nodes, node, L, ans):
    if isinstance(node, Leaf):
        ans.append(node.lang)
        return
    if node.ch in L:
        langs(nodes, nodes[node.left], L, ans)
    else:
        langs(nodes, nodes[node.left], L, ans)
        langs(nodes, nodes[node.right], L, ans)
    
    
class Internal:
    def __init__(self, ch, left, right):
        self.ch = ch
        self.left = left
        self.right = right
        
class Leaf:
    def __init__(self, lang):
        self.lang = lang

inp = input().split()
n = int(inp[0])
p = int(inp[1])

nodes = {}

for _ in range(n):
    inp = input().split()
    if inp[0] == 'I':
        nodes[inp[1]] = Internal(inp[2], inp[3], inp[4])
    else:
        nodes[inp[1]] = Leaf(inp[2])

roots = set(nodes.keys())
for node in nodes.values():
    if isinstance(node, Internal):
        if node.left in roots:
            roots.remove(node.left)
        if node.right in roots:
            roots.remove(node.right)

for _ in range(p):
    L = set(input())
    if ' ' in L:
        L.remove(' ')
    ans = []
    for root_id in roots:
        langs(nodes, nodes[root_id], L, ans)
    ans = list(set(ans))
    ans.sort()
    print(' '.join(ans))
    
    