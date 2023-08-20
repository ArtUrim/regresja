#include <gtest/gtest.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

extern  "C" {
#include "../regresja.h"
}

// The fixture for testing class Foo.
class OneCurveTest : public ::testing::Test {
	static std::vector< std::vector<float> > vv;
	static bool initDone;
	static void initData();

 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  OneCurveTest() {
     // You can do set-up work for each test here.
	  if( initDone == false )
		  OneCurveTest::initData();
	  initDone = true;
  }

  ~OneCurveTest() override {
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

std::vector< std::vector<float> > OneCurveTest::vv( 9, std::vector<float>(20) );
bool OneCurveTest::initDone = false;
void OneCurveTest::initData()
{
	std::ifstream ifh("../octave/onecurve.csv");
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

	for( std::vector< std::vector<float> >::iterator il = vv.begin();
			il != vv.end(); il++ ) {
		for( std::vector<float>::iterator ip = (*il).begin(); ip != (*il).end(); ip++ )
		{
			std::cout << *ip << " ";
		}
		std::cout << std::endl;
	}
}

#define N 10
#define STEPS 5

// Tests that the Foo::Bar() method does Abc.
TEST_F(OneCurveTest, UpSlowEdge) {

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
