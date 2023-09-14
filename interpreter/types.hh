#pragma once
#ifndef LANG_types_h
#define LANG_types_h

#define ganzZahl int
namespace lang {
      enum types {
            none, i32, f32
      };

      class numeral {
      public:
            void* value;
            int type;

            numeral(int val)
            {
                  int* p = new int(val);
                  this->value = p;
                  this->type = i32;
            }

            numeral()
            {
                  this->value = nullptr;
                  this->type = none;
            };

            ~numeral()
            {
                  if (value != nullptr) {
                        delete static_cast<int*>(this->value);
                  }
            }

            void setInt(int val)
            {
                  if (value != nullptr) {
                        delete static_cast<int*>(this->value);
                  }
                  int* p = new int(val);
                  this->value = p;
            }

            int getInt()
            {
                  return *static_cast<int*>(this->value);
            }

            void inc()
            {
                  if (type == i32) {
                        ++(*static_cast<int*>(value));
                  }
                  // else if (type == f32) {
                  //       ++(*static_cast<float*>(value));
                  // }
            }

            void dec()
            {
                  if (type == i32) {
                        --(*static_cast<int*>(value));
                  }
                  // else if (type == f32) {
                  //       --(*static_cast<float*>(value));
                  // }
            }
      };

}

#endif /* LANG_types_h */
