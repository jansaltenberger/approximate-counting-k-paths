#set terminal latex
#set output "4K80convergenceBDHlinkedlist.tex"
set datafile separator ","
set xrange [0:*]
set yrange [0:*]
plot "../../../Results/Convergence/BLSZ/convergence_blsz_R80_0-5_4_2000_1.txt" u 1:2 title 'BLSZ' w lines, 4487274 title "Exakte Lösung" w lines