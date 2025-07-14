import csv
import matplotlib.pyplot as plt
import numpy as np

def read_best_algo_csv(filename):
    data = {}
    best_algo = None

    try:
        with open(filename, newline='') as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                if len(row) < 2:
                    print("Error: Malformed row in CSV file.")
                    continue
                
                parameter = row[0].strip()
                value_str = row[1].strip()

                if parameter == 'Best Algorithm':
                    best_algo = value_str
                else:
                    try:
                        value = float(value_str)
                        data[parameter] = value
                    except ValueError:
                        print(f"Error: Non-numeric value found for parameter '{parameter}'. Skipping.")
        
    except IOError:
        print(f"Error: Unable to read or process data from the CSV file '{filename}'.")
        return None, None

    return data, best_algo

def plot_data(data, best_algo):
    parameters = list(data.keys())
    values = list(data.values())

    colors = []
    for param in parameters:
        if param == "Variance":
            colors.append('blue')
        else:
            colors.append(np.random.rand(3,))

    plt.figure(figsize=(10, 6))
    bars = plt.bar(parameters, values, color=colors)
    plt.title(f'{best_algo}' if best_algo else 'No Algorithm Name Provided')
    plt.xticks(rotation=45, ha='right')
    plt.tight_layout()

    for bar in bars:
        height = bar.get_height()
        plt.annotate(f'{height:.2f}',
                     xy=(bar.get_x() + bar.get_width() / 2, height),
                     xytext=(0, 3),
                     textcoords="offset points",
                     ha='center', va='bottom')

    plt.show()

if __name__ == "__main__":
    filename = 'bestAlgo.csv'
    best_algo_data, best_algo = read_best_algo_csv(filename)

    if best_algo_data:
        print("Data read successfully:")
        print(best_algo_data)
        plot_data(best_algo_data, best_algo)
    else:
        print("Error: Unable to read or process data from the CSV file.")
