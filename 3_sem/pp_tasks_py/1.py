import argparse
import numpy as np
import multiprocessing as mp


def sum_row(row)-> int:
    return np.sum(row)


def input_matrix():
    parser = argparse.ArgumentParser(description="rows, columns")
    parser.add_argument("-r", "--rows", help="Input count of rows", type=int)
    parser.add_argument("-c", "--columns", help="Input count of columns", type=int)
    args = parser.parse_args()
    matrix=[]
    for i in range(args.rows):
        row=[]
        for j in range(args.columns):
            el=input(f"Input element [{i},{j}]: ")
            row.append(float(el))
        matrix.append(row)
    return np.array(matrix)


if __name__ == '__main__':
    matrix=input_matrix()
    print(f"Matrix:\n {matrix}")
    rows = [matrix[i, :] for i in range(matrix.shape[0])]
    with mp.Pool(20) as p:
         results=p.map(sum_row,rows)
    print(f"Sum: {np.sum(results)}")