#include <iostream>
#include <vector>
#include <algorithm>

// #1
void print_message(const char* message) {
    std::cout << "[print_message] " << message << std::endl;
}

void execute_cb1(void (*callback)(const char*)) {
    callback("Hello, World!");
}
// ----------

// #2
struct PrintMessage {
    void operator() (const char* message) {
        std::cout << "[PrintMessage] " << message << std::endl;
    }
};

template <typename Callback>
void execute_cb2(Callback callback) {
    callback("Hello, World!");
}
// ----------

// #3
bool cmpCompare(int a, int b) {
    return a < b;
}
void cmpSortNumbers(std::vector<int>& numbers, bool (*callback)(int, int)) {
    std::sort(numbers.begin(), numbers.end(), callback);
}
void cmpPrint(std::vector<int>& numbers) {
    std::cout << "[cmpPrint] ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
// ----------

// #4
class EventEmitter {
// Klasa koja omogućava registraciju callback funkcije i emitovanje događaja pozivajući emit_event funkciju.
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
  Callback m_callback = nullptr;
};
class EventListener {
// Klasa koja se registruje kao listener instance EventEmitter i definise callback za hendlovanje dogadjajima.
 public:
  EventListener(EventEmitter& emitter) {
    emitter.register_callback(std::bind(&EventListener::handle_event, this, std::placeholders::_1));
  }

  void handle_event(int event) {
    std::cout << "Received event: " << event << std::endl;
  }
};

// #5
class Button {
public:
    // using Listener = void (*)(int);
    using Listener = std::function<void(int)>;
    void set_listener(Listener listener) {
        m_listener = listener;
    }
    void click() {
        if (m_listener) {
            m_listener(m_click_count); 
        }
        ++m_click_count;
    }
private:
    int m_click_count = 0;
    Listener m_listener = nullptr;
};
void button_clicked(int click_count) {
    std::cout << "[button_clicked] Button was clicked " << click_count << " times." << std::endl;
}
// #5.1
// Umesto button_clicked, idemo preko functora
struct ButtonClicked {
    void operator()(int click_count) {
        std::cout << "[functor] Button was clicked " << click_count << " times." << std::endl;
    }
};

int main() {
    // #1
    execute_cb1(print_message);

    // #2 Functor and lambda
    PrintMessage pm;
    execute_cb2(pm);
    execute_cb2([] (const char* message) { std::cout << "[Lambda] " << message << std::endl; });

    // #3
    std::vector<int> numbers = {5, 2, 8, 3, 1};
    cmpSortNumbers(numbers, cmpCompare);
    cmpPrint(numbers);

    // #4
    EventEmitter emitter;
    EventListener listener(emitter);
    emitter.emit_event(42);

    // #5
    Button button;
    button.set_listener(button_clicked);
    button.click();
    button.click();
    // #5.1
    ButtonClicked functor;
    button.set_listener(functor);
    button.click();
    button.click();

    
    
    return 0;
}