
### 1. Location of all major code, data, and results

* **Source Code**: All core code is located in the `/src` and `/include` folders, with the former containing the .cpp files and the latter containing .h. The `/tests` directory includes the test suites.
* **Data**: All data is located in the `/data` directory. This directory contains the Python Notebook used to actually query and download the dataset from BigQuery, as well as a few short subsets of the data, for simple testing purposes (mini_data.csv and tiny_data.csv). Because we did not push the data to GitHub, we set up a `make data` command that will automatically run all necessary scripts and freshly download the data in a new environment, that doesn't already have the data. 
* **Results**: Results can be found in the `/results` directory, labeled with the function from which they arose. 

### 2. Executable Instructions:

* `make data`: Download the necessary data files from Azure Cloud.
* `make project`: Compile the source code and form the project executable.
* `make test`: Compile the source code and test code and form the test executable.

We have provided an interface for customizing how the executable is run using command line arguments. These arguments can be mixed and matched in any order and in any combination. The following commands demonstrate only combining a few command line flags at a time for simplicity, but note that they can be strung all together. Also note that the `-f` flag is the only required flag. It is used to specify the file to load the graph from. 
* `-f <filepath>`: Load a graph into memory using the CSV file at the given filepath. 
* `-b`: Perform a BFS on the graph and print the status of the search.
* `-l <filepath>`: Run a modified BFS on the graph to find the largest connected component and save the graph representing the largest connected component to the file specified in the given path.
* `-d`: Run Dijkstra's algorithm on the graph and save the results of the algorithm to a csv file.
* `-c <int>`: Run Brandes' betweenness centrality (BC) algorithm and print out the BC of each of the `<int>` vertices with the highest BC.
* `-t <int>`: If the user elected to run Brandes' algorithm, this parameter specifies the number of threads to use when running the algorithm. If the number specified is less than or equal to 1, the algorithm will run on a single thread. If the number is larger than 1, the algorithm will run on the number of threads specified. Note that due to measures taken to prevent data races, the amount of memory used is directly proportional to the number of threads as each thread receives its own copy of the graph loaded in memory at the start of the program. 
* `-v`: If the user elected to run Brandes' algorithm with multiple threads and this this argument is specified, the program will print out the status of each thread after chunks of work have been completed by each thread.

Here are some cool example variations of our executable we think you should run...
* `./project -f data/data.csv -b -l data/largest_cc.csv`: Load the large dataset from `data/data.csv`, perform a BFS to visit all vertices and edges, and find the largest connected component and save it to `data/largest_cc.csv`.
* `./project -f data/10mb_data.csv -c 10 -t 15`: Load the moderately sized dataset and compute the betweenness centrality of each node by distrubuting work between 15 threads before printing out the betweenness centrality of the 10 vertices with the largest centrality.
* `./project -f data/data.csv -d`: Run Dijkstra's algorithm on the large dataset from `data/data.csv`.

### 3. Test Instructions

* `make data`   
*  `make test`  
*  `./test` will run all tests  
**_@akul add descriptions of the tests you wrote_**