function [x] = interpolation_finding(z,v,T,C0)
%% 
 cs = sqrt(1.4*287*T); % sound speed as function of temperature
 Mach = v/cs; % Mach number

%  if Mach < 1
%  Cd = C0/sqrt(1-Mach^2); % Prandtl-Glauert Rule
%  %Cd = C0/(sqrt(1-Mach^2) + ((C0*Mach^2)/(2*(1+sqrt(1-Mach^2)))));
%  %Karman-Tsien Rule
%  %Cd = C0/(sqrt(1-Mach^2)+(C0*Mach^2*(1+(0.2*Mach^2)))/(2*sqrt(1-Mach^2)));
%  % Laitone's Rule
%  elseif Mach == 1
%  Mach = 0.99999; % eliminate the singularity
%  Cd = C0/sqrt(1-Mach^2);
%  elseif Mach > 1
%  Cd = C0/sqrt(Mach^2 - 1);
%  end
%  x = Cd;
cd_0=load('cd_0.txt');
cd_0=[cd_0 0.*cd_0(:,1)];
cd_3000=load('cd_3000.txt');
cd_3000=[cd_3000 3000.*ones(20,1)];
cd_6000=load('cd_6000.txt');
cd_6000=[cd_6000 6000.*ones(20,1)];
cd_12000=load('cd_12000.txt');
cd_12000=[cd_12000 12000.*ones(20,1)];
difference_0=abs(z-0)
difference_3000=abs(z-3000)
difference_6000=abs(z-6000)
difference_12000=abs(z-12000)
difference_all=[difference_0 difference_3000 difference_6000 difference_12000]
siralama=sort(difference_all);
if siralama(1)==difference_0
 new_cd=interp1(cd_0(:,2),cd_0(:,1),Mach);
elseif siralama(1)==difference_3000
 new_cd=interp1(cd_3000(:,2),cd_3000(:,1),Mach);
elseif siralama(1)==difference_6000
 new_cd=interp1(cd_6000(:,2),cd_6000(:,1),Mach);
elseif siralama(1)==difference_12000
 new_cd=interp1(cd_12000(:,2),cd_12000(:,1),Mach);
end
x=new_cd;
end