import csv
import matplotlib.pyplot as plt

# Read the CSV file
data = {}
head_positions = set()  # To store all unique head positions

with open('Seek_Order.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    next(reader)  # Skip the header row
    for row in reader:
        algorithm = row[0]
        seek_order = list(map(int, row[1:]))
        data[algorithm] = seek_order
        head_positions.update(seek_order)  # Add all positions to the set

# Convert head_positions to a sorted list
head_positions = sorted(head_positions)


def plot_seek_order(algo, seek_order):
    fig, ax = plt.subplots(figsize=(12, 6))
    ax.plot(seek_order, range(len(seek_order)), marker='o', label=f'{algo} Seek Order', color='black')
    ax.set_title(f'{algo} Seek Order', fontsize=16)
    ax.set_ylabel('Step', fontsize=14)

    # Display full track numbers tilted diagonally
    ax.set_xticks(head_positions)
    ax.set_xticklabels(head_positions, rotation=45, ha='right', fontsize=12)
    ax.yaxis.set_tick_params(labelsize=12)
    ax.invert_yaxis()

    # Remove the top x-axis
    ax.spines['top'].set_visible(False)
    ax.tick_params(top=False)

    # Increase spacing between bottom of the graph and x-axis labels
    plt.subplots_adjust(bottom=0.3)  # Adjust as needed

    ax.grid(True, which='both', linestyle='--', linewidth=0.5)
    plt.legend(fontsize=12)
    plt.tight_layout()
    plt.show()
















































    


# Plotting each algorithm's seek order
for algo, seek_order in data.items():
    plot_seek_order(algo, seek_order)
