#pragma once

class CStringList
{
public:
	struct Node
	{
		std::string data;
		std::shared_ptr<Node> next;
		std::weak_ptr<Node> prev;
	};
	class Iterator;

	Iterator begin();
	Iterator end();
	std::weak_ptr<Node> GetLastNode();

	void Insert(Iterator const& it, std::string const& data);
	void Remove(Iterator const& it);

private:
	std::shared_ptr<Node> m_first;
	std::weak_ptr<Node> m_last;
};

class CStringList::Iterator
	:public std::iterator<std::bidirectional_iterator_tag, std::string>
{
public:
	Iterator();
	Iterator(bool pastEnd, std::weak_ptr<Node> const& node, CStringList *target);

	bool const operator==(Iterator const& other) const;
	bool const operator!=(Iterator const& other) const;

	std::string& operator*() const;
	std::string* operator->() const;

	Iterator& operator++();
	Iterator operator++(int);

	Iterator& operator--();
	Iterator operator--(int);

	std::weak_ptr<Node> GetNode() const;
	bool const IsPastEnd() const;

private:
	bool m_pastEnd;
	std::weak_ptr<Node> m_node;
	CStringList *m_target;
};
