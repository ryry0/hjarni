PROJECT_DIR=../
SRC_DIR=$(PROJECT_DIR)/
TEST_DIR=$(PROJECT_DIR)/test

#specify where the source code and includes are located
#To compile biotilc, need access to local installation of eigen libraries
#Included as a system dir to ignore warnings
ARDUINO_EIGEN_DIR=/mnt/c/Users/Ryan/Desktop/arduino-1.8.1-windows/arduino-1.8.1/libraries/Eigen

INCLUDE_DIRS=$(SRC_DIR)/test $(SRC_DIR)
SRC_DIRS=$(SRC_DIR)/test
SRC_FILES=$(SRC_DIR)/PID.c $(SRC_DIR)/ring_buffer.c $(SRC_DIR)/numerical.c $(SRC_DIR)/gravity_compensator.c $(SRC_DIR)/biotilc.cpp

TEST_SRC_DIRS = $(TEST_DIR)

TEST_TARGET=hybrid_module_tests

# depends on your distribution! - built using WSL
CPPUTEST_HOME=/usr
CPPUTEST_ADDITIONAL_CFLAGS=--std=c11
CPPUTEST_ADDITIONAL_CXXFLAGS=-isystem $(ARDUINO_EIGEN_DIR)
CPPUTEST_EXE_FLAGS+=-c

# you may need to create a $(CPPUTEST_HOME)/lib directory and copy or link (/usr/lib/x86_64_linux_gnu/CppuTest.a
# and CppuTestExt.a to this directory

include MakefileWorker.mk
