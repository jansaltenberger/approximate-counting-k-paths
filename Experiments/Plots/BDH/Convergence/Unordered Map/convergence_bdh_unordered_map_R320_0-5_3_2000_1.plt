#set terminal latex
#set output "4K80convergenceBDHlinkedlist.tex"
set datafile separator ","
set xrange [0:100]
set yrange [80902836.0:8179365.8]
plot "../../../../Results/Convergence/BDH/Unordered Map/convergence_bdh_unordered_map_R320_0-5_3_2000_1.txt" u 1:2 title 'BDH unordered map' w lines, 8098382 title "Exakte Lösung" w lines