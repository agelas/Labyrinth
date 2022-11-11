#include "ui.h"
#include <cassert>

UI* UI::ui_instance;

UI::UI() {
    // There can only be one instance of the UI
    assert(ui_instance == nullptr);
    ui_instance = this;
}

UI* UI::getInstance() {
    // Make sure the singleton instance exists
    assert(ui_instance != nullptr);
    return ui_instance;
}

UI::~UI() {}
