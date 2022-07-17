clc
clear 
clear all
r = randi([1,100],1,20)
stem(r);
title('Ayrik Grafik');
r(find(r<20))=50;
A=sort(r)