clc
clear
clear all
x=1:1:40;%dakika
ayse=x;
veli=randi([1,5],1,length(x));
ali=round(1.5.^x);
ahmet=round(exp(x)+1);
subplot 411
plot(x,ayse);
title('ayse');
xlabel('zaman(dk)');
ylabel('soru sayisi');

subplot 412
plot(x,ali);
title('ali');
xlabel('zaman(dk)');
ylabel('soru sayisi');
subplot 413
plot(x,ahmet);
title('ahmet');
xlabel('zaman(dk)');
ylabel('soru sayisi');
subplot 414
plot(x,veli);
title('veli');
xlabel('zaman(dk)');
ylabel('soru sayisi');
%%%%%%%%%%%%%%%%%%%%%%
figure
for i=1:40;
    plot(x(1:i+1),veli(1:i+1));
    title('veli');
xlabel('zaman(dk)');
ylabel('soru sayisi');
    pause(0.2)
    drawnow;
end