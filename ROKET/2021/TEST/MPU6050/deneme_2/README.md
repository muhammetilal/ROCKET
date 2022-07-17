# MPU6050 3D Tilt Visualization
## WARN! Before you start

There are many steps that you have to complete to implement this sketch successfully:
  - Install [MPU6050 library]
  - Check MPU6050 offset values to verify G values on axes
  
You can watch the demo video: [YouTube Video]

## Hardware Connection
#### Arduino - MPU6050 (i2c)

| Arduino | MPU6050 |
| ------ | ------ |
| 5V | Vcc |
| GND | GND |
| A4 | SDA |
| A5 | SCL |

#### Arduino - MATLAB (Serial)

| Arduino | MPU6050 |
| ------ | ------ |
| USB | USB |

About
----
This is a part of our project and it is the first draft of the code. We will develop it.


**Free Software, Hell Yeah!**

[MPU6050 library]: <https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050>
[YouTube Video]: <https://youtu.be/0MM6cKzimXs>
