#include "EventManager.h"



EventManager::EventManager()
{
}


EventManager::~EventManager()
{
	for (unsigned int i = 0; i < m_watcher.size();i++) {
		m_watcher[i] = 0;
	}
}

void EventManager::updateEvent()
{
	for (unsigned int i = 0; i < m_watcher.size();i++) {
		if (*m_watcher[i] != m_values[i]) {
			m_values[i] = *m_watcher[i];
		}
	}
}

void EventManager::addValueSpy(bool *adress)
{
	m_watcher.push_back(adress);
	m_values.push_back(*adress);
	std::cout << m_values.back() << std::endl;
}
