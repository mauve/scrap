
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <functional>

class Object
{
public:
  Object(int id)
    : _id(id)
  {
    std::cout << std::string(_depth, ' ') << "Object::Object: " << id << std::endl;
    _depth++;
  }

  ~Object()
  {
    _depth--;
    std::cout << std::string(_depth, ' ') << "Object::~Object: " << _id << std::endl;
  }

private:
  int _id;
  static int _depth;
};

int Object::_depth = 0;

/***/

void log_and_execute(const std::string& str, const std::function<void()>& func)
{
  std::cout << "<<< " << str << std::endl;
  func();
  std::cout << ">>> " << str << "\n\n\n" << std::endl;
}

/***/

void create_one_object()
{
  Object obj(1);
}

void create_two_objects()
{
  Object obj1(1);
  Object obj2(2);
}

void nested_function_calls()
{
  auto nested_function = []() {
    Object obj3(3);
    Object obj4(4);
  };

  Object obj1(1);
  nested_function();
  Object obj2(2);
}

void a_function_which_throws()
{
  Object obj2(2);
  throw std::exception("Boom!");
}

void let_me_escape()
{
  Object obj1(1);

  try {
    a_function_which_throws();
  }
  catch (const std::exception& ex) {
    std::cout << "--- caught exception: " << ex.what() << std::endl;
  }
}

/***/

int main()
{
  log_and_execute("create_one_object", create_one_object);
  log_and_execute("create_two_objects", create_two_objects);
  log_and_execute("nested_function_calls", nested_function_calls);
  log_and_execute("let_me_escape", let_me_escape);

  return 0;
}
