How to compile:
    make all

**Note** You may run this code with or without calling `DMPlexSetClosurePermutationTensor()` Function on the DM for the unknowns (called parent DM below) or its Coordinate DM by using the command line options `-nolexDM` and `-nolexCoordDM`. These two flags can be used independently.

How to run: \
`./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1 ` \
or\
`./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1 -nolexDM -nolexCoordDM` 

Results for `./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1`

```
Parent DM:     permuted
Coordinate DM: permuted

Local Coordinates from CoordinateDM
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


Boundary Values
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

Results for `./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1 -nolexDM`
```
Parent DM:     not permuted
Coordinate DM: permuted

Local Coordinates from CoordinateDM
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


Boundary Values
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
Results for `./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1 -nolexCoordDM`
```
Parent DM:     permuted
Coordinate DM: not permuted

Local Coordinates from CoordinateDM
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


Boundary Values
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
Results for `./main -mesh cube_1e_6ss_s.exo -petscspace_degree 1 -nolexDM -nolexCoordDM`
```
Parent DM:     not permuted
Coordinate DM: not permuted

Local Coordinates from CoordinateDM
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


Boundary Values
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
