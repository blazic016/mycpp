#include <iostream>

class Button {
public:
    using Listener = void (*)(int);

    void set_listener(Listener listener) {
        m_listener = listener;
    }

    void click() {
        if (m_listener) { // if p is not nullptr
            m_listener(m_click_count); 
        }
        ++m_click_count;
    }

private:
    int m_click_count = 0;
    Listener m_listener = nullptr;
};

void button_clicked(int click_count) {
    std::cout << "Button was clicked " << click_count << " times." << std::endl;
}

int main() {
    Button button;
    button.set_listener(button_clicked);
    button.click();
    button.click();
    return 0;
}