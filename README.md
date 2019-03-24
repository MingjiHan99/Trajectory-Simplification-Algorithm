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

#### Generate the Exeutable File and Get Result

```
cd src
make
./prog
```



