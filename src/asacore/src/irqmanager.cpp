#include"irqmanager.hpp"
#include"irqhandle.hpp"

#include<iostream>

// TODO :: finish impliment

#define EN_DEBUG_MSG

#ifdef EN_DEBUG_MSG
#define DEBUG_MSG(msg) {std::cout << "[DEBUG] " << msg << std::endl;}
#else
#define DEBUG_MSG(msg)
#endif // EN_DEBUG_MSG

IRQManager::IRQManager(ASA485& asa_comm) :
	p_asacomm(&asa_comm) {

}

IRQManager::~IRQManager() {
}

void IRQManager::spinOnce() {
	if (p_asacomm->getISR() == false) return;
	for (IRQHandle& handle : m_IRQHandles) {
		DEBUG_MSG("Handle ID " << handle.getID() << " Called");
		handle.callback();
	}
}

IRQHandle& IRQManager::findIRQHandle(int id) {
	for (IRQHandle& handle : m_IRQHandles) {
		if (handle.getID() == id)
			return handle;
	}
	return IRQHandle();
}

size_t IRQManager::getCount() {
	return m_IRQHandles.size();
}

void IRQManager::registerIRQHandle(IRQHandle& irqhandle) {
	m_IRQHandles.push_back(irqhandle);
}

vector<IRQHandle> IRQManager::getIRQHandleList() {
	return vector<IRQHandle>();
}