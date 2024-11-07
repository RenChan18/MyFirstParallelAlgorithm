#!/bin/bash

# Параметры для настройки
sizes=(100000 200000 400000 600000 800000) # Размер массива
threads=(2 4 6 8) # Количество потоков
OPTION_NUMBER=2
RAND_RANGE=100
LOOP_NUM=100000
output_file="result.txt"

# Очистка файла с результатами перед началом записи
echo "" > "$output_file"

# Цикл по количеству потоков и размерам массива
for t in "${threads[@]}"; do
    for s in "${sizes[@]}"; do
        # Выполнение сборки с заданными параметрами
        make OPTION_NUMBER="$OPTION_NUMBER" RAND_RANGE="$RAND_RANGE" ARRAY_SIZE="$s" THREADS_NUM="$t" LOOP_NUM="$LOOP_NUM"
        
        # Запуск программы и запись результатов в файл с указанием потоков и размера массива
        echo "Threads: $t, Array Size: $s" >> "$output_file"
        ./array_sum >> "$output_file"
        echo "" >> "$output_file" # Добавляем пустую строку для удобства чтения
    done
done

