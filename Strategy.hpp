#pragma once

#include <vector>
#include <iostream>

template<typename T>
class FilterStrategy {
public:
	virtual bool RemoveValue(const T& value) const = 0;
};

template<typename T>
class RemoveNegativesStrategy : public FilterStrategy<T> {
public:
	bool RemoveValue(const T& value) const override {
		return value < 0;
	}
};

template<typename T>
class RemoveOddsStrategy : public FilterStrategy<T> {
public:
	bool RemoveValue(const T& value) const override {
		const auto p_val = value >= 0 ? value : (-1 * value);
		return p_val % 2;
	}
};

template<typename T>
class Values {
public:
	Values(const std::vector<T>& values) : _values(values) {}

	std::vector<T> Filter(const FilterStrategy<T>& strategy) const {
		std::vector<T> filtered_values{};

		for (const auto& value : _values) {
			if (!strategy.RemoveValue(value)) {
				filtered_values.push_back(value);
			}
		}

		return filtered_values;
	}
private:
	std::vector<T> _values{};
};

void TestStrategy() {

	std::vector<int> arr{ -2, 4, 5, -13, 15, 0, -6 };
	Values values{ arr };

	const auto pos_arr = values.Filter(RemoveNegativesStrategy<int>());
	const auto even_arr = values.Filter(RemoveOddsStrategy<int>());

	std::cout << "Pos arr : ";
	for (const auto& value : pos_arr) {
		std::cout << value << " ";
	}
	std::cout << "\n";

	std::cout << "Even arr : ";
	for (const auto& value : even_arr) {
		std::cout << value << " ";
	}
	std::cout << "\n";
}
