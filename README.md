# My_Tiny_News

Code for Arduino on the car: car_distance_callRespond
-To cennect to the motor that make car run and avoid obstacle
Code for Proceesing in raspberry pi: GetPoto
- It used to check if the car is stopped and the lens is in the right side.



<h1>After connect to the raspi by SSH</h1>
1. To get the photo from raspberry pi, run this code in your laptop:

<code>rsync -avz -e ssh pi@lichipi:camera/ /Users/Siao/Desktop/camera</code>

2. To run the car, run this code in your laptop:
<code>
sudo Xvfb :1 -screen 0 1024x768x24 \</dev/null &</code>
<code>export DISPLAY=":1"</code>
<code>/home/pi/processing-3.3.5/processing-java --sketch=/home/pi/Desktop/GetPhoto --run
</code>
