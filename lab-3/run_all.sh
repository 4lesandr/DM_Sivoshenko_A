#!/bin/bash

input_dir="graphs"
output_dir="output"
png_dir="png"

mkdir -p "$output_dir"
mkdir -p "$png_dir"

for input_file in "$input_dir"/*.dot; do
    base_name=$(basename "$input_file" .dot)
    
    output_file="$output_dir/output${base_name:5}.txt"

    ./graph_checker "$input_file" "$output_file"

    echo "Обработан файл $input_file, результат сохранен в $output_file"
    
    png_file="$png_dir/${base_name}.png"
    dot -Tpng "$input_file" -o "$png_file"
    echo "PNG сохранен в $png_file"
done