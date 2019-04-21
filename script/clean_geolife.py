import os

directory = '../dataset/Geolife/Data'

n = 0
for n in range(68,69):
    sub_dir_name = str(n).zfill(3)
    folder = directory + '/' + sub_dir_name + '/Trajectory/'
    files = os.listdir(folder)
    file_name = str(n)
    output = open(os.path.join('../dataset/geo_clean/',file_name),'w')
    for f in files:
        file_name = folder + f
        print(file_name)
        open_f = open(file_name,'r')
        for line in open_f.readlines()[6:]:
            row = line.split(',')
            #print(row)
            output.write(row[4]+' '+row[0]+' '+row[1]+'\n')
        open_f.close()
    output.close()
    print(str(n) + " Done")