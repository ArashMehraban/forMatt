How to compile:
    make all

**Note** You may run this code with or without calling DMPlexSetClosurePermutationTensor() Function
by using the command line option -nolex


How to run: \
`./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1 ` \
or\
`./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1 -nolex` \

**The result from: `./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1:`**
```
Vec Object: coordinates 1 MPI processes
  type: seq
-0.5
-0.5
0.5
-0.5
-0.5
-0.5
-0.5
0.5
-0.5
-0.5
0.5
0.5
0.5
-0.5
0.5
0.5
-0.5
-0.5
0.5
0.5
-0.5
0.5
0.5
0.5


Xloc Size 24
Vec Object: 1 MPI processes
  type: seq
-0.5
-0.5
0.5
-0.5
0.5
0.5
-0.5
-0.5
-0.5
-0.5
0.5
-0.5
0.5
-0.5
0.5
0.5
-0.5
-0.5
0.5
0.5
0.5
0.5
0.5
-0.5
```

**The result from: `./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1 -nolex:`**
```
Vec Object: coordinates 1 MPI processes
  type: seq
-0.5
-0.5
0.5
-0.5
-0.5
-0.5
-0.5
0.5
-0.5
-0.5
0.5
0.5
0.5
-0.5
0.5
0.5
-0.5
-0.5
0.5
0.5
-0.5
0.5
0.5
0.5


Xloc Size 24
Vec Object: 1 MPI processes
  type: seq
-0.5
-0.5
0.5
-0.5
-0.5
-0.5
-0.5
0.5
-0.5
-0.5
0.5
0.5
0.5
-0.5
0.5
0.5
-0.5
-0.5
0.5
0.5
-0.5
0.5
0.5
0.5
```
