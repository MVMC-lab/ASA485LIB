#include"asa485.hpp"
#include"asacomm.hpp"

#include<vector>

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
	// Clear data buffer and wait to create wrap data array
	_data_buffer.clear();

	_data_buffer.push_back(PREFIX_DATA_TYPE);
	_data_buffer.push_back(data);

	return this->ASAComm::writeMultiBytes(_data_buffer);
}

std::vector<uint8_t> ASA485::readWrapMultiBytes(size_t count) {
	// Clear data buffer and wait to create wrap data array
	_data_buffer.clear();

	// Read the raw data from 485 adapter
	std::vector<uint8_t> rec_data = this->ASAComm::readMultiBytes(count * 2);
	
	// Parse the data and save to _data_buffer
	if (rec_data.size() == count * 2) {
		// Handle the raw data
		for (int i = 0; i < (int)rec_data.size(); i+=2) {
			if ((i % 2 == 0) ) {
				if (rec_data.at(i) == 'D') {
					_data_buffer.push_back(rec_data.at(i + 1));
				}	
			}
		}
	}
	else if (rec_data.size() % 2 != 0) {
		// There is error occure!!
		throw serial::SerialException("[readWrapMultiBytes()]Received data count not an even!");
	}
	else {
		// There is error occure!!
		throw serial::SerialException("[readWrapMultiBytes()]Received data count not fit target count!");
	}

	return _data_buffer;
}

uint8_t ASA485::readWrapByte() {
	// Read the raw data from 485 adapter
	std::vector<uint8_t> rec_data = this->ASAComm::readMultiBytes(2);
	if (rec_data.size() != 2) {
		throw serial::SerialException("[readWrapByte()]Received data count not an even!");
		return 0;
	}
	return rec_data.at(1);
}

/* [Wrap] send Trigger signal(interrupt) to slaves*/
bool ASA485::sendTrigger() {
	// Clear daat buffer and wait to create wrap data array
	_data_buffer.clear();

	_data_buffer.push_back(PREFIX_TRIGGLE_TYPE);
	_data_buffer.push_back(PREFIX_TRIGGLE_TYPE);

	return this->ASAComm::writeMultiBytes(_data_buffer);
}

/* [Wrap] send Trigger signal(interrupt) to slaves*/
bool ASA485::getISR() {
	// Clear daat buffer and wait to create wrap data array
	_data_buffer.clear();

	_data_buffer.push_back(PREFIX_GET_STATE_TYPE);
	_data_buffer.push_back(PREFIX_GET_STATE_TYPE);

	bool sendResult = this->ASAComm::writeMultiBytes(_data_buffer);
	if (sendResult == false) return false;

	uint8_t echo_header = this->ASAComm::readByte();
	//std::cout << "Header:" << echo_header << std::endl;
	uint8_t status = this->ASAComm::readByte();
	//std::cout << "Status:" << status << std::endl;

	if (status == 'Y')
		return true;
	else
		return false;
}

