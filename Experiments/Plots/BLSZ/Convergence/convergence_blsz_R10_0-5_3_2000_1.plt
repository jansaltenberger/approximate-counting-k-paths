set terminal latex
set output "convergence-blsz-k3-r10.tex"
set datafile separator ","
set xrange [0:2000]
set yrange [149.4:182.6]
set xlabel "Iteration"
set ylabel "Ausgabe" offset -1,0 rotate by 90
plot "../../../Results/Convergence/BLSZ/convergence_blsz_R10_0-5_3_2000_1.txt" u 1:2 title 'BLSZ' w lines, 166 title "Exakte Lösung" w lines