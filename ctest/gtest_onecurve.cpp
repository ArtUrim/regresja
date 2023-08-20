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
	static bool initDone;
	static void initData();

 protected:
	static std::vector< std::vector<float> > vv;
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  RegresjaConfig config;

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
}

#define N 10
#define STEPS 5

TEST_F(OneCurveTest, UpSlowEdge) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = OneCurveTest::vv[1].begin();
			it != OneCurveTest::vv[1].end(); it++ )
	{
		float val = regresja( &config, *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			if( i == 5 )
				EXPECT_FLOAT_EQ( val, 1.0f );
			else if( i == 20 )
				EXPECT_FLOAT_EQ( val, 2.0f );
		}
		i++;
	}
  
}

TEST_F(OneCurveTest, UpFastEdge) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = OneCurveTest::vv[2].begin();
			it != OneCurveTest::vv[2].end(); it++ )
	{
		float val = regresja( &config, *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			if( i == 5 )
				EXPECT_FLOAT_EQ( val, 2.0f );
			else if( i == 20 )
				EXPECT_FLOAT_EQ( val, 1.0f );
		}
		i++;
	}
  
}

TEST_F(OneCurveTest, DownSlowEdge) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = OneCurveTest::vv[3].begin();
			it != OneCurveTest::vv[3].end(); it++ )
	{
		float val = regresja( &config, *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			if( i == 5 )
				EXPECT_FLOAT_EQ( val, -1.0f );
			else if( i == 20 )
				EXPECT_FLOAT_EQ( val, -2.0f );
		}
		i++;
	}
  
}

TEST_F(OneCurveTest, DownFastEdge) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = OneCurveTest::vv[4].begin();
			it != OneCurveTest::vv[4].end(); it++ )
	{
		float val = regresja( &config, *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			if( i == 5 )
				EXPECT_FLOAT_EQ( val, -2.0f );
			else if( i == 20 )
				EXPECT_FLOAT_EQ( val, -1.0f );
		}
		i++;
	}
  
}

TEST_F(OneCurveTest, UpSlowSmooth) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = OneCurveTest::vv[5].begin();
			it != OneCurveTest::vv[5].end(); it++ )
	{
		float val = regresja( &config, *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			if( i == 4 )
				EXPECT_FLOAT_EQ( val, 1.0f );
			else if( i == 20 )
				EXPECT_FLOAT_EQ( val, 2.0f );
		}
		i++;
	}
  
}

TEST_F(OneCurveTest, UpFastSmooth) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = OneCurveTest::vv[6].begin();
			it != OneCurveTest::vv[6].end(); it++ )
	{
		float val = regresja( &config, *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			if( i == 4 )
				EXPECT_FLOAT_EQ( val, 2.0f );
			else if( i == 20 )
				EXPECT_FLOAT_EQ( val, 1.0f );
		}
		i++;
	}
  
}

TEST_F(OneCurveTest, DownSlowSmooth) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = OneCurveTest::vv[7].begin();
			it != OneCurveTest::vv[7].end(); it++ )
	{
		float val = regresja( &config, *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			if( i == 4 )
				EXPECT_FLOAT_EQ( val, -1.0f );
			else if( i == 20 )
				EXPECT_FLOAT_EQ( val, -2.0f );
		}
		i++;
	}
  
}

TEST_F(OneCurveTest, DownFastSmooth) {

	float buffer[STEPS];
	regresja_init( &config, STEPS, buffer, 1.0f ); 

	int i = 0;
	for( std::vector<float>::iterator it = OneCurveTest::vv[8].begin();
			it != OneCurveTest::vv[8].end(); it++ )
	{
		float val = regresja( &config, *it );
		if( i < 4 )
		{
			EXPECT_EQ( regresja_ready( &config), false );
		} else {
			EXPECT_EQ( regresja_ready( &config), true );
			if( i == 4 )
				EXPECT_FLOAT_EQ( val, -2.0f );
			else if( i == 20 )
				EXPECT_FLOAT_EQ( val, -1.0f );
		}
		i++;
	}
  
}
