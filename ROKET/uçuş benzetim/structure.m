clear
clear all
clc
g=9.8;
motion.initvelocity=input('Enter velocity ');
motion.initangle.degrees=input('Enter angle ');
motion.initvx=motion.initvelocity*cosd(motion.initangle.degrees);
motion.initvy=motion.initvelocity*sind(motion.initangle.degrees);
motion.initangle.radians=motion.initangle.degrees*pi/180;
motion.time=2*motion.initvy/g;
motion.hmax=(motion.initvy^2)/(2*g);
motion.rangemax=motion.initvx*motion.time;
t=0:0.01:motion.time;
motion.componentsx=motion.initvx.*t;
motion.componentsy=(motion.initvy.*t)-1/2*g.*t.^2;
figure('name',sprintf('UCUS BENZETIM %d',1),'numbertitle','off');
[maxx,idx] = max(motion.componentsx);
[maxy,idy] = max(motion.componentsy);
plot(motion.componentsx,motion.componentsy,motion.componentsx(idx),motion.componentsy(idx),'pr');
legend(sprintf('Max height = %0.3f',maxy),sprintf('Maximum range = %0.3f',maxx));
axis([xlim min(motion.componentsx) max(motion.componentsx)+1]);
trxt=('Max Range');
txt=('Maximum Height \uparrow');
text(motion.componentsx(length(t)),motion.componentsy(length(t)),trxt,'VerticalAlignment','bottom');
text(motion.rangemax/2,motion.hmax,txt,'HorizontalAlignment','right');

%%
% for j=1:20;
% ti(i,j)=motion.time(i)/(21-j);
% y(j)=motion.initvy(i)*ti(i,j)-1/2*g*ti(i,j)^2;
% x(j)=motion.initvx(i)*ti(i,j);
% motion.xvalue_for_spaced_time(i,j)=x(j);
% motion.yvalue_for_spaced_time(i,j)=y(j);
% end


