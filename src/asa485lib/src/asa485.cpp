#include"asa485.hpp"
#include"asacomm.hpp"

#include <iostream>

ASA485::ASA485() {

}

ASA485::ASA485(std::string port) {
	this->ASAComm::setPort(port);
}

ASA485::~ASA485() {
	
}

/* [Wrap] read and write data method */
size_t ASA485::sendWrapMultiBytes(std::vector<uint8_t> data) {

	// Clear daat buffer and wait to create wrap data array
	_data_buffer.clear();

	// Wrap Data Header
	for (uint8_t byte : data) {
		_data_buffer.push_back(PREFIX_DATA_TYPE);
		_data_buffer.push_back(byte);
	}

	return this->ASAComm::writeMultiBytes(_data_buffer);
}
bool ASA485::sendWrapByte(uint8_t data) {
	// Clear daat buffer and wait to create wrap data array
	_data_buffer.clear();

	_data_buffer.push_back(PREFIX_DATA_TYPE);
	_data_buffer.push_back(data);

	return this->ASAComm::writeMultiBytes(_data_buffer);
}

/* [Wrap] send Trigger signal(interrupt) to slaves*/
bool ASA485::sendTrigger() {
	this->ASAComm::writeByte(PREFIX_TRIGGLE_TYPE);
	return true;
}

/* [Wrap] send Trigger signal(interrupt) to slaves*/
bool ASA485::getISR() {
	this->ASAComm::writeByte(PREFIX_GET_STATE_TYPE);
	uint8_t status = this->ASAComm::readByte();
	std::cout << "Status:" << status << std::endl;
	if (status == 'Y')
		return true;
	else
		return false;
}

