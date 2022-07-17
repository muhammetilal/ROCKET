clc;
clear;
clear all;
close all;
ax = axes('XLim',[-4 4],'YLim',[-4 4],'ZLim',[-4 4]);
view(3); grid on; axis equal;
 %axis off;
% Create objects to group
[cylx,cyly,cylz]=cylinder(.4);
[conx,cony,conz]=cylinder([1,0]);
[mx,my,mz]=cylinder([0,0.1]);
[x,y,z]=sphere(50);
h(1)=surface(x,y,z-1);
h(2)=surface(cylx,cyly,cylz*2+1); %orta gövde
h(3)=surface(conx/2-0.01,cony/2-0.01,conz+3); %baþ kýsýmý
h(4)=surface(my/2,mx/4+0.4,mz/1.5+0.5,'FaceColor','red');
h(5)=surface(my/2,mx/4-0.4,mz/1.5+0.5,'FaceColor','red');
h(6)=surface(my/2+0.4,mx/4,mz/1.5+0.5,'FaceColor','red');
h(7)=surface(my/2-0.4,mx/4,mz/1.5+0.5,'FaceColor','red');
set(h(2:7),'Clipping','off');
t = hgtransform('Parent',ax);
set(h(2:7),'Parent',t);

%% GPS

a=37.0866;

b=29.35225;
%transmitter
tx = txsite('Name','MathWorks Apple Hill',...
       'Latitude',a, ...
       'Longitude',b);
  % show(tx);
   
 %receiver
   rx = rxsite('Name','MathWorks Lakeside', ...
       'Latitude',37.3021, ...
       'Longitude',29.3764);
  
   %distance
   dm = distance(tx,rx); % Unit: m
   dkm = dm / 1000; %unit:km
   azFromEast = angle(tx,rx); % Unit: degrees counter-clockwise from East
   azFromNorth = -azFromEast + 90; % Convert angle to clockwise from North
   
   ss = sigstrength(rx,tx);
   margin = abs(rx.ReceiverSensitivity - ss); %hassassiyeti çýkararak ölçer
   %link(rx,tx)
  coverage(tx,'close-in', ...
      'SignalStrengths',-100:5:-60) %sinyl gücüneg göre kapsadýðý alan


 %% Simulation
 clc;
clear;
clear all;
g=9.801; %yerçekimi ivmesi
v=100;
a=70;% uçuþi yola açýsý;
t_ucus=(2*v*sind(a))/g;
t_cikis=t_ucus/2;
for t=0:0.1:t_ucus
time=0:0.01:t;
vx=v*cosd(a);
x_konum=vx.*time;
z_konum=(v*sind(a).*time) - (1/2).*g.*(time.^2);
[maxx,idx] = max(x_konum);
[maxz,idz] = max(z_konum);
plot(x_konum,z_konum,x_konum(idx),z_konum(idx),'pr');
legend(sprintf('Max Ýrtifa = %0.3f',maxz),sprintf('Maximum Uzaklýk = %0.3f',maxx));
trxt=('Max Uzaklýk');
txt=('Maximum Ýrtifa \uparrow');
 text(x_konum(idx),z_konum(idx),trxt,'VerticalAlignment','bottom');
 text(x_konum(idz),maxz,txt,'HorizontalAlignment','right');
 drawnow;
end
