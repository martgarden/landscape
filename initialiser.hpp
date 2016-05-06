#ifndef MARROW_INITIALISER_H
#define MARROW_INITIALISER_H

namespace marrow {
    class Initialiser {
        private:
            static bool _initialised;
            static bool _after_initialised;

        public:
            Initialiser();

            static void init();

            static void afterInit();
    };
}

#endif
