I used a complete directed graph to check my program

Notes: Hello professor. I had a pretty rough night before attempting to finish this assignment. I wanted to say that the program works as expected till I try to list multiple paths.
I feel like the way I approached the implementation of the hasPath and listPaths methods in the driver file uses excessive code to accomplish the task ineffectively.

If you could point out what I was doing incorrectly or prehaps share your solution to this assignment for learning purposes then I'd greatly appreciate it.

CITIES :
Austin 
Chicago 
Dallas 
Denver

EDGES | WEIGHT :
Austin,Chicago |1000
Austin,Dallas |200
Chicago,Austin |1000
Chicago,Dallas |900
Dallas,Chicago |900
Dallas,Austin |200
Denver Chicago |500
Dallas Denver |300

NO CONNECTIONS :
Denver

DIRECT CONNECTIONS (List | Distance) :
Austin , Chicago |1000
Austin , Dallas |200
Chicago , Austin |1000
Chicago , Dallas |900
Dallas , Chicago |900
Dallas , Austin |200

THROUGH CONNECTIONS (List | Distance) :
Austin , Chicago , Dallas | 1900
Austin , Dallas , Chicago | 1100
Chicago , Austin , Dallas | 1200
Chicago , Dallas , Austin | 1100
Dallas , Chicago , Austin | 1900
Dallas , Austin , Chicago | 1200