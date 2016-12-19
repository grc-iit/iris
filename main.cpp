
#include "/usr/include/mpich/mpi.h"

int main() {
  MPI_Init();

  MPI_Wtime();
  doBenchmark(CM1);
  MPI_Wtime();

  MPI_Wtime();
  doBenchmark(WRF);
  MPI_Wtime();

  MPI_Finalize();
  return 0;
}