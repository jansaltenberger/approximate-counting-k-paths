set terminal latex
set output "clock-cycles-k-4.tex"
set datafile separator ","
set xrange [10:160]
set yrange [0:*]
set xlabel "n"
set ylabel "Taktzyklen" rotate by 90
plot "../Results/Measurements/bdh_unordered_map_k_4.txt" u 1:4 title 'BDH unordered map' with linespoints lt 1 pt 4, "../Results/Measurements/bdh_linked_list_k_4.txt" u 1:4 title 'BDH linked list' with linespoints lt 4 pt 6, "../Results/Measurements/blsz_k_4.txt" u 1:4 title 'BLSZ' with linespoints lt 3 pt 8
set output
set terminal pop