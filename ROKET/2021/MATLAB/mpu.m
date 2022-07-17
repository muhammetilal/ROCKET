Fs = 100;
samplesPerRead = 10;
runTime = 20;
isVerbose = false;
useHW = true;
% Accelerometer axes parameters.
accelXAxisIndex = 1;
accelXAxisSign = 1;
accelYAxisIndex = 2;
accelYAxisSign = 1;
accelZAxisIndex = 3;
accelZAxisSign = 1;

% Gyroscope axes parameters.
gyroXAxisIndex = 1;
gyroXAxisSign = 1;
gyroYAxisIndex = 2;
gyroYAxisSign = 1;
gyroZAxisIndex = 3;
gyroZAxisSign = 1;

% Magnetometer axes parameters.
magXAxisIndex = 2;
magXAxisSign = 1;
magYAxisIndex = 1;
magYAxisSign = 1;
magZAxisIndex = 3;
magZAxisSign = -1;

% Helper functions used to align sensor data axes.

alignAccelAxes = @(in) [accelXAxisSign, accelYAxisSign, accelZAxisSign] ...
    .* in(:, [accelXAxisIndex, accelYAxisIndex, accelZAxisIndex]);

alignGyroAxes = @(in) [gyroXAxisSign, gyroYAxisSign, gyroZAxisSign] ...
    .* in(:, [gyroXAxisIndex, gyroYAxisIndex, gyroZAxisIndex]);

alignMagAxes = @(in) [magXAxisSign, magYAxisSign, magZAxisSign] ...
    .* in(:, [magXAxisIndex, magYAxisIndex, magZAxisIndex]);
compFilt = complementaryFilter('SampleRate', Fs);

compFilt = complementaryFilter('HasMagnetometer', false);

tuner = HelperOrientationFilterTuner(compFilt);

if useHW
    tic
else
    idx = 1:samplesPerRead;
    overrunIdx = 1;
end
while true
    if useHW
        [accel, gyro, mag, t, overrun] = imu();
        accel = alignAccelAxes(accel);
        gyro = alignGyroAxes(gyro);
    else
        accel = allAccel(idx,:);
        gyro = allGyro(idx,:);
        mag = allMag(idx,:);
        t = allT(idx,:);
        overrun = allOverrun(overrunIdx,:);

        idx = idx + samplesPerRead;
        overrunIdx = overrunIdx + 1;
        pause(samplesPerRead/Fs)
    end

    if (isVerbose && overrun > 0)
        fprintf('%d samples overrun ...\n', overrun);
    end

    q = compFilt(accel, gyro);
    update(tuner, q);

    if useHW
        if toc >= runTime
            break;
        end
    else
        if idx(end) > numSamplesAccelGyro
            break;
        end
    end
end