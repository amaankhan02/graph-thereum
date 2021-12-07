
CS225 Final Project - GraphThereum

Aman Khinvasara, Amaan Khan, Akul Gupta, and Neil Kaushikkar

We began this final project with the goal of analyzing the recent transactions on the Ethereum blockchain, to better understand the costs/inefficiencies of utilizing such a blockchain network, as well as to prove or disprove the concept of decentralization.

We began by accessing the most recent ~1.4 million transactions on the network as our dataset.

Our first basic algorithm was a basic Breadth First Search/Traversal. Through the execution of this algorithm, which took about 10.7 seconds to run on EWS, we found out that these 1.4 million transactions (more precisely 1365188 edges) occured among only 123496 addresses on the network (vertices). The fact that there were 10 times as many transactions as there were individuals involved in the transaction was neither particularly surprising nor concerning. It is reasonable to expect that an individual who uses the network would use it more than once to transact. Additionally, the number wasn't extremely high, which would be concerning from a decentralization perspective. 

Here is the terminal output from running the BFS:
![Alt text](img/bfs_proof.PNG?raw=true "Title")

However, admittedly, this simple average heuristic is limited in the amount it can inform us about the decentralization (or lack thereof) of this network. For that, we will use the betweeness centrality algorithm, whose results you will see later.


