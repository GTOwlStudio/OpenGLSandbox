#pragma once

#include <vector>
#include <iostream>

class EventManager
{
public:
	EventManager();
	~EventManager();
	void updateEvent();
	void displayEvent();
	void addValueSpy(bool *address);

private:
	std::vector<bool*> m_watcher;
	std::vector<bool> m_values;

};

