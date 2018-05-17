#include "ASA485.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	
	ASA485 asa_comm("COM12");

	asa_comm.setBaudrate(38400);
	asa_comm.setTimeout(1000);

	if (asa_comm.connect()) {
		std::cout
			<< "Connect "
			<< asa_comm.getPort()
			<< "successful!"
			<< std::endl;
	}
	else {
		std::cout
			<< "Connect "
			<< asa_comm.getPort()
			<< "Failed!"
			<< std::endl;

		return -1;
	}
	
	try {
		asa_comm.sendWrapByte('T');
	}
	catch (serial::SerialException e) {
		std::cerr<< e.what() << std::endl;
		return -1;
	}

	std::cout << "Read :" << asa_comm.readByte() << std::endl;
	std::cout << "Read :" << asa_comm.readByte() << std::endl;

	try {
		asa_comm.sendWrapByte('K');
	}
	catch (serial::SerialException e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	std::cout << "Read :" << asa_comm.readWrapByte() << std::endl;
	//std::cout << "Read :" << asa_comm.readWrapByte() << std::endl;


	vector<uint8_t> data;
	data.clear();
	data.push_back('A');
	data.push_back('P');
	data.push_back('P');
	data.push_back('L');
	data.push_back('E');

	int send_c(0);
	try {
		send_c = asa_comm.sendWrapMultiBytes(data);
	}
	catch (serial::SerialException e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	cout << "Send  " << send_c << " Data" << endl;;

	vector<uint8_t> rec_data;

	try {
		rec_data = asa_comm.readWrapMultiBytes(data.size());
	}
	catch (serial::SerialException e) {
		std::cerr << e.what() << std::endl;
	}

	for (char byte : rec_data) {
		std::cout << "Read :" << byte << std::endl;
	}

	
	bool isrState(false);
	try {
		isrState = asa_comm.getISR();
	}
	catch (serial::SerialException e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	std::cout << "ISR state : ";
	if (isrState) {
		std::cout << "Have ISR";
	}
	else {
		std::cout << "Without ISR";
	}
	std::cout << std::endl;


	system("pause");

	return 0;
}