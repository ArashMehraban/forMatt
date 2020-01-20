CFLAGS           = -std=c99
FFLAGS           =
CPPFLAGS         =
FPPFLAGS         =

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules


all: main

main: main.o
	-${CLINKER} -o main main.o ${PETSC_KSP_LIB} ${PETSC_LIB} ${PETSC_SNES_LIB}
	${RM} main.o
