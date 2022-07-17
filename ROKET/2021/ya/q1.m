clc
clear
clear all
%  Alu = readtable("Aluminum6061-T6.txt");
% % %% TIME
% load('Aluminum6061-T6.txt');
% time=Alu(15:end,1);  time = table2array(time); 
% % t(1:186,1)=time{1:186,1};
% % %%
% % extension=Alu(15:end,2);  extension = table2array(extension);
% % 
% % plot(time{1:186,1}, extension{1:186,1})
%% OBTAIN parameters

Alu=Aluminum6061T6; 
area=Alu(5,2);
time=Alu(15:end,1); %time
exten=Alu(15:end,2); %extension
loa=Alu(15:end,3); %load
strain=Alu(15:end,4); %strain
stress=loa./area;
%% STRESS STRAIN CURVE
plot(strain,stress);
title(' Stress - Strain Curve ');
xlabel('Strain');
ylabel('Stress');
%%

elastic=stress./strain;
plot(elastic);