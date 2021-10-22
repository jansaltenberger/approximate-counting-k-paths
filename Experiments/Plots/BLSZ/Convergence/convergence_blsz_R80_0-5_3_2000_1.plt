#set terminal latex
#set output "4K80convergenceBDHlinkedlist.tex"
set datafile separator ","
set xrange [0:*]
set yrange [0:*]
plot "../../../Results/Convergence/BLSZ/convergence_blsz_R80_0-5_3_2000_1.txt" u 1:2 title 'BLSZ' w lines, 118774 title "Exakte Lösung" w lines