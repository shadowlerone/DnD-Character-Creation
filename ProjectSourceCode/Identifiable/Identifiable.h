#pragma once

class Identifiable {
	public:
		int getID() {return ID;}
		void setID(int _id) {ID=_id;}
	private:
		int ID;
};