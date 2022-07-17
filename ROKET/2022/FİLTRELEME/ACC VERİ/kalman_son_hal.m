clc
clear
clear all
clf
real_value1=load("x.txt");
real_value2=load("y.txt");
real_value3=load("z.txt");
real_value=[real_value1 real_value2 real_value3];
filtered_valx=zeros(length(real_value),1);
filtered_valy=zeros(length(real_value),1);
filtered_valz=zeros(length(real_value),1);
for i=1:length(real_value)
    z=real_value(i,1:3);
[y,klm_gain] = muhammet(z);
 filtered_valx(i)=y(1,1);
  filtered_valy(i)=y(1,2);
   filtered_valz(i)=y(1,3);
   gain(i)=klm_gain(1);
end

plot(real_value1,'r');
hold on
plot(filtered_valx,'b');
ylabel('Degree')
xlabel('Sample')
legend('real value(red)','filtered value(blue)')
title('for x')
figure
plot(real_value2,'r');
ylabel('Degree')
xlabel('Sample')
hold on
plot(filtered_valy,'b');
legend('real value(red)','filtered value(blue)')
title('for y')
figure
plot(real_value3,'r');
ylabel('Degree')
xlabel('Sample')
hold on
plot(filtered_valz,'b');
legend('real value(red)','filtered value(blue)')
title('for z')
figure
plot(gain);
title('kalman gain');
%% simulation
% for i=10:length(real_value3)
% % subplot 311
% plot(real_value1(1:i),'r');
% hold on
% plot(filtered_valx(1:i),'b');
% % legend('real value(red)','filtered value(blue)')
% % title('for x')
% % subplot 312
% % plot(real_value2(i),'r');
% % hold on
% % plot(filtered_valy(i),'b');
% % legend('real value(red)','filtered value(blue)')
% % title('for y')
% % subplot 313
% % plot(real_value3(i),'r');
% % hold on
% % plot(filtered_valz(i),'b');
% % legend('real value(red)','filtered value(blue)')
% % title('for z')
% drawnow;
% end

