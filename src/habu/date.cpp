#include <habu/date.h>

namespace habu {

    date::date() : m_ctr(0) {}
    date::date(std::int64_t ctr) 
      : m_ctr(ctr) {}
    date::~date()  {}

    std::int64_t date::counter() const {
      return m_ctr;
    }
}
