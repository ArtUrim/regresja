#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

extern  "C" {
#include "../regresja.h"
}

// The fixture for testing class Foo.
class TwoCurvesTest : public ::testing::Test {
	static bool initDone;
	static void initData();

 protected:
	static std::vector< std::vector<float> > vv;
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TwoCurvesTest() {
     // You can do set-up work for each test here.
	  if( initDone == false )
		  TwoCurvesTest::initData();
	  initDone = true;
  }

  ~TwoCurvesTest() override {
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

std::vector< std::vector<float> > TwoCurvesTest::vv( 5, std::vector<float>(20) );
bool TwoCurvesTest::initDone = false;
void TwoCurvesTest::initData()
{
	std::ifstream ifh("../octave/edges2.csv");
	std::string line;
	if( ifh.good() )
	{
		int lnum = 0;
		while( std::getline( ifh, line ) ) {
			int pos = 0;
			std::vector<float> & rv = vv[lnum++];
			char *pch = strtok( const_cast<char *>(line.c_str()), "," );
			while( pch != NULL ) {
				try {
					rv.at(pos) =  atof( pch );
				} catch( std::out_of_range const & e ) {
					rv.resize( 2*rv.size() );
					rv[pos] = atof( pch );
				}
				pos++;
				pch = strtok( NULL, "," );
			}
			if( rv.size() > pos ) {
				rv.resize(pos);
			}
		}
	}
	ifh.close();
}

#define N 10
#define STEPS 5

TEST_F(TwoCurvesTest, Up123) {

	float buffer[STEPS];
	regresja_init( STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = TwoCurvesTest::vv[1].begin();
			it != TwoCurvesTest::vv[1].end(); it++ )
	{
		float val = regresja( *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready(), false );
		} else {
			EXPECT_EQ( regresja_ready(), true );
			if( i == 5 )
				EXPECT_FLOAT_EQ( val, 1.0f );
			else if( i == 14 )
				EXPECT_FLOAT_EQ( val, 2.0f );
			else if( i == 24 )
				EXPECT_FLOAT_EQ( val, 3.0f );
		}
		i++;
	}
  
}

TEST_F(TwoCurvesTest, Up132) {

	float buffer[STEPS];
	regresja_init( STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = TwoCurvesTest::vv[2].begin();
			it != TwoCurvesTest::vv[2].end(); it++ )
	{
		float val = regresja( *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready(), false );
		} else {
			EXPECT_EQ( regresja_ready(), true );
			if( i == 5 )
				EXPECT_FLOAT_EQ( val, 1.0f );
			else if( i == 14 )
				EXPECT_FLOAT_EQ( val, 3.0f );
			else if( i == 24 )
				EXPECT_FLOAT_EQ( val, 2.0f );
		}
		i++;
	}
  
}

TEST_F(TwoCurvesTest, Down123) {

	float buffer[STEPS];
	regresja_init( STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = TwoCurvesTest::vv[3].begin();
			it != TwoCurvesTest::vv[3].end(); it++ )
	{
		float val = regresja( *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready(), false );
		} else {
			EXPECT_EQ( regresja_ready(), true );
			if( i == 5 )
				EXPECT_FLOAT_EQ( val, -1.0f );
			else if( i == 14 )
				EXPECT_FLOAT_EQ( val, -2.0f );
			else if( i == 24 )
				EXPECT_FLOAT_EQ( val, -3.0f );
		}
		i++;
	}
  
}

TEST_F(TwoCurvesTest, Down132) {

	float buffer[STEPS];
	regresja_init( STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = TwoCurvesTest::vv[4].begin();
			it != TwoCurvesTest::vv[4].end(); it++ )
	{
		float val = regresja( *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready(), false );
		} else {
			EXPECT_EQ( regresja_ready(), true );
			if( i == 5 )
				EXPECT_FLOAT_EQ( val, -1.0f );
			else if( i == 14 )
				EXPECT_FLOAT_EQ( val, -3.0f );
			else if( i == 24 )
				EXPECT_FLOAT_EQ( val, -2.0f );
		}
		i++;
	}
  
}
