#include <iostream>
#include <stack>
#include <string>

// using namespace std;

// Abstract Builder
//
class builder
{
public:
    virtual void on_null() = 0;
    virtual void on_string(const std::string&) = 0;

    virtual void on_array_begin() = 0;
    virtual void on_array_end() = 0;
};


// Concrete Builder
//
class strBuilder : public builder
{
public:
    //maybe we can use the default constructor

	void on_null() {
		_result += "null ";
	}

    void on_string(const std::string& s){
		_result += s + " ";
    }

	void on_array_begin() {
	}

	void on_array_end() {
	}

	const std::string& result() {
		return _result;
	}
private:
	std::string _result;
};


// Stack Builder
class stackBuilder : public builder
{
public:
    //ctor
	stackBuilder() : _errors(0), _val("") {
	}

	void on_null() {
		_val += "null ";
	}

    void on_string(const std::string& s){
		_val += s + " ";
    }

	void on_array_begin() {
		_stack.push(_val);
		_val = "(";
	}

	void on_array_end() {
		_val += ")";
		// use robust stack operation to prevent segfault
		if (_stack.empty()) { 
			_errors++;
		} else {
			_val = _stack.top() + _val;
			_stack.pop();
		}
	}

	const std::string& result() const {
		return _val;
	}

	int errors() const { 
		return _errors;
	}

private:
	std::string _val;
	std::stack<std::string> _stack;
	int _errors;
};


// Director
//
class parser
{
public:
	parser(builder &b) : _build(b) { }
	void test_run() {
		_build.on_array_begin();
		_build.on_null();
		_build.on_string("foo");
		_build.on_array_begin();
		_build.on_array_end();
		_build.on_null();
		_build.on_array_end();
		_build.on_array_end(); // produces error
	}

private:
	builder& _build;
};


int main() {

	stackBuilder build;
	parser parser(build);

	parser.test_run();

	std::cout << build.result() << std::endl;
	std::cout << build.errors() << std::endl;

	return 0;
}


