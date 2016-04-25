#ifndef MARROW_WINDOW_H
#define MARROW_WINDOW_H

#include <string>

namespace marrow {
    class Window {
        private:
            int _identifier = 0;

        public:
            Window();

            Window(int width, int height, std::string title);

            void SetFocus();

            ~Window();
    };
}

#endif
