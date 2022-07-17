clear all
a = arduino('COM3','Uno');
for i=1:20
writeDigitalPin(a,'D7',1);
pause(2);
writeDigitalPin(a,'D7',0);
pause(2)
end
imu = mpu6050(a,'SampleRate',50,'SamplesPerRead',5,'ReadMode','Latest')