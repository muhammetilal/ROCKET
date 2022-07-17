clc
clear
clear all
%% motion model
function [Ad,Bd,R,n] = motion_model(example,dt)

% Provides discretized Ad(state update), Bd(control) and R(disturbance) 
% matrices for the motion model

% Inputs:
%       example   : Example under considertaion [1,2 or 3]
%       dt        : time interval in seconds

% Outputs:
%       Ad        : State update
%       Bd        : control
%       R         : Disturbance
%       n         : state dimension

% Example 1: Temperature
if example == 1
    Ad = 0.8;
    Bd = 3;
    R = 2;
    n = length(Ad(1,:));
end

% Example 2: 2D Omnidirectional AUV
if example == 2
    b = 1; % drag coefficient
    m = 2; % mass
    A = [ 0 1 0 0; 0 -b/m 0 0; 0 0 0 1; 0 0 0 -b/m];
    B = [0 0 ;1/m 0; 0 0; 0 1/m];
    C = [];
    D = 0;
    R = [.01 0 0 0; 0 .01 0 0; 0 0 .01 0; 0 0 0 .01];
    %R = [.001 0 0 0; 0 .001 0 0; 0 0 .001 0; 0 0 0 .001];
    %R = [.0001 0 0 0; 0 .0001 0 0; 0 0 .0001 0; 0 0 0 .0001];
    
    % Form continuous system
    sysc=ss(A,B,C,D);

    % zoh discretization
    sysd = c2d(sysc,dt,'zoh');
    Ad = sysd.A;
    Bd = sysd.B;
    
    n = length(Ad(1,:));
end

% Eample 3: Multirate 2D Omnidirectional AUV
if example == 3
    b = 1;
    m = 2;
    A = [ 0 1 0 0; 0 -b/m 0 0; 0 0 0 1; 0 0 0 -b/m];
    B = [0 0 ;1/m 0; 0 0; 0 1/m];
    R = [.0001 0 0 0; 0 .0001 0 0; 0 0 .0001 0; 0 0 0 .0001];
    
    n = length(A(1,:));
    C = [];
    D = 0;
    % Form continuous system
    sysc=ss(A,B,C,D);

    % zoh discretization
    sysd = c2d(sysc,dt,'zoh');
    Ad = sysd.A;
    Bd = sysd.B;
end

%% prediction update
function [mup, Sp] = ekf_prediction_update(Ad, R, mu, S)
    % prediction update
    mup = Ad * mu;
    Sp = Ad * S * transpose(Ad) + R;
end
%% measurement update
function [K, mu, S] = ekf_measurement_update(t, Ad, Ht, Q, y, mup, Sp)
    n = length(Ad(1,:));
    
    % measurement update
    K = Sp * transpose(Ht) * inv(Ht * Sp * transpose(Ht) + Q);
    mu = mup + K * (y(:,t) - sqrt(mup(1)^2 + mup(3)^2));
    S = (eye(n) - K * Ht) * Sp;
end

%%




%% Extended Kalman Filter Estimation
% Prediction update
mup = Ad*mu;
Sp = Ad*S*Ad' + R;
% Measurement update
Ht = [(mup(1))/(sqrt(mup(1)^2 + mup(3)^2)); 
0; (mup(3))/(sqrt(mup(1)^2 + mup(3)^2))] ;
K = Sp*Ht'*inv(Ht*Sp*Ht'+Q);
mu = mup + K*(y(:,t)-sqrt(mup(1)^2 + mup(3)^2));
S = (eye(n)-K*Ht)*Sp;
