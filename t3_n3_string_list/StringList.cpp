#include "stdafx.h"
#include "StringList.h"

using namespace std;

shared_ptr<CStringList::Node> ForceLockWeakPtr(weak_ptr<CStringList::Node> const& weak)
{
	assert(!weak.expired());
	return move(weak.lock());
}

CStringList::Iterator CStringList::begin()
{
	if (m_first)
	{
		return Iterator(false, m_first, this);
	}
	else
	{
		return end();
	}
}

CStringList::Iterator CStringList::end()
{
	return Iterator(true, weak_ptr<Node>(), this);
}

weak_ptr<CStringList::Node> CStringList::GetLastNode()
{
	return m_last;
}

void CStringList::Insert(Iterator const& it, string const& data)
{
	shared_ptr<Node> newNode(new Node);
	newNode->data = data;

	if (it.IsPastEnd())
	{
		if (m_first)
		{
			newNode->prev = m_last;
			ForceLockWeakPtr(m_last)->next = newNode;
			m_last = newNode;
		}
		else
		{
			m_first = newNode;
			m_last = newNode;
		}
	}
	else
	{
		assert(m_first);

		if (ForceLockWeakPtr(it.GetNode()).get() == m_first.get())
		{
			newNode->next = m_first;
			m_first->prev = newNode;
			m_first = newNode;
		}
		else
		{
			shared_ptr<Node> nextNode(ForceLockWeakPtr(it.GetNode()));
			shared_ptr<Node> prevNode(ForceLockWeakPtr(nextNode->prev));

			newNode->prev = prevNode;
			newNode->next = nextNode;

			prevNode->next = newNode;
			nextNode->prev = newNode;
		}
	}
}

void CStringList::Remove(Iterator const& it)
{
	shared_ptr<Node> delNode(ForceLockWeakPtr(it.GetNode()));
	shared_ptr<Node> prevNode(delNode->prev.lock());
	shared_ptr<Node> nextNode(delNode->next);

	if (prevNode)
	{
		if (nextNode)
		{
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}
		else
		{
			prevNode->next.reset();
			m_last = prevNode;
		}
	}
	else
	{
		if (nextNode)
		{
			nextNode->prev.reset();
			m_first = nextNode;
		}
		else
		{
			m_first.reset();
			m_last.reset();
		}
	}
}

CStringList::Iterator::Iterator()
	:m_pastEnd(true)
	,m_target(nullptr)
{}

CStringList::Iterator::Iterator(bool pastEnd, weak_ptr<Node> const& node, CStringList *target)
	:m_pastEnd(pastEnd)
	,m_node(node)
	,m_target(target)
{}

bool const CStringList::Iterator::operator==(Iterator const& other) const
{
	if (m_pastEnd != other.m_pastEnd)
	{
		return false;
	}

	if (m_pastEnd)
	{
		return (m_target == other.m_target);
	}
	else
	{
		return (ForceLockWeakPtr(m_node).get() == ForceLockWeakPtr(other.m_node).get());
	}
}

bool const CStringList::Iterator::operator!=(Iterator const& other) const
{
	return !(*this == other);
}

string& CStringList::Iterator::operator*() const
{
	assert(!m_pastEnd);
	return ForceLockWeakPtr(m_node)->data;
}

string* CStringList::Iterator::operator->() const
{
	return &(*(*this));
}

CStringList::Iterator& CStringList::Iterator::operator++()
{
	assert(!m_pastEnd);

	if (ForceLockWeakPtr(m_node)->next)
	{
		m_node = ForceLockWeakPtr(m_node)->next;
	}
	else
	{
		m_pastEnd = true;
		m_node.reset();
	}

	return *this;
}

CStringList::Iterator CStringList::Iterator::operator++(int)
{
	Iterator old(*this);
	++(*this);
	return old;
}

CStringList::Iterator& CStringList::Iterator::operator--()
{
	if (!m_pastEnd)
	{
		assert(ForceLockWeakPtr(ForceLockWeakPtr(m_node)->prev));
		m_node = ForceLockWeakPtr(ForceLockWeakPtr(m_node)->prev);
	}
	else
	{
		m_pastEnd = false;
		m_node = m_target->GetLastNode();
	}

	return *this;
}

CStringList::Iterator CStringList::Iterator::operator--(int)
{
	Iterator old(*this);
	--(*this);
	return old;
}

weak_ptr<CStringList::Node> CStringList::Iterator::GetNode() const
{
	return m_node;
}

bool const CStringList::Iterator::IsPastEnd() const
{
	return m_pastEnd;
}
