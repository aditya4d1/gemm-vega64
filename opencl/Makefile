CC=g++
INC_FLAGS=/opt/rocm/opencl/include
LIB_DIR=/opt/rocm/opencl/lib/x86_64
LIB=OpenCL
CLANG=clang

all: sgemm_v1

sgemm_v1:
	mkdir -p bin
	$(CC) -I$(INC_FLAGS) -I./inc sgemm_v1.cpp -L$(LIB_DIR) -l$(LIB) -o ./bin/sgemm_v1

sgemm_v2:
	mkdir -p bin
	$(CC) -I$(INC_FLAGS) -I./inc sgemm_v2.cpp -L$(LIB_DIR) -l$(LIB) -o ./bin/sgemm_v2

sgemm_v3:
	mkdir -p bin
	$(CC) -I$(INC_FLAGS) -I./inc sgemm_v3.cpp -L$(LIB_DIR) -l$(LIB) -o ./bin/sgemm_v3

clean:
	rm -rf ./bin a.out


