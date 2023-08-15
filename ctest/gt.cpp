#include <gtest/gtest.h>

extern  "C" {
#include "../regresja.h"
}

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  FooTest() {
     // You can do set-up work for each test here.
  }

  ~FooTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

#define N 10
#define STEPS 5

// Tests that the Foo::Bar() method does Abc.
TEST_F(FooTest, MethodBarDoesAbc) {

	float buffer[STEPS];
	regresja_init( STEPS, buffer, 0.1f ); 
	for( int i = 0; i < N; i++ )
	{
		float val = regresja( (float)i );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready(), false );
		} else {
			EXPECT_EQ( regresja_ready(), true );
			EXPECT_FLOAT_EQ( val, 10.0f );
		}
	}
  
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
