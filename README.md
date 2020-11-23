# TBB Mergesort
An implementation of a parallel MergeSort using Threaded Building Blocks.

## Parameters
- Read from file
    - Sort by Name then Graduation Date
    ```
    tbb-merge <num_threads> -a -n  <inputFile> <outputFile>  
    ```
    - Sort by Graduation Date then Name
    ```
    tbb-merge <num_threads> -a -d <inputFile> <outputFile>
    ```
- Generate random ints
    - Run the following command
    ```
    tbb-merge <num_threads> -i <num_ints> <unsortedOutputFile> <outputFile>
    ```

## Compiling
1. Clone the repository with the following command
```
git clone https://gitlab.com/enochlev/TBB-MergeSort.git
```
2. Navigate to the directory containing the code
3. Run the following code to compile
```
g++ code.cpp -ltbb -O2 -o tbb-merge
```

## Execution
1. Navigate to the directory containing the code
2. Run the following command
```
./a.out
```

### Note
Code Built by 
Enoch Levandovsky 
Nathan Teeter
Jacob Winters
