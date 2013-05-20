#include <string>
#include <iostream>

class Message
{
public:
	std::string greeting, recipient;
	void send()
	{
		std::cout << greeting << " " << recipient << "!" << std::endl;
	}
};

class Builder
{
public:
	virtual ~Builder() { }
	virtual void build(Message & msg) const=0;
};

class Hello : public Builder
{
public:
	void build(Message & msg) const
	{
		msg.greeting = "Hello";
	}
};

class World : public Builder
{
public:
	void build(Message & msg) const
	{
		msg.recipient = "world";
	}
};

void hello_world(const Builder & stage1, const Builder & stage2)
{
	Message msg;
	stage1.build(msg);
	stage2.build(msg);
	msg.send();
}

int main()
{
	hello_world(Hello(), World());
	return 0;
}

