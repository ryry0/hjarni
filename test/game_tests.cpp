
#include "CppUTest/TestHarness.h"
#include "PID.h"

pid_data_t pid;
const float MAX_INTEGRAL_GUARD = 1.0f;
const float MIN_INTEGRAL_GUARD = -1.0f;
const float EPSILON = 0.05f;

TEST_GROUP(PIDTestGroup)
{
  void setup() {
    pid_init(&pid, 1.0f, 1.0f, 0.1f, MIN_INTEGRAL_GUARD, MAX_INTEGRAL_GUARD);
  }

  void teardown() {
  }
};

TEST(PIDTestGroup, MaxTest_velocUpdate)
{
  float output = 0;

  for (size_t i = 0; i < 100; ++i) {
    output = pid_FeedbackCtrl(&pid, 2.0f, 0.0f, 0.01f, pid_velocUpdate);
  }

  DOUBLES_EQUAL(MAX_INTEGRAL_GUARD, output, EPSILON);
}

TEST(PIDTestGroup, MinTest_velocUpdate)
{
  float output = 0;

  for (size_t i = 0; i < 100; ++i) {
    output = pid_FeedbackCtrl(&pid, -2.0f, 0.0f, 0.01f, pid_velocUpdate);
  }

  DOUBLES_EQUAL(MIN_INTEGRAL_GUARD, output, EPSILON);
}

TEST(PIDTestGroup, MaxTest_minPIUpdate)
{
  float output = 0;

  for (size_t i = 0; i < 100; ++i) {
    output = pid_FeedbackCtrl(&pid, 2.0f, 0.0f, 0.01f, pid_minPIUpdate);
  }

  DOUBLES_EQUAL(MAX_INTEGRAL_GUARD, output, EPSILON);
}


TEST(PIDTestGroup, MinTest_minPIUpdate)
{
  float output = 0;

  for (size_t i = 0; i < 100; ++i) {
    output = pid_FeedbackCtrl(&pid, -2.0f, 0.0f, 0.01f, pid_minPIUpdate);
  }

  DOUBLES_EQUAL(MIN_INTEGRAL_GUARD, output, EPSILON);
}

TEST(PIDTestGroup, SecondTest) {
  //STRCMP_EQUAL("hello", "world");
  //LONGS_EQUAL(1, 2);
  //CHECK(false);
  //FAIL("Fail me!");
}


