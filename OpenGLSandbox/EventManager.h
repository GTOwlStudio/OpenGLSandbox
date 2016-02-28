#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <queue>


class EventManager
{
public:
	EventManager();
	~EventManager();
	void updateEvent();
	void displayEvent();
	bool isEvent() const;
	unsigned int readEventId();
	bool getValue(size_t id) const;
	void addValueSpy(bool* address);
	void clearEventQueue();

private:
	std::vector<bool*> m_watcher;
	std::vector<bool> m_values;
	std::queue<unsigned int> m_events;
};

