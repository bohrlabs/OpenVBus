#pragma once
#include "app_state.h"
#include "model.h"

namespace ovb::ui {
    struct Context {
        AppState &s;
        Model    &m;
        Context(AppState &s, Model &m)
            : s(s), m(m) {}
    };
    void DrawDockspace(Context &);
} // namespace ovb::ui
