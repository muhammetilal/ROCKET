clc
clear
clear all
duration=10;
dt=0.1;
%% defining update equations
A=[1 dt;0 1]; % state transition matrix
B=[dt^2/2 ; dt]; %input control matrix
C=[1 0]; % measurement matrix
