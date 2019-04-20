import os

directory = '../dataset/taxi/'

n = 0
for n in range(0,1):
    file_name = 'A000' + str(n)
    path = os.path.join(directory,file_name)

    f = open(path,'r')
    output = open(os.path.join('../dataset/taxi_clean/',file_name),'w')
    count = 0
    for line in f.readlines():
            row = line.split(';')
            #print(row)
            output.write(row[2]+' '+row[3]+' '+row[1]+'\n')
            
    f.close()
    output.close()