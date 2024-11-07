import matplotlib.pyplot as plt

# Data from the table
threads = [2, 4, 6, 8]
speed_up_100k = [0.1094, 0.5471, 0.7765, 1.8353]
speed_up_200k = [0.2, 0.8723, 1.1064, 1.5187]
speed_up_400k = [0.7603, 1.4255, 0.8251, 1.1296]
speed_up_600k = [1.0897, 2.0166, 2.0441, 3.4497]
speed_up_800k = [5.1336, 2.6832, 2.4885, 2.6269]

# Plotting the graph
plt.figure(figsize=(10, 6))
plt.plot(threads, speed_up_100k, marker='o', label='100,000 elements')
plt.plot(threads, speed_up_200k, marker='o', label='200,000 elements')
plt.plot(threads, speed_up_400k, marker='o', label='400,000 elements')
plt.plot(threads, speed_up_600k, marker='o', label='600,000 elements')
plt.plot(threads, speed_up_800k, marker='o', label='800,000 elements')

# Labels and title
plt.xlabel("Number of Threads")
plt.ylabel("Speed Up (S(p))")
plt.title("Speed Up vs Number of Threads for Different Array Sizes")
plt.legend()
plt.grid(True)
plt.show()

