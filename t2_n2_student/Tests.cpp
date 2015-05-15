#include "stdafx.h"
#include "Student.h"

using namespace std;

BOOST_AUTO_TEST_CASE(StudentPropertiesAreWorking)
{
	CStudent s("name", "surname", "patronymic", 20);
	BOOST_CHECK_EQUAL(s.GetName(), "name");
	BOOST_CHECK_EQUAL(s.GetSurname(), "surname");
	BOOST_CHECK_EQUAL(s.GetPatronymic(), "patronymic");
	BOOST_CHECK_EQUAL(s.GetAge(), 20u);
}

BOOST_AUTO_TEST_CASE(SpacesCanBeUsedInStudentNameComponents)
{
	CStudent s("name ", "sur name", "    patronymic", 20);
}

BOOST_AUTO_TEST_CASE(CantCreateStudentWithEmptyNameOrSurname)
{
	BOOST_CHECK_THROW(CStudent s("", "surname", "patronymic", 20), invalid_argument);
	BOOST_CHECK_THROW(CStudent s("name", "", "patronymic", 20), invalid_argument);
}

BOOST_AUTO_TEST_CASE(CanCreateStudentWithEmptyPatronymic)
{
	CStudent s("name", "surname", "", 20);
}

BOOST_AUTO_TEST_CASE(CantCreateStudentWithBadNameComponent)
{
	BOOST_CHECK_THROW(CStudent s(" ", "surname", "patronymic", 20), invalid_argument);
	BOOST_CHECK_THROW(CStudent s("name", "     ", "patronymic", 20), invalid_argument);
	BOOST_CHECK_THROW(CStudent s("name", "surname", "  ", 20), invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestStudentAgeLimit)
{
	BOOST_CHECK_THROW(CStudent s("name", "surname", "patronymic", 13), out_of_range);
	{ CStudent s("name", "surname", "patronymic", 14); }
	{ CStudent s("name", "surname", "patronymic", 60); }
	BOOST_CHECK_THROW(CStudent s("name", "surname", "patronymic", 61), out_of_range);
}

BOOST_AUTO_TEST_CASE(StudentCanBeRenamed)
{
	CStudent s("name", "surname", "patronymic", 20);
	s.Rename("name2", "surname2", "patronymic2");
	BOOST_CHECK_EQUAL(s.GetName(), "name2");
	BOOST_CHECK_EQUAL(s.GetSurname(), "surname2");
	BOOST_CHECK_EQUAL(s.GetPatronymic(), "patronymic2");
}

BOOST_AUTO_TEST_CASE(StudentRenameFailsCantDamageItsData)
{
	CStudent original("name", "surname", "patronymic", 20);
	CStudent copy(original);

	BOOST_CHECK_THROW(copy.Rename("", "surname", "patronymic"), invalid_argument);
	BOOST_CHECK(original == copy);

	BOOST_CHECK_THROW(copy.Rename("name", "", "patronymic"), invalid_argument);
	BOOST_CHECK(original == copy);

	BOOST_CHECK_THROW(copy.Rename("   ", "surname", "patronymic"), invalid_argument);
	BOOST_CHECK(original == copy);

	BOOST_CHECK_THROW(copy.Rename("name", "  ", "patronymic"), invalid_argument);
	BOOST_CHECK(original == copy);

	BOOST_CHECK_THROW(copy.Rename("name", "surname", " "), invalid_argument);
	BOOST_CHECK(original == copy);
}

BOOST_AUTO_TEST_CASE(StudentAgeCanBeChanged)
{
	CStudent s("name", "surname", "patronymic", 20);

	s.SetAge(20);
	BOOST_CHECK_EQUAL(s.GetAge(), 20u);

	s.SetAge(30);
	BOOST_CHECK_EQUAL(s.GetAge(), 30u);

	s.SetAge(40);
	BOOST_CHECK_EQUAL(s.GetAge(), 40u);
}

BOOST_AUTO_TEST_CASE(StudentAgeCantBeChangedToWrongValue)
{
	CStudent s("name", "surname", "patronymic", 20);

	BOOST_CHECK_THROW(s.SetAge(19), domain_error);
	BOOST_CHECK_EQUAL(s.GetAge(), 20u);

	BOOST_CHECK_THROW(s.SetAge(13), out_of_range);
	BOOST_CHECK_EQUAL(s.GetAge(), 20u);

	BOOST_CHECK_THROW(s.SetAge(61), out_of_range);
	BOOST_CHECK_EQUAL(s.GetAge(), 20u);
}
