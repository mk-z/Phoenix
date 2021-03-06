#include "SceneTestSuite.h"
#include "DHCPClientTest.h"
#include "ARPClientTest.h"
#include "DZPLIBTEST.h"
#include "DHLIBTEST.h"
#include "HKLIBTEST.h"
#include "DownloadContainerTest.h"
#include "SearchFileTest.h"
#include "UtilityTest.h"
#include "YSLIBTEST.h"

CppUnit::Test* SceneTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SceneTestSuite");

//	pSuite->addTest(DZPLIBTEST::suite());

	/*
	pSuite->addTest(DownloadContainerTest::suite());
	pSuite->addTest(SearchFileTest::suite());
	pSuite->addTest(DHCPClientTest::suite());
	pSuite->addTest(ARPClientTest::suite());
	//pSuite->addTest(DZPLIBTEST::suite());
	pSuite->addTest(DHLIBTEST::suite());
	pSuite->addTest(HKLIBTEST::suite());*/
	pSuite->addTest(YSLIBTEST::suite());

	//pSuite->addTest(UtilityTest::suite());

	return pSuite;
}
