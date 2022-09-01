# set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 600, 400 
# set output 'histograms.2.png'
set boxwidth 2 absolute
set style fill solid 1.00 border lt -1
set key fixed right top vertical Right noreverse noenhanced autotitle nobox
set style histogram clustered gap 1 title textcolor lt -1
set datafile missing '-'
set style data histograms
set xtics border in scale 0,0 nomirror rotate by -45  autojustify font "1,7"
set xtics norangelimit 
set xtics ()
set title "Histogram \n dla pomiarów wygenerowanych w aplikacji" 
set xlabel "klasy" font "1,10"
set ylabel "liczność" font "1,10"
set xrange [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback
set yrange [ 0 : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback
set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback
NO_ANIMATION = 1
set encoding utf8
plot 'pomiary.txt' using 2:xtic(1) ti "liczność"
set terminal png
set output "histogram.png"
replot