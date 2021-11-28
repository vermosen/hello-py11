
#pragma once 
#ifndef HABU_DATE_H
#define HABU_DATE_H

#include <cinttypes>

namespace habu {

  class date {
    public:
      date();
      date(std::int64_t ctr);
      ~date();

    public:
      std::int64_t counter() const;

    private:
      std::int64_t m_ctr;
  };
}

#endif // HABU_DATE_H