#include <iostream>
#include <functional>


class Button {
public:
    template <typename Listener>
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
    std::function<void(int)> m_listener;
};

struct ButtonClicked {
    void operator()(int click_count) {
        std::cout << "Button was clicked " << click_count << " times." << std::endl;
    }
};

int main() {
    Button button;
    ButtonClicked button_clicked;
    button.set_listener(button_clicked);
    button.click();
    button.click();
    return 0;
}
