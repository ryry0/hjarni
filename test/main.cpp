/**
 * \file
 * \author Ryan-David Reyes
 *
 * \brief Tests are done using the Cpputest unit testing framework.
 */

#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char ** av) {
  return CommandLineTestRunner::RunAllTests(ac, av);
}
