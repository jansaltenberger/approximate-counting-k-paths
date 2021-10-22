#set terminal latex
#set output "4K80convergenceBDHlinkedlist.tex"
set datafile separator ","
set xrange [0:*]
set yrange [0:*]
set xrange [0:2000]
set yrange [149.4:182.6]
plot "../../../../Results/Convergence/BDH/Linked List/convergence_bdh_linked_list_R10_0-5_3_2000_1.txt" u 1:2 title 'BDH linked list' w lines, 166 title "Exakte Lösung" w lines