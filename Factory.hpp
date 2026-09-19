#pragma once

#include <stdexcept>
#include <memory>
#include <iostream>

class Button {
public:
	virtual void Render() = 0;
	virtual void OnClick() = 0;
};

class WindowsButton : public Button {
public:
	void Render() override {
		std::cout << "Rendering Windows button\n";
	}

	void OnClick() override {
		std::cout << "Windows button click\n";
	}
};

class HTMLButton : public Button {
public:
	void Render() override {
		std::cout << "Rendering HTML button\n";
	}

	void OnClick() override {
		std::cout << "HTML button click\n";
	}
};

enum class OS {
	windows = 0,
	web
};

class ButtonFactory {
public:
	static std::unique_ptr<Button> CreateButton(const OS os) {
		if (os == OS::windows) {
			return std::make_unique<WindowsButton>();
		}
		else if (os == OS::web) {
			return std::make_unique<HTMLButton>();
		}
		else {
			throw std::invalid_argument("Error! Unknown operating system.");
		}
	}
};

void FactoryTest() {

	try {
		std::unique_ptr<Button> button = ButtonFactory::CreateButton(OS::web);

		button->Render();
		button->OnClick();
	} catch (std::exception ex) {
		std::cerr << ex.what() << "\n";
	}


}
