import networkx as nx
import matplotlib.pyplot as plt

# Initialize a directed graph
G = nx.DiGraph()

# Read the file and parse each line
with open('input.txt', 'r') as file:
    for line in file:
        # Discard the first character and then split the line into module and signals
        line = line.strip()
        discarded_char = line[0]
        line = line[1:]
        module, _, signals = line.partition('->')
        
        # Extract module name and signals
        module = module.strip()
        signals = [signal.strip() for signal in signals.split(',')]

        # Add edges from module to signals
        for signal in signals:
            G.add_edge(module, signal)
            
        # Assign colors based on the discarded character
        if discarded_char == '%':
            node_color = 'skyblue'
        elif discarded_char == '&':
            node_color = 'lightgreen'
        else:
            node_color = 'salmon'

        # Add the module node with its assigned color
        if module not in G.nodes:
            G.add_node(module)
        G.nodes[module]['color'] = node_color

# Draw the graph with the specified node colors
pos = nx.spring_layout(G, seed=42)
node_colors = [G.nodes[node].get('color', 'skyblue') for node in G.nodes]
nx.draw(G, pos, with_labels=True, node_size=500, node_color=node_colors, font_size=10, font_weight="bold", arrowsize=10)
plt.title("Module Signals Map")
plt.tight_layout()
plt.show()