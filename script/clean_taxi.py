import os

directory = '../dataset/taxi/'

n = 0
for n in range(0,101):
    file_name = 'A000' + str(n)
    path = os.path.join(directory,file_name)

    f = open(path,'r')
    output = open(os.path.join('../dataset/taxi_clean/',file_name),'w')

    for line in f.readlines():
            row = line.split(';')
            print(row)
            output.write(row[1]+' '+row[2]+' '+row[3]+'\n')

    f.close()
    output.close()