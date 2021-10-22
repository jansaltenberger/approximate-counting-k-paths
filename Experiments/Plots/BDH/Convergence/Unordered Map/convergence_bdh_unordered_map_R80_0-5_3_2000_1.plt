#set terminal latex
#set output "4K80convergenceBDHlinkedlist.tex"
set datafile separator ","
set xrange [0:200]
set yrange [0:*]
plot "../../../../Results/Convergence/BDH/Unordered Map/convergence_bdh_unordered_map_R80_0-5_3_2000_1.txt" u 1:2 title 'BDH unordered map' w lines, 118774 title "Exakte Lösung" w lines