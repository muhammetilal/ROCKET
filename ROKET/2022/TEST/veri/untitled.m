clear
clear all
clc

for i=1:10000000
    a=importdata("deneme.txt");
    plot(a(end-15:end-1,4));
    drawnow;
end