#pragma once

template<typename T>
class Parameter {
public:
	Parameter()
		: currentVal(0) {}

	Parameter(T initVal)
		: currentVal(initVal) {}

	void setValue(const T input) {
		if (input != currentVal) {
			changed = true;
			currentVal = input;
		}
	}

	bool isChanged() {
		bool changeStatus = changed;
		changed = false;
		return changeStatus;
	}

	T getValue() const {
		return currentVal;
	}

	operator T() const {
		return getValue();
	}

	void operator=(const T &that) {
		this->setValue(that);
	}

private:
	T currentVal = 0;
	bool changed = true;
};

template<typename T>
class RefParameter {
public:
	RefParameter(T &initVal)
		: currentVal{initVal} {}

	void setValue(const T input) {
		if (input != currentVal) {
			changed = true;
			currentVal = input;
		}
	}

	bool isChanged() {
		bool changeStatus = changed;
		changed = false;
		return changeStatus;
	}

	T getValue() const {
		return currentVal;
	}

	operator T() const {
		return getValue();
	}

	void operator=(const T &that) {
		this->setValue(that);
	}

private:
	T &currentVal;
	bool changed = true;
};
