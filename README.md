# 🚀 Disk Scheduling Algorithms – OS Project

This project is a comprehensive **Operating Systems project** written in **C++**, analyzing and visualizing key **disk scheduling algorithms** with Python-powered plots.

### ✅ Implemented Algorithms:
- FCFS (First-Come First-Serve)
- SSTF (Shortest Seek Time First)
- SCAN
- C-SCAN (Circular SCAN)
- LOOK
- C-LOOK (Circular LOOK)

Each algorithm is analyzed and compared on the basis of:
- 🔁 Total Head Movements
- ⏱ Average Seek Time (AST)
- 📊 Throughput
- ⏱ Response Time (RT)
- ⌛ Max Seek Time
- 📈 Variance

---

## 📁 Project Structure
├── main.cpp # Main driver
├── Algorithms.cpp # Algorithm logic
├── comparision.cpp # Comparison table generator
├── structure.h # Data structures (Request, Metrics)
├── Algorithms.h # Algorithm headers
├── comparision.h # Header for comparison logic
├── input.txt # Disk I/O request queue input
├── plot.py # Python line plot for seek order
├── result.py # Python grouped bar chart for all algorithms
├── bestAlgo.py # Python bar chart for best algorithm
├── Result.csv # Output CSV for all algorithm metrics
├── Seek_Order.csv # Output CSV for seek orders
├── bestAlgo.csv # Output CSV for best algorithm
└── README.md # This file

---

## ⚙️ How to Run

### 1. ✅ Compile the C++ Project
```bash
g++ main.cpp Algorithms.cpp comparision.cpp -o os_project
./os_project          # Linux/Mac
.\os_project.exe      # Windows PowerShell
``` 
---

### 2. ✅ You'll be prompted:
enter the no. of requests:
📌 At this prompt, enter how many requests you want to process from input.txt.
📝 Example:
If input.txt contains 100+ numbers, and you want to test with just the first 8, type:8

---
### 3. 📊 Run Python Visualizations
Make sure you have Python 3 with matplotlib and numpy:
pip install matplotlib numpy
Then run the graph scripts:
python plot.py        # Line plot of seek order
python result.py      # Grouped bar chart of all algorithms
python bestAlgo.py    # Bar chart of best algorithm

---
### 4. 📈 Sample Output
✅ Terminal comparison table with algorithm performance
✅ CSV exports (Result.csv, Seek_Order.csv, bestAlgo.csv)
✅ Python-generated graphs:
Seek order line plot
Metric-wise grouped bar charts
Best algorithm analysis chart

---
### 5.📦Requirements
g++ compiler (Linux/Mac/MinGW on Windows)
Python 3.x
Python libraries: matplotlib, numpy

🤝 Contributing
This project is built for educational purposes. Contributions, suggestions, or improvements are welcome!

📝 License
This project is for academic/non-commercial use only. Customize freely for your university or personal learning use.

👨‍💻 Author
Anoop Pant
B.Tech – Computer Science & Engineering
OS Mini Project (Disk Scheduling Algorithms)
