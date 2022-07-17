Alu=Aluminum6061T6; 
area=Alu(5,2);
time=Alu(15:end,1); %time
exten=Alu(15:end,2); %extension
loa=Alu(15:end,3); %load
Truestrain=Alu(15:end,4); %True strain
MaxLoa=Alu(end,3);
EngineeringStress=loa./area;
trueStress= EngineeringStress.*exp(Truestrain);
EngineeringStrain=(exp(Truestrain))-1;
%% STRESS STRAIN CURVES
plot(Truestrain,trueStress);
title(' Stress - Strain Curve ');
xlabel('Strain');
ylabel('Stress');

hold on
plot(EngineeringStrain,EngineeringStress);

%Elastic Modulus
x1=0.0037;
y1=205.5889;
x2=0.0021;
y2=121.9146;
m=(y2-y1)/(x2-x1);
E=m;
E 
%Yield Strenght
x=.002:.000001:.01;
y=m*(x-.002);
hold on
plot(x,y);
plot(x,y,'o-','MarkerFaceColor','red','MarkerEdgeColor','red','MarkerIndices',167);
legend('True','Engineering','offset');

%Ultimate Tensile Strenght(UTS)
UTS= MaxLoa/area;
UTS