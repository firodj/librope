#include "rope.h"

#include <stdlib.h>
#include <stdio.h>

using namespace std;

class jrope {
  public:
    jrope(): s_(0) {
      r_ = rope_new();
    }
    jrope(const jrope &jr): s_(0) {
      r_ = rope_copy(jr.r_);
    }
    jrope(const char *str): s_(0) {
      r_ = rope_new_with_utf8((uint8_t*)str);
    }
    const char *c_str() {
      if (s_) r_->free(s_);
      s_ = create_cstr();
      return (const char*)s_;
    }
    void insert(size_t pos, const char* str) {
      ROPE_RESULT result = rope_insert(r_, pos, (uint8_t *)str);
    }
    void append(const char* str) {
      insert(size(), str);
    }
    size_t size() const
    {
      return rope_char_count(r_);
    }

    jrope& operator=(const jrope &jr) {
      if (r_) rope_free(r_);
      r_ = rope_copy(jr.r_);
      return *this;
    }
    jrope& operator=(const char* str) {
      if (r_) rope_free(r_);
      r_ = rope_new_with_utf8((uint8_t*)str);
      return *this;
    }
    jrope& operator+=(const jrope &jr) {
      if (s_) r_->free(s_);
      s_ = jr.create_cstr();
      append((const char*)s_);
      return *this;
    }
    jrope& operator+=(const char* right) {
      append(right);
      return *this;
    }
    jrope operator+(const char* right) const {
      jrope res(*this);
      res += right;
      return res;
    }
    jrope operator+(const jrope &jr) const {
      jrope res(*this);
      res += jr;
      return res;
    }

    ~jrope() {
      rope_free(r_);
      if (s_) r_->free(s_);
    }

    void erase(size_t pos, size_t num)
    {
      rope_del(r_, pos, num);
    }
    bool empty() const {
      return size() == 0;
    }
    void replace(size_t pos, size_t num, const char *str)
    {
      erase(pos, num);
      insert(pos, str);
    }
    void replace(size_t pos, size_t num, const jrope &jr)
    {
      if (s_) r_->free(s_);
      s_ = jr.create_cstr();
      replace(pos, num, (const char*)s_);
    }

  protected:
    uint8_t *create_cstr() const {
      return rope_create_cstr(r_);
    }

    rope *r_;
    uint8_t *s_;
};

int main(int argc, char* argv[])
{
  jrope a("kuda");
  jrope b(a);
  jrope c("kuali");

  a = "ganteng mauts";
  a.insert(0, "sekali");
  a = a + "kualas";
  a += b + c;

  printf("%s %s\n", a.c_str(), b.c_str());

  c.replace(1,1, jrope("emb"));
  printf("%s\n", c.c_str());

  return 0;
}
