#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>

class YoutubeSubscriber {
public:
	YoutubeSubscriber(const std::string& name) : _name(name) {}
	virtual ~YoutubeSubscriber() {}

	virtual void SendNotification(const std::string& channel, const std::string& event) const = 0;

protected:
	const std::string _name{};
};

class YoutubeUser : public YoutubeSubscriber {
public:
	YoutubeUser(const std::string& name) : YoutubeSubscriber(name) {}
	~YoutubeUser() {}

	void SendNotification(const std::string& channel, const std::string& event) const override {
		std::cout << "User " << _name << " received notification from " << channel << " : " << event << "\n";
	}
};

class YoutubeChannel {
public:
	YoutubeChannel(const std::string& name) : _name(name) {}
	~YoutubeChannel() {}

	void Subscribe(const std::shared_ptr<YoutubeSubscriber> sub) {
		_subscribers.emplace_back(sub);
	}

	void RemoveInvalidSubscribers() {
		size_t removed_count = std::erase_if(
			_subscribers,
			[](std::weak_ptr<YoutubeSubscriber> subscriber) {
				return subscriber.expired();
			}
		);

		std::cout << removed_count << " subscribers removed\n";
	}

	void Notify(const std::string& event) {
		for (auto& subscriber : _subscribers) {
			if (auto subscriber_shared_ptr = subscriber.lock()) {
				subscriber_shared_ptr->SendNotification(_name, event);
			}
		}
	}
private:
	const std::string _name{};
	std::vector<std::weak_ptr<YoutubeSubscriber>> _subscribers{};
};

void TestObserver() {
	YoutubeChannel channel{ "My Youtube Channel" };

	std::shared_ptr<YoutubeUser> user_1 = std::make_shared<YoutubeUser>("Youtube User 1");
	std::shared_ptr<YoutubeUser> user_2 = std::make_shared<YoutubeUser>("Youtube User 2");

	{
		std::shared_ptr<YoutubeUser> user_3 = std::make_shared<YoutubeUser>("Youtube User 3");

		channel.Subscribe(user_1);
		channel.Subscribe(user_2);
		channel.Subscribe(user_3);
	}

	channel.RemoveInvalidSubscribers();

	channel.Notify("A new video released");
}
