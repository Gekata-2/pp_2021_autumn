// Copyright 2021 Uglinskii Bogdan
#include <gtest/gtest.h>
#include <gtest-mpi-listener.hpp>
#include "./Cannon.h"

TEST(Cannon_MPI, Test_Seq_Multiply_Fixed) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  if (ProcRank == 0) {
    int size = 6;
    int exp_C[] = {21, 42, 63, 84, 105, 126, 21, 42, 63, 84, 105, 126,
                   21, 42, 63, 84, 105, 126, 21, 42, 63, 84, 105, 126,
                   21, 42, 63, 84, 105, 126, 21, 42, 63, 84, 105, 126};
    double* A = CreateEasyMatrix(size);
    double* B = CreateEasyMatrix(size);
    double* C = SeqMulti(size, A, B);
    int errors = 0;

    for (int i = 0; i < size * size; i++) {
      if (std::abs(exp_C[i] - C[i]) > 0.0000001) {
        errors = 1;
        break;
      }
    }
    ASSERT_EQ(0, errors);
  }
}

TEST(Cannon_MPI, Test_Parallel_Multiply_Fixed) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int size = 6;
  double* A = new double[size * size];
  double* B = new double[size * size];
  if (ProcRank == 0) {
    A = CreateEasyMatrix(size);
    B = CreateEasyMatrix(size);
  }

  double* C = ParallelMulti(size, A, B);
  if (ProcRank == 0) {
    int exp_C[] = {21, 42, 63, 84, 105, 126, 21, 42, 63, 84, 105, 126,
                   21, 42, 63, 84, 105, 126, 21, 42, 63, 84, 105, 126,
                   21, 42, 63, 84, 105, 126, 21, 42, 63, 84, 105, 126};

    int errors = 0;

    for (int i = 0; i < size * size; i++) {
      if (std::abs(exp_C[i] - C[i]) > 0.0000001) {
        errors = 1;
        break;
      }
    }
    ASSERT_EQ(0, errors);
  }
}

TEST(Cannon_MPI, Test_Parallel_Multiply_Random_10) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int size = 10;
  double* A = new double[size * size];
  double* B = new double[size * size];
  double* C_seq = new double[size * size];

  double t1, t2;
  double t_seq, t_parallel;
  if (ProcRank == 0) {
    A = CreateRandomMatrix(size);
    B = CreateRandomMatrix(size);
    t1 = MPI_Wtime();
    C_seq = SeqMulti(size, A, B);
    t2 = MPI_Wtime();
    t_seq = t2 - t1;
  }

  if (ProcRank == 0) {
    t1 = MPI_Wtime();
  }
  double* C_par = ParallelMulti(size, A, B);
  if (ProcRank == 0) {
    t2 = MPI_Wtime();
    t_parallel = t2 - t1;
    int errors = 0;

    for (int i = 0; i < size * size; i++) {
      if (std::abs(C_seq[i] - C_par[i]) > 0.0000001) {
        errors = 1;
        break;
      }
    }
    ASSERT_EQ(0, errors);
  }
}

TEST(Cannon_MPI, Test_Parallel_Multiply_Random_100) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int size = 100;
  double* A = new double[size * size];
  double* B = new double[size * size];
  double* C_seq = new double[size * size];

  double t1, t2;
  double t_seq, t_parallel;
  if (ProcRank == 0) {
    A = CreateRandomMatrix(size);
    B = CreateRandomMatrix(size);
    t1 = MPI_Wtime();
    C_seq = SeqMulti(size, A, B);
    t2 = MPI_Wtime();
    t_seq = t2 - t1;
  }

  if (ProcRank == 0) {
    t1 = MPI_Wtime();
  }
  double* C_par = ParallelMulti(size, A, B);
  if (ProcRank == 0) {
    t2 = MPI_Wtime();
    t_parallel = t2 - t1;
    int errors = 0;

    for (int i = 0; i < size * size; i++) {
      if (std::abs(C_seq[i] - C_par[i]) > 0.0000001) {
        errors = 1;
        break;
      }
    }
    ASSERT_EQ(0, errors);
  }
}

TEST(Cannon_MPI, Test_Parallel_Multiply_Random_500) {
  int ProcRank, ProcNum;
  MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

  int size = 500;
  double* A = new double[size * size];
  double* B = new double[size * size];
  double* C_seq = new double[size * size];

  double t1, t2;
  double t_seq, t_parallel;
  if (ProcRank == 0) {
    A = CreateRandomMatrix(size);
    B = CreateRandomMatrix(size);
    t1 = MPI_Wtime();
    C_seq = SeqMulti(size, A, B);
    t2 = MPI_Wtime();
    t_seq = t2 - t1;
  }

  if (ProcRank == 0) {
    t1 = MPI_Wtime();
  }
  double* C_par = ParallelMulti(size, A, B);
  if (ProcRank == 0) {
    t2 = MPI_Wtime();
    t_parallel = t2 - t1;
    int errors = 0;

    for (int i = 0; i < size * size; i++) {
      if (std::abs(C_seq[i] - C_par[i]) > 0.0000001) {
        errors = 1;
        break;
      }
    }
    ASSERT_EQ(0, errors);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();
  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
