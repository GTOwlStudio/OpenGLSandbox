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
	clearEventQueue();
	for (unsigned int i = 0; i < m_watcher.size(); i++) {
		if (*m_watcher[i] != m_values[i]) {
			m_values[i] = *m_watcher[i];
			m_events.push(i);
		}
	}
}

bool EventManager::isEvent() const
{
	return !m_events.empty();
}

unsigned int EventManager::readEventId()
{
	unsigned int tmp = m_events.back();
	m_events.pop();
	return tmp;
}

bool EventManager::getValue(size_t id) const
{
	return m_values[id];
}

void EventManager::clearEventQueue() {
	while (!m_events.empty()) {
		m_events.pop();
	}
}

void EventManager::addValueSpy(bool* adress)
{
	m_watcher.push_back(adress);
	m_values.push_back(*adress);
}
