# Trajectory-Compression-Algorithm
### Overview
A research project on trajectory compression. We will implement three trajectory simplication algorithms (DP,FBQS,OPERB) in this repository.

### Prerequisite
+ python3
+ unrar
+ g++
+ make

### Test Douglas-Peucker algorithm on Taxi dataset

#### About the dataset
The taxi dataset on http://mashuai.buaa.edu.cn/traj.html include 100 trajectories collected by sensors on taxi. A trajectory has 39,100 data points on average. The size of the dataset is 36.3M

#### Get the Repository
```
git clone https://github.com/Hannnnnn/Trajectory-Compression-Algorithm.git
cd Trajectory-Compression-Algorithm
```
#### Download and Preprocess the Dataset
```
chmod 777 taxi_dataset.sh
./taxi_dataset.sh
```

#### Generate the Executable File and Get Result

```
cd src
make
./prog error_bound size
```
Note: error_bound means the error boundary(meters)
You can set error boundary when you run the program
Size means the number of trajectory the program will compress
Example: ./prog 10.0 100
This means the program will compress 100 trajectories with error bound 10 meters.



