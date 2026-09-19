#pragma once
#include <memory>
#include <string>
#include <iostream>

struct Size {
	uint32_t width{};
	uint32_t height{};
};

class Object {
public:
	void SetName(const std::string& name) {
		_name = name;
	}

	void SetSize(const Size& size) {
		_size = size;
	}

	void SetStyle(const uint32_t style) {
		_style = style;
	}

	void DisplayProperties() {
		std::cout << "Properties : Name - " << _name << ", Size - (" << _size.width << ", " << _size.height << "), Style - " << _style << "\n";
	}

private:
	std::string _name{};
	Size _size{};
	uint32_t _style{};
};

class ObjectBuilder {
public:
	ObjectBuilder& SetName(const std::string& name) {
		_obj->SetName(name);
		return *this;
	}

	ObjectBuilder& SetSize(const Size& size) {
		_obj->SetSize(size);
		return *this;
	}

	ObjectBuilder& SetStyle(const uint32_t style) {
		_obj->SetStyle(style);
		return *this;
	}

	std::unique_ptr<Object> Build() { return std::move(_obj); }

	void PrintObjPtr() {
		std::cout << "Builder Obj ptr : " << _obj.get() << "\n";
	}

private:
	std::unique_ptr<Object> _obj{ std::make_unique<Object>() };
};

void TestBuilder() {
	ObjectBuilder obj_builder;
	obj_builder.PrintObjPtr();

	std::unique_ptr<Object> obj = obj_builder.
		SetName("My Object").
		SetSize({ 1280, 720 }).
		SetStyle(123).
		Build();

	obj_builder.PrintObjPtr();
	std::cout << "Ouput Obj ptr : " << obj.get() << "\n";

	obj->DisplayProperties();
}
