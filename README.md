
### 1. Location of all major code, data, and results

* **Source Code**: All core code is located in the `/src` and `/include` folders, with the former containing the .cpp files and the latter containing .h. The `/tests` directory includes the test suites.
* **Data**: All data is located in the `/data` directory. This directory contains the Python Notebook used to actually query and download the dataset from BigQuery, as well as a few short subsets of the data, for simple testing purposes (mini_data.csv and tiny_data.csv). Because we did not push the data to GitHub, we set up a `make data` command that will automatically run all necessary scripts and freshly download the data in a new environment, that doesn't already have the data. 
* **Results**: Results can be found in the `/results` directory, labeled with the function from which they arose. 

### 2. Executable Instructions:

* `make data`   
* `make project`   
*  For BFS: `./project -f "data/data.csv" -b`  
*  For Dijkstra: `./project -f "data/data.csv" -d`  

The data input location is specified after the `-f` file, indicating to read from a file. The `-b`, `-d`, flags specify which graph algorithm should be run. 


### 3. Test Instructions

* `make data`   
*  `make test`  
*  `./test` will run all tests  
**_@akul add descriptions of the tests you wrote_**