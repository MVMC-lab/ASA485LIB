#include"irqmanager.hpp"
#include<iostream>

using namespace std;

void test_cb() {
	cout << "Test callback!!!" << endl;
}

int main(int argc, char** argv) {

	ASA485 asa_comm("COM12");
	if (asa_comm.connect()) {
		cout << "Connect successful" << endl;
	}
	else {
		cout << "Connect failed" << endl;
		system("pause");
		return -1;
	}

	IRQManager irq_manager(asa_comm);

	IRQHandle handle_1(1);
	//handle_1.registerCallback(test_cb);
	handle_1.registerCallback([] {cout << "CB 1" << endl; });

	IRQHandle handle_2(2);
	handle_2.registerCallback([] {cout << "CB 2" << endl; });

	irq_manager.registerIRQHandle(handle_1);
	irq_manager.registerIRQHandle(handle_2);

	while(1) {
		irq_manager.spinOnce();
		_sleep(100);
	}

	system("pause");

	return 0;
}