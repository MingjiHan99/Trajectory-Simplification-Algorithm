import os

directory = '../dataset/truck/'

n = 0
for n in range(0,100):
    file_name = 'TK000' + str(n)
    path = os.path.join(directory,file_name)

    f = open(path,'r')
    output = open(os.path.join('../dataset/truck_map/',file_name),'w')
    count = 0
    for line in f.readlines():
            row = line.split(';')
            #print(row)
            output.write(row[2]+' '+row[3]+' '+row[1]+'\n')
            count += 1
            print(count)
            if count == 10000:
                break
    f.close()
    output.close()