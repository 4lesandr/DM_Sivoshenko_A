for file in output/*.dot; do
    dot -Tpng "$file" -o "${file%.dot}.png"
done
