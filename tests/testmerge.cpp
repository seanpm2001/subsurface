#include "testmerge.h"
#include "core/dive.h"
#include "core/file.h"
#include "core/divelist.h"
#include <QTextStream>

void TestMerge::initTestCase()
{
	/* we need to manually tell that the resource exists, because we are using it as library. */
	Q_INIT_RESOURCE(subsurface);
}

void TestMerge::testMergeEmpty()
{
	/*
	 * check that we correctly merge mixed cylinder dives
	 */
	QCOMPARE(parse_file(SUBSURFACE_SOURCE "/dives/test47.xml"), 0);
	process_dives(true, false);
	QCOMPARE(parse_file(SUBSURFACE_SOURCE "/dives/test48.xml"), 0);
	process_dives(true, false);
	QCOMPARE(save_dives("./testmerge47+48.ssrf"), 0);
	QFile org(SUBSURFACE_SOURCE "/dives/test47+48.xml");
	org.open(QFile::ReadOnly);
	QFile out("./testmerge47+48.ssrf");
	out.open(QFile::ReadOnly);
	QTextStream orgS(&org);
	QTextStream outS(&out);
	QStringList readin = orgS.readAll().split("\n");
	QStringList written = outS.readAll().split("\n");
	while(readin.size() && written.size()){
		QCOMPARE(readin.takeFirst(), written.takeFirst());
	}
	clear_dive_file_data();
}

void TestMerge::testMergeBackwards()
{
	/*
	 * check that we correctly merge mixed cylinder dives
	 */
	QCOMPARE(parse_file(SUBSURFACE_SOURCE "/dives/test48.xml"), 0);
	process_dives(true, false);
	QCOMPARE(parse_file(SUBSURFACE_SOURCE "/dives/test47.xml"), 0);
	process_dives(true, false);
	QCOMPARE(save_dives("./testmerge47+48.ssrf"), 0);
	QFile org(SUBSURFACE_SOURCE "/dives/test47+48.xml");
	org.open(QFile::ReadOnly);
	QFile out("./testmerge47+48.ssrf");
	out.open(QFile::ReadOnly);
	QTextStream orgS(&org);
	QTextStream outS(&out);
	QStringList readin = orgS.readAll().split("\n");
	QStringList written = outS.readAll().split("\n");
	while(readin.size() && written.size()){
		QCOMPARE(readin.takeFirst(), written.takeFirst());
	}
	clear_dive_file_data();
}

QTEST_GUILESS_MAIN(TestMerge)
