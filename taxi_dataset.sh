#!/bin/bash
cd ./dataset/
rm taxi.rar
wget "http://mashuai.buaa.edu.cn/DataSets/traj/taxi.rar" --user-agent="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.86 Safari/537.36"
unrar x taxi.rar
mkdir taxi_clean
cd ../script/
python3 clean_taxi.py
