import csv
import matplotlib.pyplot as plt
import numpy as np

def read_best_algo_csv(filename):
    data = {}
    best_algo = None

    try:
        with open('C:\\Users\\panta\\Desktop\\os project\\summer\\bestAlgo.csv', newline='') as csvfile:
            reader = csv.reader(csvfile)
            header = next(reader)  # Read the header row
            if len(header) < 2:
                print("Error: CSV file should have at least two columns (parameter, value).")
                return None, None
            
            for row in reader:
                if len(row) < 2:
                    print("Error: Malformed row in CSV file.")
                    continue
                
                parameter = row[0].strip()
                value_str = row[1].strip()

                if parameter == 'Best Algorithm':
                    best_algo = value_str
                    continue

                try:
                    value = float(value_str)  # Attempt to convert to float
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

    # Generate colors avoiding yellow for "Variance"
    colors = []
    for param in parameters:
        if param == "Variance":
            colors.append('blue')  # Assign blue to Variance
        else:
            colors.append(np.random.rand(3,))  # Random color

    plt.figure(figsize=(10, 6))
    plt.bar(parameters, values, color=colors)
    plt.title(f'{best_algo}' if best_algo else '')
    plt.xticks(rotation=45, ha='right')
    plt.tight_layout()
    plt.show()

# Example usage:
if __name__ == "__main__":
    filename = 'C:\\Users\\panta\\Desktop\\os project\\summer\\bestAlgo.csv'
    best_algo_data, best_algo = read_best_algo_csv(filename)

    if best_algo_data:
        print("Data read successfully:")
        print(best_algo_data)
        plot_data(best_algo_data, best_algo)
    else:
        print("Error: Unable to read or process data from the CSV file.")
