t_ucus=20;
a=70;
v=100
time=0:0.1:t_ucus;
g=9.801; %yerçekimi ivmesi
vx=v*cosd(a);
x_konum=vx.*time;
z_konum=(v*sind(a).*time) - (1/2).*g.*(time.^2);