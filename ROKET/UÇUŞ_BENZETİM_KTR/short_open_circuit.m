ax1=axes('Position',[0.13  .49  .865  .25],'Units', 'normalized');
x1=[0.2  0.2  .875];
y1=[0.8  1.2  1.2];
x2=[1.1  1.6];
y2=[1.2  1.2];
x3 = [2.0  2.4 2.4];
y3 = [1.2 1.2  .9];
x4 = [2.4  2.4 .2  .2];
y4 = [ .3  0   0   .4];
th=0:.0025:2*pi;
xv=0.2+0.2*cos(th);
yv=0.6 +0.2*sin(th);
xA= 1.8+0.2*cos(th);
yA=1.2 +0.2*sin(th);
thw1=-pi/3:.0025:pi;
thw2= 0:.0025:4*pi/3;
xw1= .95+0.075*cos(thw1);
yw1= 1.2 +0.075*sin(thw1);
xw2= 1.025+0.075*cos(thw2);
yw2= 1.2 +0.075*sin(thw2);
thv = 0:.0025:pi;
xp1 =0.85+0.05*cos(thv);
yp1 = 1 +0.05*sin(thv);
xp2 =.95+0.05*cos(thv);
xp3 =1.05+0.05*cos(thv);
x5 = [0.75 0.75 .8];
y5 =[1.2 1.0 1.0];
x6 = [1.1 1.3 1.3];
y6 = [1.0 1.0  0];
xw = [0.65  0.65  1.4  1.4  0.65];
yw = [0.95  1.35  1.35  0.95  0.95];
tho=-pi/2:.0025:pi/2;
xo=2.4+0.1*cos(tho);
yo=.1*sin(tho);
xt1=[xo     xo      xo] ;
yt1=[.4+yo 0.6+yo 0.8+yo];
xo2=3.0 -0.1*cos(tho);
yo2=.1*sin(tho);
xt2=[xo2     xo2      xo2] ;
yt2=[.4+yo2 0.6+yo2 0.8+yo2];
xt3 = [3.0  3.0 3.6];
yt3 = [0.9  1.2  1.2];
xt4 = [3.0  3.0  3.6];
yt4 = [ .3  0   0];
xc1=[2.65 2.65 ];
xc2=[2.75 2.75];
yc1=[.4  .8];
xt3b = [3.0  3.0 3.8];
xt4b = [3.0  3.0  3.8];

% Open Circuit
plot(x1, y1,'b', x2,y2,'b',x3, y3, 'b', x4, y4, 'b', 'erasemode','none')
axis('equal')
axis off
hold on
plot(xv,yv,'b', xA, yA, 'b', xw1, yw1, 'b', xw2, yw2, 'b')
plot(xp1,yp1,'b', xp2,yp1, 'b', xp3,yp1,'b', x5, y5, 'b', x6, y6, 'b', xw, yw, 'b') 
plot(xt1, yt1, 'b', xt2, yt2, 'b', xt3, yt3 ,'b', xt4, yt4, 'b')
plot(xc1, yc1, 'b', xc2, yc1, 'b')
text(.185,1.17, '\circ')
text(.185,-.0325, '\circ')
text(3.55,1.17, '\circ')
text(3.58,-.0325, '\circ')
text(.14, .6, 'V', 'Fontsize', 9, 'color', [0 0 1])
text(1.755, 1.2, 'A', 'Fontsize', 9, 'color', [0 0 1])
text(.6, .85, 'Wattmeter', 'Fontsize', 8, 'color', [0 0 1])
text(3.2, .7, 'Open', 'Fontsize', 9, 'color', [0 0 1])
text(3.2, .52, 'Circuit', 'Fontsize', 9, 'color', [0 0 1])

% Short Circuit
plot(4.9+x1, y1,'b', 4.9+x2,y2,'b',4.9+x3, y3, 'b', 4.9+x4, y4, 'b', 'erasemode','none')

plot(4.9+xv,yv,'b', 4.9+xA, yA, 'b', 4.9+xw1, yw1, 'b', 4.9+xw2, yw2, 'b')
plot(4.9+xp1,yp1,'b', 4.9+xp2,yp1, 'b', 4.9+xp3,yp1,'b', 4.9+x5, y5, 'b', 4.9+x6, y6, 'b', 4.9+xw, yw, 'b') 
plot(4.9+xt1, yt1, 'b', 4.9+xt2, yt2, 'b', 4.9+xt3b, yt3 ,'b', 4.9+xt4b, yt4, 'b')
plot(4.9+xc1, yc1, 'b', 4.9+xc2, yc1, 'b')
xs=[9  9];
ys=[0  1.2];
plot(xs, ys, 'Color', [0.87, 0.83, 0.75])
plot(xs-0.3, ys, 'Color', 'r')

text(4.9+.2,1.17, '\circ')
text(4.9+.2,-.031, '\circ')
text(4.9+3.8,1.17, '\circ')
text(4.9+3.8,-.031, '\circ')
text(4.9+.15, .6, 'V', 'Fontsize', 9, 'color', [0 0 1])
text(4.9+1.78, 1.2, 'A', 'Fontsize', 9, 'color', [0 0 1])
text(4.9+.6, .85, 'Wattmeter', 'Fontsize', 9, 'color', [0 0 1])
text(4.9+3.2, .7, 'Short', 'Fontsize', 9, 'color', [0 0 1])
text(4.9+3.2, .52, 'Circuit', 'Fontsize', 9, 'color', [0 0 1])
hold off