#include <iostream>
#include <functional>

// Callback listener je design pattern gde klasa registruje callback funkciju iz druge klase, 
// u cilju notifikovanja nekog eventa ili da se izvrsi zahtev za neku akciju.

class EventEmitter {
 public:
  using Callback = std::function<void(int)>;

  void register_callback(Callback callback) {
    m_callback = callback;
  }

  void emit_event(int event) {
    if (m_callback) {
      m_callback(event);
    }
  }

 private:
  Callback m_callback;
};

class EventListener {
 public:
  EventListener(EventEmitter& emitter) {
    emitter.register_callback(std::bind(&EventListener::handle_event, this, std::placeholders::_1));
  }

  void handle_event(int event) {
    std::cout << "Received event: " << event << std::endl;
  }
};

int main() {
  EventEmitter emitter;
  EventListener listener(emitter);
  emitter.emit_event(42);
  return 0;
}