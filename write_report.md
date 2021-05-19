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



#### 2. Creation of the Training Set & Training Process

To capture good driving behavior, I first recorded two laps on track one using center lane driving. Here is an example image of center lane driving:

![alt text][image2]

I then recorded the vehicle recovering from the left side and right sides of the road back to center so that the vehicle would learn to .... These images show what a recovery looks like starting from ... :

![alt text][image3]
![alt text][image4]
![alt text][image5]


To augment the data sat, I also flipped images and angles thinking that this would avoid overfitting and make the model more generated. (code line 102 ~ 125). 
After the collection process, I had X number of data points. I then preprocessed this data by ...


I finally randomly shuffled the data set and put 20% of the data into a validation set. 

I used this training data for training the model. The validation set helped determine if the model was over or under fitting. The ideal number of epochs was 3 because my training result shows that the loss won't go significanty less after 3 epochs.
