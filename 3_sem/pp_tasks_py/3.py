import argparse
import multiprocessing as mp

#keyword - person 
def search_keyword(keyword,file):
    with open(file,'r',encoding = 'utf-8') as f:
        lines=f.readlines()
        for line in lines:
            if keyword in line:
                print(f"keyword '{keyword}' in file {file}")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="keyword, files")
    parser.add_argument("-k", "--keyword", help="Input keyword", type=str)
    parser.add_argument("-f", "--files", nargs="+", help="Input list of files", type=str)
    args = parser.parse_args()
    with mp.Pool(20) as p:
        p.starmap(search_keyword,[(args.keyword,file) for file in args.files])
   