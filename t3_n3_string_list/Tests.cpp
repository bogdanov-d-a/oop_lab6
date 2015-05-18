#include "stdafx.h"
#include "StringList.h"

using namespace std;

vector<string> StringListAsNormalVector(CStringList &list)
{
	vector<string> result;

	for (auto &str : list)
	{
		result.push_back(str);
	}

	return result;
}

vector<string> StringListAsReverseVector(CStringList &list)
{
	vector<string> result;

	if (list.begin() != list.end())
	{
		for (auto it = --list.end(); it != list.begin(); --it)
		{
			result.push_back(*it);
		}
		result.push_back(*list.begin());
	}

	return result;
}

bool const VectorsAreValid(vector<string> const& normal, vector<string> const& reverse)
{
	if (normal.size() != reverse.size())
	{
		return false;
	}

	for (size_t i = 0; i < normal.size(); ++i)
	{
		if (normal[i] != reverse[normal.size() - 1 - i])
		{
			return false;
		}
	}

	return true;
}

vector<string> StringListAsVector(CStringList &list)
{
	vector<string> normal(StringListAsNormalVector(list));
	vector<string> reverse(StringListAsReverseVector(list));
	assert(VectorsAreValid(normal, reverse));
	return normal;
}

BOOST_AUTO_TEST_CASE(TestEmptyList)
{
	CStringList l;
	BOOST_CHECK(l.begin() == l.end());
}

BOOST_AUTO_TEST_CASE(TestListInsertion)
{
	CStringList l;

	l.Insert(l.end(), "test");
	BOOST_CHECK(StringListAsVector(l) == vector<string>({ "test" }));

	l.Insert(l.begin(), "more");
	BOOST_CHECK(StringListAsVector(l) == vector<string>({ "more", "test" }));

	l.Insert(l.end(), "end");
	BOOST_CHECK(StringListAsVector(l) == vector<string>({ "more", "test", "end" }));

	l.Insert(++l.begin(), "middle");
	BOOST_CHECK(StringListAsVector(l) == vector<string>({ "more", "middle", "test", "end" }));
}

struct StringListFixture
{
	CStringList l;

	StringListFixture()
	{
		l.Insert(l.end(), "1");
		l.Insert(l.end(), "2");
		l.Insert(l.end(), "3");
		l.Insert(l.end(), "4");
		l.Insert(l.end(), "5");
	}
};

BOOST_FIXTURE_TEST_SUITE(StringList, StringListFixture)

BOOST_AUTO_TEST_CASE(CanObtainListBeginAndEnd)
{
	BOOST_CHECK_EQUAL(*l.begin(), "1");
	BOOST_CHECK_EQUAL(*--l.end(), "5");
}

BOOST_AUTO_TEST_CASE(CanIterateThroughList)
{
	auto it = l.begin();
	BOOST_CHECK_EQUAL(*it, "1");

	++it;
	BOOST_CHECK_EQUAL(*it, "2");

	++it;
	++it;
	BOOST_CHECK_EQUAL(*it, "4");

	--it;
	BOOST_CHECK_EQUAL(*it, "3");

	++it;
	++it;
	BOOST_CHECK_EQUAL(*it, "5");

	++it;
	--it;
	BOOST_CHECK_EQUAL(*it, "5");
}

BOOST_AUTO_TEST_CASE(TestListRemoval)
{
	l.Remove(l.begin());
	BOOST_CHECK(StringListAsVector(l) == vector<string>({ "2", "3", "4", "5" }));

	l.Remove(--l.end());
	BOOST_CHECK(StringListAsVector(l) == vector<string>({ "2", "3", "4" }));

	l.Remove(++l.begin());
	BOOST_CHECK(StringListAsVector(l) == vector<string>({ "2", "4" }));

	l.Remove(l.begin());
	BOOST_CHECK(StringListAsVector(l) == vector<string>({ "4" }));

	l.Remove(l.begin());
	BOOST_CHECK(StringListAsVector(l).empty());
}

BOOST_AUTO_TEST_SUITE_END()
