import matplotlib.pyplot as plt

# Данные с делением на 10000
data = {
    1: [0.00017, 0.000235, 0.000463, 0.000725, 0.001048],
    2: [0.000036, 0.000047, 0.000352, 0.000790, 0.005380],
    4: [0.000093, 0.000205, 0.000660, 0.001462, 0.002812],
    6: [0.000132, 0.000260, 0.000382, 0.001482, 0.002608],
    8: [0.000312, 0.0003569, 0.000523, 0.002501, 0.002753],
}


array_sizes = [100000, 200000, 400000, 600000, 800000]

# Первый график: зависимость времени выполнения от размера массива для разных потоков
plt.figure(figsize=(12, 8))

for threads, times in data.items():
    plt.plot(array_sizes, times, marker='o', label=f'{threads} threads')

plt.xlabel('Array Size')
plt.ylabel('Elapsed Time (seconds)')
plt.title('Elapsed Time vs Array Size for Different Thread Counts')
plt.legend(title="Threads")
plt.grid(True)
plt.show()

# Второй график: зависимость времени выполнения от количества потоков для разных размеров массива
plt.figure(figsize=(12, 8))

for i, size in enumerate(array_sizes):
    times_for_size = [data[threads][i] for threads in data]  # Время для данного размера массива при разном количестве потоков
    plt.plot(data.keys(), times_for_size, marker='o', label=f'Array Size: {size}')

plt.xlabel('Number of Threads')
plt.ylabel('Elapsed Time (seconds)')
plt.title('Elapsed Time vs Number of Threads for Different Array Sizes')
plt.legend(title="Array Sizes")
plt.grid(True)
plt.show()


