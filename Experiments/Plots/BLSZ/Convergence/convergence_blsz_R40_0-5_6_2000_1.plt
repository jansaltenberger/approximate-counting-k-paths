#set terminal latex
#set output "4K80convergenceBDHlinkedlist.tex"
set datafile separator ","
set xrange [0:*]
set yrange [0:*]
plot "../../../Results/Convergence/BLSZ/convergence_blsz_R40_0-5_6_2000_1.txt" u 1:2 title 'BLSZ' w lines, 86206002 title "Exakte Lösung" w lines