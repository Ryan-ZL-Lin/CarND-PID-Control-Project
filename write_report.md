# **PID Control** 


**PID Control Project**

The goals / steps of this project are the following:
* Convert the PID Control mchanism from Python (available from the course) to C++
* Implement twiddle algorithm to optimize the 3 parameters used in PID.
* Run the simulator with "twiddle" enabled to find the optimized parameters.
* Test the optimized parameters on simulator to complete at least one lap.
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./examples/placeholder.png "Model Visualization"


## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/1972/view) individually and describe how I addressed each point in my implementation.  

---
### Compilation

#### 1. Code must compile without errors with cmake and make.

My project includes the following files:
* main.cpp
* PID.h
* PID.cpp
* PID_Contro.mp4 (stored on google drive, available via video/video_link.txt)
* writeup_report.md summarizing the results

#### 2. Given that we've made CMakeLists.txt as general as possible, it's recommend that you do not change it unless you can guarantee that your changes will still compile on any platform.
No change on akeLists.txt 


### Implementation

#### 1. The PID procedure follows what was taught in the lessons.

The PID procedure that I implemented is folloiwng what was taught in the lessons, you could find the PID parameters in PID.h and PID.cpp.
In Main.cpp: 
* Invoke "UpdateError" function to update the error of P, I and D regularly. (code line 107)
* Invoke "TotalError" function to calculate the steering value. (code line 108)




### Reflection

#### 1. Describe the effect each of the P, I, D components had in your implementation.

When navigating the Udacity Knowledge forumn to have an initial idea how to use PID class properly, I found out that there was a blog (https://medium.com/intro-to-artificial-intelligence/pid-controller-udacitys-self-driving-car-nanodegree-c4fd15bdc981) that describes the effect of P, I and D componenets clearly with videos as visual aids. 

Here are the main points: 
* Car started to oscillate when KP value set to 0.05 whereas Ki and Kd set to zero. (expected result as the lessons say)
* Then found the Kd value set to 1.5 stops the oscillating behaviour along with 0.05 for Kp and zero for Ki. (expected result as the lessons say)
* Finally value Ki set as 0.0001 to reduce the steady-state error.

Hence, my initial parameters for P, I and D is 0.05, 0.0001 and 1.5. 


#### 2. Describe how the final hyperparameters were chosen.

To choose the final hyperparameters in PID procedure, I implemented the 


### Simulation

#### 1. The vehicle must successfully drive a lap around the track.

