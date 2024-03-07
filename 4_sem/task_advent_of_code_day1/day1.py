import re
def part_1():
    with open('abc.txt','r') as file:
        print(sum([int(re.search(r'\d', line).__getitem__(0)+re.search(r'\d', line[::-1]).__getitem__(0)) for line in file.readlines()]))
    
def part_2():
    digits={ 'one':'o1e' , 'two':'t2o' , 'three':'t3e', 'four':'f4r' , 'five':'f5e' , 'six':'s6x' , 'seven':'s7n', 'eight':'e8t', 'nine':'n9e'}
    
    with open('test.txt','r') as file:
        with open('w.txt','w') as f:
            sum=0
            for line in file.readlines():
                for i in range(0,len(line)-5):
                    for key in digits.keys():
                        if key in line: 
                            line=line.replace(key,digits.get(key))                
                sum+=int(re.search(r'\d', line).__getitem__(0)+re.search(r'\d', line[::-1]).__getitem__(0))
    print(sum)

if __name__=='__main__':
    part_2()
    