const char help[] = "Testing Coordinate Permutation Tensor\n";

#include <stdbool.h>
#include <string.h>
#include <petscdmplex.h>

PetscErrorCode BCTestFunction(PetscInt dim, PetscReal time, const PetscReal coords[],
                     PetscInt ncompu, PetscScalar *u, void *ctx) {

  PetscScalar x = coords[0];
  PetscScalar y = coords[1];
  PetscScalar z = coords[2];

  PetscFunctionBeginUser;

  u[0] = x;
  u[1] = y;
  u[2] = z;

  PetscFunctionReturn(0);
}

int main(int argc, char **argv) {
  PetscInt    ierr;
  MPI_Comm    comm;
  char        filename[PETSC_MAX_PATH_LEN];
  PetscBool   fileFlag = PETSC_FALSE;
  PetscBool   permTensorFlagDM = PETSC_FALSE;
  PetscBool   permTensorFlagCoordDM = PETSC_FALSE;
  DM          dm, distributedMesh;
  DM          dmcoord;
  PetscSection cs;
  PetscBool   interpolate = PETSC_TRUE;
  PetscPartitioner part;
  PetscFE     fe;
  Vec         coords, Xloc;

  // For Dirichlet (Essential) Boundary
  IS              faceSetIS;         //Index Set for Face Sets
  const char      *name="Face Sets"; //PETSc internal requirement
  PetscInt        numFaceSets;        //Number of FaceSets in faceSetIS
  const PetscInt  *faceSetIds;       //id of each FaceSet

  ierr = PetscInitialize(&argc, &argv, NULL, help);
  if(ierr)
    return ierr;

  comm = PETSC_COMM_WORLD;

  ierr = PetscOptionsBegin(comm, NULL,NULL ,NULL); CHKERRQ(ierr);
  //read in ExodusII mesh file
  ierr = PetscOptionsString("-mesh", "Read mesh from file", NULL,filename, filename, sizeof(filename), &fileFlag); CHKERRQ(ierr);
  #if !defined(PETSC_HAVE_EXODUSII)
  SETERRQ(comm, PETSC_ERR_ARG_WRONG,
          "ExodusII support needed. Reconfigure your Arch with --download-exodusii");
  #endif

  ierr = PetscOptionsBool("-nolexDM", "Not use DMPlexSetClosurePermutationTensor() for DM",
         NULL,permTensorFlagDM, &permTensorFlagDM, NULL); CHKERRQ(ierr);
  ierr = PetscOptionsBool("-nolexCoordDM", "Not use DMPlexSetClosurePermutationTensor() for CoordinateDM",
         NULL,permTensorFlagCoordDM, &permTensorFlagCoordDM, NULL); CHKERRQ(ierr);
  PetscOptionsEnd();

  //Create and distribute dm
  ierr = DMPlexCreateFromFile(comm, filename, interpolate, &dm); CHKERRQ(ierr);
  ierr = DMPlexGetPartitioner(dm, &part); CHKERRQ(ierr);
  ierr = PetscPartitionerSetFromOptions(part); CHKERRQ(ierr);
  ierr = DMPlexDistribute(dm, 0, NULL, &distributedMesh); CHKERRQ(ierr);
  if (distributedMesh) {
    ierr = DMDestroy(&dm); CHKERRQ(ierr);
    dm  = distributedMesh;
  }

 ierr = PetscPrintf(comm, "Parent DM:     %s\nCoordinate DM: %s\n\n", permTensorFlagDM ? "not permuted" : "permuted", permTensorFlagCoordDM ? "not permuted" : "permuted"); CHKERRQ(ierr);

  //Setup FE for DM
  PetscFECreateDefault(comm,3,3,PETSC_FALSE, NULL, PETSC_DETERMINE, &fe);
  // Setup DM
  ierr = DMSetFromOptions(dm); CHKERRQ(ierr);
  ierr = DMAddField(dm, NULL, (PetscObject)fe); CHKERRQ(ierr);
  // Add Dirichlet (Essential) boundray
  ierr = DMCreateDS(dm); CHKERRQ(ierr);
  ierr = DMGetLabelIdIS(dm, name, &faceSetIS); CHKERRQ(ierr);
  ierr = ISGetLocalSize(faceSetIS,&numFaceSets);
  ierr = ISGetIndices(faceSetIS, &faceSetIds); CHKERRQ(ierr);

  for (PetscInt i=0; i<numFaceSets; i++) {
    ierr = DMAddBoundary(dm,DM_BC_ESSENTIAL,NULL,"Face Sets",0,0,NULL,
                         (void(*)(void))BCTestFunction,1,&faceSetIds[i],
                         (void *)(&faceSetIds[i])); CHKERRQ(ierr);
  }
  ierr = ISRestoreIndices(faceSetIS, &faceSetIds); CHKERRQ(ierr);
  ierr = ISDestroy(&faceSetIS); CHKERRQ(ierr);
  if(!permTensorFlagDM){
      ierr = DMPlexSetClosurePermutationTensor(dm, PETSC_DETERMINE, NULL); CHKERRQ(ierr);
  }
  ierr = PetscFEDestroy(&fe); CHKERRQ(ierr);

  // Viewing the CoordinateDM
  ierr = DMGetCoordinateDM(dm, &dmcoord); CHKERRQ(ierr);
  ierr = DMGetCoordinateSection(dm, &cs); CHKERRQ(ierr);
  if(!permTensorFlagCoordDM){
    ierr = DMPlexSetClosurePermutationTensor(dmcoord, PETSC_DETERMINE, cs); CHKERRQ(ierr);
  }
  ierr = DMGetCoordinatesLocal(dm, &coords); CHKERRQ(ierr);

  ierr = PetscPrintf(comm, "Local Coordinates from CoordinateDM\n");CHKERRQ(ierr);
  ierr = VecView(coords,PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

  ierr = PetscPrintf(comm, "\n\n");CHKERRQ(ierr);

  // Viewing Coordinates in Essential Boundary Condition Function
  ierr = DMGetLocalVector(dm,&Xloc);CHKERRQ(ierr);
  PetscInt Xloc_sz;
  ierr = VecGetSize(Xloc, &Xloc_sz);CHKERRQ(ierr);

  ierr = PetscPrintf(comm, "Boundary Values\n");CHKERRQ(ierr);
  ierr = VecSet(Xloc, -42); // clearly not a boundary coordinate
  ierr = DMPlexInsertBoundaryValues(dm, PETSC_TRUE, Xloc, 0, NULL, NULL, NULL); CHKERRQ(ierr);
  ierr = VecView(Xloc,PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
  ierr =  DMRestoreLocalVector(dm,&Xloc);CHKERRQ(ierr);

  // Free objects
  ierr = VecDestroy(&Xloc); CHKERRQ(ierr);
  ierr = DMDestroy(&dm); CHKERRQ(ierr);

  return PetscFinalize();
}
