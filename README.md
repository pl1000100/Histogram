# Histogram

This application communicate with gnuplot program to create histogram and save it to png file (example below).

![](https://github.com/pl1000100/Histogram/blob/main/images/histogram-1.png?raw=true)

While installing gnuplot you need to remember to add it to system variables.

Application can run created script to create histogram from generated data.
You can generate data by choosing range and value (5 digits), adding error with standard deviation is optional.

Program also create files with generated data, one saved in ASCII code and one needed for gnuplot, both with data and time when they was created.
Number of classes of histogram can be determined automatically or by the user.
