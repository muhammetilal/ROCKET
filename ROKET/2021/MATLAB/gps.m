clc
clear
clear all


% a=37.0866;
% 
% b=29.35225;
% %transmitter
% tx = txsite('Name','MathWorks Apple Hill',...
%        'Latitude',a, ...
%        'Longitude',b,...
%         'TransmitterFrequency', 2.4e9, ...
%         'TransmitterPower', 18);
%    %show(tx);
%    
 %receiver
   rx = rxsite('Name','MathWorks Lakeside', ...
        'Latitude',37.1920547, ...
       'Longitude',29.3775272);
  
show(rx)


%    %distance
%    dm = distance(tx,rx); % Unit: m
%    dkm = dm / 1000; %unit:km
%    azFromEast = angle(tx,rx); % Unit: degrees counter-clockwise from East
%    azFromNorth = -azFromEast + 90; % Convert angle to clockwise from North
%    
%    ss = sigstrength(rx,tx);
%    margin = abs(rx.ReceiverSensitivity - ss); %hassassiyeti çýkararak ölçer
%    link(rx)
% %   figure
%  %  coverage(tx,rx)
%    %%coverage(tx,'close-in', ...
%      %%  'SignalStrengths',-100:5:-60) %sinyl gücüneg göre kapsadýðý alan
