namespace Utils {

struct Vec2 {
  Vec2(float x = 0, float y = 0) : m_x(x), m_y(y) {}
  Vec2 operator+(Vec2 const &obj) {
    m_x += obj.m_x;
    m_y += obj.m_y;
    return *this;
  }

  float m_x, m_y;
};
} // namespace Utils
