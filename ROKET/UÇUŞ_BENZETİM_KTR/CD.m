function x = CD(v,T,C0)
 cs = sqrt(1.4*287*T); % sound speed as function of temperature
 Mach = v/cs; % Mach number

 if Mach < 1
 Cd = C0/sqrt(1-Mach^2); % Prandtl-Glauert Rule
 %Cd = C0/(sqrt(1-Mach^2) + ((C0*Mach^2)/(2*(1+sqrt(1-Mach^2)))));
 %Karman-Tsien Rule
 %Cd = C0/(sqrt(1-Mach^2)+(C0*Mach^2*(1+(0.2*Mach^2)))/(2*sqrt(1-Mach^2)));
 % Laitone's Rule
 elseif Mach == 1
 Mach = 0.99999; % eliminate the singularity
 Cd = C0/sqrt(1-Mach^2);
 elseif Mach > 1
 Cd = C0/sqrt(Mach^2 - 1);
 end

 x = Cd;
end