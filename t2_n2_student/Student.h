#pragma once

class CStudent
{
public:
	CStudent(std::string const& name, std::string const& surname,
		std::string const& patronymic, unsigned age);

	std::string GetName() const;
	std::string GetSurname() const;
	std::string GetPatronymic() const;
	unsigned GetAge() const;

	void Rename(std::string const& name,
		std::string const& surname, std::string const& patronymic);

	void SetAge(unsigned age);

	bool const operator==(CStudent const& other) const;
	bool const operator!=(CStudent const& other) const;

private:
	std::string m_name, m_surname, m_patronymic;
	unsigned m_age;

	static void ThrowOnIncorrectAge(unsigned age);
	static bool StringContainsNonWhitespace(std::string const& str);
	static bool StringIsNotEmptyAndContainsNonWhitespace(std::string const& str);
	static void ThrowOnBadNameComponent(std::string const& name,
		std::string const& surname, std::string const& patronymic);
};
