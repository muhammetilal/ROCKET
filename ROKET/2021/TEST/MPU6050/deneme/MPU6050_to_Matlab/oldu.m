clear all;
clear all;
clf
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
drawnow;
k=0;

%%%%%%%%%%%%%% obje oluþturma kýsmý bitti þimdi arduinodan veri alýþý var

radians_degree = pi/180;
% a = arduino('COM4', 'Uno', 'Libraries', 'I2C');
%  imu = mpu6050(a,'SampleRate',50,'SamplesPerRead',5,'ReadMode','Latest');
%      gyroReadings = readAngularVelocity(imu);
d=5;
for d=1:1000000
m=importdata('denm.txt');
% m.data(d:d+1)
     gyroReadings= [m.data((length(m.data)-1));m.data((length(m.data)))];

    a0=gyroReadings(1);   %xaxis reading
    a1=gyroReadings(2);
    k=(a0-90);%yaxis reading
     k0=(a0-90);         %shifting to 0
     k1=(a1-90);
    r0 = k0*radians_degree;
    r1=k1*radians_degree;
   
    Rz = makehgtform('xrotate',r0,'yrotate',r1);
    set(t,'Matrix',Rz)
    drawnow;
  %  pause(.05);
    
    
end
