from decimal import Decimal

if __name__ == '__main__':
    object = open("/home/zsq/ave_out.txt", "r")
    line = object.readline()
    i = 0
    time_sum = 0
    iter_sum = 0
    count_sum = 0
    lines = object.readlines()
    for line in lines:
        ave_time = str(line).split()[1]
        ave_iter = str(line).split()[2]
        count_num = str(line).split()[3]
        time_sum += float(ave_time)
        iter_sum += float(ave_iter)
        count_sum += float(count_num)
        i+=1

    time_sum = time_sum / i
    iter_sum = iter_sum / i
    count_sum = count_sum / i

    print(time_sum)
    print(iter_sum)
    print(count_sum)
    object.close()