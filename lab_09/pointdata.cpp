#include "pointdata.h"

PointDataList::~PointDataList()
{
	toHead();
	tail_->next() = nullptr;
	head_->prev() = nullptr;
	
	PointData* tmp = nullptr;
	
	while (cur_->next() != nullptr)
	{
		tmp = cur_;
		next();
		delete tmp;
	}
}

void PointDataList::insert(PointData* p, PointData* after)
{
	if (after == nullptr)
	{
		push_front(p);
		return;
	}
	
	PointData* curSave = cur_;
	
	while (cur_->next() != after && cur_->next() != head_)
		next();
	
	if (cur_->next() == head_)
		return;
	
	p->next() = after->next();
	p->prev() = after;
	after->next() = p;
	
	if (p->next() == head_)
		tail_ = p;
	
	cur_ = curSave;
}

void PointDataList::push_back(PointData* p)
{
	p->next() = head_;
	if (head_ == nullptr)
	{
		cur_ = p;
		p->prev() = nullptr;
		head_ = p;
	}
	else
		p->prev() = head_->prev();
	tail_ = p;
}

void PointDataList::push_front(PointData* p)
{
	p->next() = head_;
	if (head_ == nullptr)
	{
		cur_ = p;
		p->prev() = nullptr;
		tail_ = p;
	}
	else
		p->prev() = head_->prev();
	head_ = p;
}

Point PointDataList::pop_front()
{
	Point data = head_->data();
	tail_->next() = head_->next();
	head_->next()->prev() = tail_;
	PointData* tmp = head_;
	head_ = head_->next();
	if (cur_ == tmp)
		toHead();
	delete tmp;
	return data;
}

Point PointDataList::pop_back()
{
	Point data = tail_->data();
	head_->prev() = tail_->prev();
	tail_->prev()->next() = head_;
	PointData* tmp = tail_;
	tail_ = tail_->prev();
	if (cur_ == tmp)
		toTail();
	delete tmp;
	return data;
}

PointData *PointDataList::toHead()
{
	cur_ = head_;
	return head_;
}

PointData *PointDataList::toTail()
{
	cur_ = tail_;
	return tail_;
}

PointData *PointDataList::cur()
{
	return cur_;
}

PointData *PointDataList::prev()
{
	cur_ = cur_->prev();
	return cur_;
}

PointData *PointDataList::next()
{
	cur_ = cur_->next();
	return cur_;
}

bool PointDataList::isAtHead()
{
	return cur_ == head_;
}

bool PointDataList::isAtTail()
{
	return cur_ == tail_;
}
