#include <gtest/gtest.h>

extern  "C" {
#include "../regresja.h"
}

// The fixture for testing class Foo.
class RegresjaBasic : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
  RegresjaConfig config;

  RegresjaBasic() {
     // You can do set-up work for each test here.
  }

  ~RegresjaBasic() override {
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

TEST_F(RegresjaBasic, init ) {
	float buffer[STEPS];
	EXPECT_EQ( regresja_init( &config, STEPS, buffer, 2.3f ), &config );
}

TEST_F(RegresjaBasic, EmptyBuffer ) {
	EXPECT_EQ( regresja_init( &config, STEPS, NULL, 2.3f ), &config );
}

TEST_F(RegresjaBasic, EmptyConfig ) {
	float buffer[STEPS];

	RegresjaConfig *pConfig = regresja_init( NULL, STEPS, buffer, 2.3f );
	EXPECT_NE( pConfig, nullptr );
}

TEST_F(RegresjaBasic, EmptyBoth ) {

	RegresjaConfig *pConfig = regresja_init( NULL, STEPS, NULL, 2.3f );
	EXPECT_NE( pConfig, nullptr );
}

TEST_F(RegresjaBasic, o5) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 0.1f ); 
	for( int i = 0; i < N; i++ )
	{
		float val = regresja( &config, (float)i );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			EXPECT_FLOAT_EQ( val, 10.0f );
		}
	}
  
}

TEST_F(RegresjaBasic, o10) {

	float buffer[STEPS];
	EXPECT_EQ( regresja_init( &config, STEPS, buffer, 1.0f ), &config );
	for( int i = 0; i < N; i++ )
	{
		float val = regresja( &config, (float)i );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			EXPECT_FLOAT_EQ( val, 1.0f );
		}
	}
	for( int i = N; i < 15; i++ ) {
		float val = regresja( &config, 2.0*i );
		if( i == 14 )
			EXPECT_FLOAT_EQ( val, 2.0 );
	}
  
}
