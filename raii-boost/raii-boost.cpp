
#include <iostream>
#include <boost/signals2.hpp>

class Producer
{
  using signal_type = boost::signals2::signal < void(int) > ;

public:
  boost::signals2::connection add_listener(const signal_type::slot_type& slot)
  {
    return _signal.connect(slot);
  }

  void DoStuff()
  {
    _signal(++_i);
  }

private:
  int _i = 0;
  signal_type _signal;
};



class Broken_Observer
{
public:
  Broken_Observer(Producer& producer)
  {
    producer.add_listener([this](int a) {
      std::cout << "Broken_Observer: " << a << std::endl;
    });
  }
};

class Working_Observer
{
public:
  Working_Observer(Producer& producer, int id)
  {
    _connection = producer.add_listener([this, id](int a) {
      std::cout << "Working_Observer: (" << id << ") " << a << std::endl;
    });
  }

private:
  boost::signals2::scoped_connection _connection;
};


int main()
{
  Producer producer;

  Working_Observer working1{ producer, 0 };
  {
    Broken_Observer broken{ producer };
    Working_Observer working{ producer, 1 };

    producer.DoStuff();
  }

  producer.DoStuff();

  return 0;
}