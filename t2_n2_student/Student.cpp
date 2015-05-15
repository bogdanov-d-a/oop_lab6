#include "stdafx.h"
#include "Student.h"

using namespace std;

CStudent::CStudent(string const& name, string const& surname,
	string const& patronymic, unsigned age)
	:m_name(name)
	,m_surname(surname)
	,m_patronymic(patronymic)
	,m_age(age)
{
	ThrowOnBadNameComponent(m_name, m_surname, m_patronymic);
	ThrowOnIncorrectAge(m_age);
}

string CStudent::GetName() const
{
	return m_name;
}

string CStudent::GetSurname() const
{
	return m_surname;
}

string CStudent::GetPatronymic() const
{
	return m_patronymic;
}

unsigned CStudent::GetAge() const
{
	return m_age;
}

void CStudent::Rename(string const& name,
	string const& surname, string const& patronymic)
{
	ThrowOnBadNameComponent(name, surname, patronymic);

	string nameCopy(name);
	string surnameCopy(surname);
	string patronymicCopy(patronymic);

	m_name = move(nameCopy);
	m_surname = move(surnameCopy);
	m_patronymic = move(patronymicCopy);
}

void CStudent::SetAge(unsigned age)
{
	ThrowOnIncorrectAge(age);
	
	if (age < m_age)
	{
		throw domain_error("Age can't be reduced");
	}
	
	m_age = age;
}

bool const CStudent::operator==(CStudent const& other) const
{
	return (
		m_name == other.m_name &&
		m_surname == other.m_surname &&
		m_patronymic == other.m_patronymic &&
		m_age == other.m_age
	);
}

bool const CStudent::operator!=(CStudent const& other) const
{
	return !(*this == other);
}

void CStudent::ThrowOnIncorrectAge(unsigned age)
{
	if (age < 14 || age > 60)
	{
		throw out_of_range("Age is out of range");
	}
}

bool CStudent::StringContainsNonWhitespace(string const& str)
{
	return (str.find_first_not_of(' ') != string::npos);
}

bool CStudent::StringIsNotEmptyAndContainsNonWhitespace(string const& str)
{
	return (!str.empty() && StringContainsNonWhitespace(str));
}

void CStudent::ThrowOnBadNameComponent(string const& name,
	string const& surname, string const& patronymic)
{
	if (!StringIsNotEmptyAndContainsNonWhitespace(name))
	{
		throw invalid_argument("Name is incorrect");
	}

	if (!StringIsNotEmptyAndContainsNonWhitespace(surname))
	{
		throw invalid_argument("Surname is incorrect");
	}

	if (!(patronymic.empty() || StringContainsNonWhitespace(patronymic)))
	{
		throw invalid_argument("Patronymic is incorrect");
	}
}
