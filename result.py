import csv
import matplotlib.pyplot as plt
import numpy as np

def clean_value(value):
    try:
        parts = value.split('.')
        if len(parts) > 2:
            value = ''.join(parts[:-1]) + '.' + parts[-1]
        return float(value)
    except ValueError:
        print(f"Invalid value {value}, skipping.")
        return None

def read_csv(filename):
    data = {}
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        header = next(reader)
        for key in header:
            data[key] = []
        for row in reader:
            for key, value in zip(header, row):
                if key == "Algorithms":
                    data[key].append(value)
                else:
                    data[key].append(clean_value(value))
    return data

def plot_data(data):
    algorithms = data['Algorithms']
    parameters = list(data.keys())[1:]
    num_algorithms = len(algorithms)
    width = 0.15
    x_indices = np.arange(num_algorithms)

    plt.figure(figsize=(12, 6))

    for i, parameter in enumerate(parameters):
        values = data[parameter]
        valid_values = [v for v in values if v is not None]
        valid_algorithms = [algorithms[i] for i, v in enumerate(values) if v is not None]

        if not valid_values:
            print(f"No valid values for {parameter}, skipping plot.")
            continue

        offset = width * i
        plt.bar(x_indices + offset, valid_values, width=width, label=parameter)

    plt.xlabel('Algorithms')
    plt.ylabel('Values')
    plt.title('Comparison of Parameters for each Algorithm')
    plt.xticks(x_indices + width * (len(parameters) - 1) / 2, algorithms)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    filename = 'Result.csv'
    data = read_csv(filename)
    plot_data(data)
